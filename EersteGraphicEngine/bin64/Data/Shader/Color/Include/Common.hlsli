cbuffer ConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    matrix World;

    float4 AmbientColor;

    float4 CameraPosition;

    float4 LightColor;
    float4 LightDirection;
    float4 LightPosition;
    float4 LightRadius;

    float4 SpecularColor;
    float4 SpecularPower;
}

SamplerState ColorSampler : register(s0);

struct ColorComponent
{
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
};