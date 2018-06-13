#include "Include/Common.hlsli"

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
    float2 Texture  : TEXCOORD0;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float3 Binormal : BINORMAL;

    float3 ViewWorldDirection : COLOR1;

    float4 LightWorldDirection : COLOR2;
    float3 LightViewDirection : COLOR3;
};

ColorComponent ComputeAmbientLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN);
ColorComponent ComputeDirectionalLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN);
ColorComponent ComputePointLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN);
ColorComponent ComputeSpotLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN);

PixelComponent ComputePixelComponent(PS_INPUT IN);

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
    colorComponent = ComputeDirectionalLight(pixelComponent, colorComponent, IN);

    OUT.rgb = colorComponent.Ambient + colorComponent.Diffuse + colorComponent.Specular;
    OUT.a   = 1.0f;

    return OUT;
}

ColorComponent ComputeAmbientLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN)
{
    colorComponent.Ambient += AmbientColor.rgb * AmbientColor.a * pixelComponent.Diffuse.rgb;
    return colorComponent;
}

ColorComponent ComputeDirectionalLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN)
{
    float3 refVector = (float3) 0;
    float3 lightDirection = normalize(-LightDirection.xyz);
    float n_dot_l = dot(lightDirection, normalize(IN.Normal));

    if (n_dot_l > 0)
    {
		// D = kd * ld * md
        colorComponent.Diffuse += max(n_dot_l, 0.0f) * LightColor.rgb * LightColor.a * pixelComponent.Diffuse.rgb;

		// R = I - 2(n.I) * n
        refVector = normalize(reflect(lightDirection, pixelComponent.Normal));

		// S = max(dot(V.R),0)^P * SpecularColor.rgb * SpecularColor.a * color.rgb;
        colorComponent.Specular += pow(max(dot(IN.ViewWorldDirection, refVector), 0), SpecularPower) * SpecularColor.rgb * pixelComponent.Specular.rgb * pixelComponent.Diffuse.rgb;
    }

    return colorComponent;
}

ColorComponent ComputePointLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN)
{

}

ColorComponent ComputeSpotLight(PixelComponent pixelComponent, ColorComponent colorComponent, PS_INPUT IN)
{

}

PixelComponent ComputePixelComponent(PS_INPUT IN)
{
    PixelComponent pixelComponent;

    pixelComponent.Diffuse = (float4) 0;
    pixelComponent.Specular = (float3) 0;
    pixelComponent.Normal = (float3) 0;

    if (HasDiffuseTexture == true && LightType == 2)
    {
        pixelComponent.Diffuse = DiffuseTexture.Sample(ColorSampler, IN.Texture);
    }
    else
    {
        pixelComponent.Diffuse = IN.Color;
    }

    if (HasSpecularTexture == true)
    {
        pixelComponent.Specular = SpecularTexture.Sample(ColorSampler, IN.Texture).xyz;
    }
    else
    {
        pixelComponent.Specular = SpecularColor.rgb;
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