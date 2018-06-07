cbuffer FrameConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;

    float4 CameraPosition;
}

cbuffer ObjectConstantBuffer : register(b1)
{
    matrix World;

    float4 SpecularColor;
    float4 SpecularPower;
}

cbuffer LightConstantBuffer : register(b2)
{
    float4 AmbientColor;

    float4 LightColor;
    float4 LightDirection;
    float4 LightPosition;
    float4 LightRadius;
}

SamplerState ColorSampler : register(s0);

struct ColorComponent
{
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
};