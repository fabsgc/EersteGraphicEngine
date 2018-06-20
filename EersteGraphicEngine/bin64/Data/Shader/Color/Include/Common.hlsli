#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

#define FLIP_TEXTURE_Y 1

#define MAX_LIGHT 8

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

    bool   HasDiffuseTexture;
    bool   HasSpecularTexture;
    bool   HasNormalTexture;
}

cbuffer LightConstantBuffer : register(b2)
{
    float4 AmbientColor;

    float4 LightColor;
    float3 LightDirection;
    float3 LightPosition;
    float  LightRadius;
    int    LightType;
}

Texture2D DiffuseTexture : register(t0);
Texture2D SpecularTexture : register(t1);
Texture2D NormalTexture : register(t2);

SamplerState ColorSampler : register(s0);

struct ColorComponent
{
    float3 Ambient;
    float3 Diffuse;
    float3 Specular;
};

struct PixelComponent
{
    float4 Diffuse;
    float3 Specular;
    float3 Normal;
};

float2 GetCorrectedTextureCoordinate(float2 textureCoordinate)
{
#if FLIP_TEXTURE_Y
    return float2(textureCoordinate.x, 1.0 - textureCoordinate.y);
#else
    return textureCoordinate;
#endif
}

float3 GetVectorColorContribution(float4 light, float3 color)
{
    // Color (.rgb) * Intensity (.a)
    return light.rgb * light.a * color;
}

float3 GetScalarColorContribution(float4 light, float color)
{
    // Color (.rgb) * Intensity (.a)
    return light.rgb * light.a * color;
}