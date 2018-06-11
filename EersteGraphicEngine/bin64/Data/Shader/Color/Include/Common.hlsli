#define POINT_LIGHT 1.0f
#define SPOT_LIGHT 2.0f
#define DIRECTIONAL_LIGHT 3.0f

cbuffer FrameConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;

    float3 CameraPosition;
}

cbuffer ObjectConstantBuffer : register(b1)
{
    matrix World;

    float4 SpecularColor;
    float  SpecularPower;
}

cbuffer LightConstantBuffer : register(b2)
{
    float4 AmbientColor;

    float4 LightColor;
    float3 LightDirection;
    float3 LightPosition;
    float  LightRadius;
    float  LightType;
}

SamplerState ColorSampler : register(s0);

struct ColorComponent
{
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
};