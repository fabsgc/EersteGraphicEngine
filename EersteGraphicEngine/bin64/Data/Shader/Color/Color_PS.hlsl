#include "Include/Common.hlsli"

struct PS_INPUT
{
    float4 LocalPosition : POSITION;
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
    float2 Texture  : TEXCOORD0;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float3 Binormal : BINORMAL;

    float3 ViewWorldDirection : COLOR1;
};

ColorComponent   ComputeAmbientLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN);
ColorComponent   ComputeDirectionalLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN, int index);
ColorComponent   ComputePointLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN, int index);
ColorComponent   ComputeSpotLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN, int index);

ColorComponent   ComputeEmitter(ColorComponent colorComponent);
ColorComponent   ComputeSpecular(ColorComponent colorComponent, PS_INPUT IN);

LightInformation ComputeLightInformation(int index, PS_INPUT IN);
PixelComponent   ComputePixelComponent(PS_INPUT IN);

float4 PS_MAIN( PS_INPUT IN ) : SV_Target
{
    ColorComponent colorComponent;
    PixelComponent pixelComponent;
    float4 OUT       = (float4) 0;

    colorComponent.Ambient = (float3) 0;
    colorComponent.Diffuse = (float3) 0;
    colorComponent.Specular = (float3) 0;

    pixelComponent = ComputePixelComponent(IN);
    colorComponent = ComputeAmbientLight(pixelComponent, colorComponent, IN);

    for (int i = 0; i < LightIndex; i++)
    {
        switch (Lights[i].LightType)
        {
            case POINT_LIGHT:
                colorComponent = ComputePointLight(pixelComponent, colorComponent, IN, i);
                break;

            case SPOT_LIGHT:
                colorComponent = ComputeSpotLight(pixelComponent, colorComponent, IN, i);
                break;

            case DIRECTIONAL_LIGHT:
                colorComponent = ComputeDirectionalLight(pixelComponent, colorComponent, IN, i);
                break;
        }
    }

    colorComponent = ComputeSpecular(colorComponent, IN);
    colorComponent = ComputeEmitter(colorComponent);

    OUT.rgb = colorComponent.Ambient + colorComponent.Diffuse + colorComponent.Specular;
    OUT.a   = 1.0f;

    return OUT;
}

ColorComponent ComputeAmbientLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN)
{
    colorComponent.Ambient += AmbientColor.rgb * AmbientColor.a * pixelComponent.Diffuse.rgb;
    return colorComponent;
}

ColorComponent ComputePointLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN, int index)
{
    LightInformation information = ComputeLightInformation(index, IN);
    float3 refVector             = (float3) 0;
    float3 lightWorlDdirection   = normalize(-information.LightWorldDirection.xyz);
    float n_dot_l                = dot(lightWorlDdirection, normalize(IN.Normal));

    if (n_dot_l > 0)
    {
        float intensity = information.LightWorldDirection.w;
        float  light_n_dot_l = dot(lightWorlDdirection, IN.Normal);

        // D = kd * ld * md
        colorComponent.Diffuse += max(n_dot_l, 0.0f) * Lights[index].LightColor.rgb * Lights[index].LightColor.a * intensity;

        // R = I - 2(n.I) * n
        refVector = normalize(reflect(lightWorlDdirection, pixelComponent.Normal));

        // S = max(dot(V.R),0)^P * SpecularColor.rgb * SpecularColor.a * color.rgb;
        colorComponent.Specular += pow(max(dot(IN.ViewWorldDirection, refVector), 0), SpecularPower) * SpecularColor.rgb * SpecularColor.a * intensity;
    }

    return colorComponent;
}

