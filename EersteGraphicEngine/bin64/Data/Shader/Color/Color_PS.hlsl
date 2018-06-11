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

ColorComponent ComputeAmbientLight(ColorComponent colorComponent, PS_INPUT IN);
ColorComponent ComputeDirectionalLight(ColorComponent colorComponent, PS_INPUT IN);
ColorComponent ComputePointLight(ColorComponent colorComponent, PS_INPUT IN);
ColorComponent ComputeSpotLight(ColorComponent colorComponent, PS_INPUT IN);

float4 PS_MAIN( PS_INPUT IN ) : SV_Target
{
    ColorComponent colorComponent;
    float4 OUT       = (float4) 0;

    colorComponent.Ambient = (float3) 0;
    colorComponent.Diffuse = (float3) 0;
    colorComponent.Specular = (float3) 0;

    colorComponent = ComputeAmbientLight(colorComponent, IN);
    colorComponent = ComputeDirectionalLight(colorComponent, IN);

    OUT.rgb = colorComponent.Ambient + colorComponent.Diffuse + colorComponent.Specular;
    OUT.a   = 1.0f;

    return OUT;
}

ColorComponent ComputeAmbientLight(ColorComponent colorComponent, PS_INPUT IN)
{
    colorComponent.Ambient += AmbientColor.rgb * AmbientColor.a * IN.Color.rgb;
    return colorComponent;
}

ColorComponent ComputeDirectionalLight(ColorComponent colorComponent, PS_INPUT IN)
{
    float3 refVector = (float3) 0;
    float3 lightDirection = normalize(-LightDirection.xyz);
    float n_dot_l = dot(lightDirection, normalize(IN.Normal));

    if (n_dot_l > 0)
    {
		// D = kd * ld * md
        colorComponent.Diffuse += max(n_dot_l, 0.0f) * LightColor.rgb * LightColor.a * IN.Color.rgb;

		// R = I - 2(n.I) * n
        refVector = normalize(reflect(lightDirection, IN.Normal));

		// S = max(dot(V.R),0)^P * SpecularColor.rgb * SpecularColor.a * color.rgb;
        colorComponent.Specular += pow(max(dot(IN.ViewWorldDirection, refVector), 0), SpecularPower) * SpecularColor.rgb * SpecularColor.a * IN.Color.rgb;
    }

    return colorComponent;
}

ColorComponent ComputePointLight(ColorComponent colorComponent, PS_INPUT IN)
{

}

ColorComponent ComputeSpotLight(ColorComponent colorComponent, PS_INPUT IN)
{

}