ColorComponent ComputeSpotLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN, int index)
{
    LightInformation information = ComputeLightInformation(index, IN);
    float3 refVector             = (float3) 0;
    float3 lightWorlDdirection   = normalize(-information.LightWorldDirection.xyz);
    float n_dot_l                = dot(lightWorlDdirection, normalize(IN.Normal));

    if (n_dot_l > 0)
    {
        float intensity = information.LightWorldDirection.w;
        float light_n_dot_l = dot(lightWorlDdirection, IN.Normal);
        float lightAngle = dot(information.LightDirection, lightWorlDdirection);

        if(lightAngle > 0)
        {
            float spotFactor = smoothstep(Lights[index].LightOuterAngle, Lights[index].LightInnerAngle, lightAngle);

            // D = kd * ld * md
            colorComponent.Diffuse += max(n_dot_l, 0.0f) * Lights[index].LightColor.rgb * Lights[index].LightColor.a * intensity * spotFactor;
            // R = I - 2(n.I) * n
            refVector = normalize(reflect(lightWorlDdirection, pixelComponent.Normal));
            // S = max(dot(V.R),0)^P;
            colorComponent.Specular += pow(max(dot(IN.ViewWorldDirection, refVector), 0), SpecularPower) * SpecularColor.rgb * SpecularColor.a * intensity * spotFactor;
        }
    }

    return colorComponent;
}

ColorComponent ComputeDirectionalLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN, int index)
{
    float3 refVector      = (float3) 0;
    float3 lightDirection = normalize(-Lights[index].LightDirection.xyz);
    float n_dot_l         = dot(lightDirection, normalize(IN.Normal));

    if (n_dot_l > 0)
    {
        // D = kd * ld * md
        colorComponent.Diffuse += max(n_dot_l, 0.0f) * Lights[index].LightColor.rgb * Lights[index].LightColor.a * pixelComponent.Diffuse.rgb;
        // R = I - 2(n.I) * n
        refVector = normalize(reflect(lightDirection, pixelComponent.Normal));
        // S = max(dot(V.R),0)^P;
        colorComponent.Specular += pow(max(dot(IN.ViewWorldDirection, refVector), 0), SpecularPower) * SpecularColor.rgb * SpecularColor.a;
    }

    return colorComponent;
}

ColorComponent ComputeEmitter(ColorComponent colorComponent)
{
    if(EmitPower > 0)
    {
        colorComponent.Diffuse *= (1 + EmitPower);
    }

    return colorComponent;
}

ColorComponent ComputeSpecular(ColorComponent colorComponent, PS_INPUT IN)
{
    if (HasSpecularTexture == true)
    {
        colorComponent.Specular.xyz *= SpecularTexture.Sample(ColorSampler, IN.Texture).xyz;
    }

    return colorComponent;
}

PixelComponent ComputePixelComponent(PS_INPUT IN)
{
    PixelComponent pixelComponent;

    pixelComponent.Diffuse = (float4) 0;
    pixelComponent.Specular = (float3) 0;
    pixelComponent.Normal = (float3) 0;

    if (HasDiffuseTexture == true)
    {
        pixelComponent.Diffuse = DiffuseTexture.Sample(ColorSampler, IN.Texture);
    }
    else
    {
        pixelComponent.Diffuse = IN.Color;
    }

    if (HasNormalTexture == true)
    {
        float3 sampledNormal = (2 * NormalTexture.Sample(ColorSampler, IN.Texture).xyz) - 1.0f;
        float3x3 tbn = float3x3(IN.Tangent, IN.Binormal, IN.Normal);
        pixelComponent.Normal = mul(sampledNormal, tbn);
    }
    else
    {
        pixelComponent.Normal = normalize(IN.Normal);
    }

    return pixelComponent;
}

LightInformation ComputeLightInformation(int index, PS_INPUT IN)
{
    LightInformation information;
    float3 worldPosition = mul(IN.LocalPosition, World).xyz;

    //Compute vector between light and model
    float3 lightWorldDirection = (Lights[index].LightPosition) - worldPosition;
    information.LightWorldDirection.xyz = normalize(-(lightWorldDirection));
    information.LightWorldDirection.w = saturate(1.0f - (length(lightWorldDirection) / Lights[index].LightRadius));

    //Compute vector between light and camera
    information.LightViewDirection = normalize(CameraPosition - worldPosition);

    //Normalize light direction (light look at)
    information.LightDirection = normalize(Lights[index].LightDirection);

    return information;
}

