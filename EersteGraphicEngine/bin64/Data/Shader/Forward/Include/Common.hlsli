#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

#define MAX_LIGHT 8

struct LightDesc
{
    float4 LightColor;
    float3 LightDirection;
    float3 LightPosition;
    float LightRadius;
    float LightInnerAngle;
    float LightOuterAngle;
    int LightType;
};

struct LightInformation
{
    float4 LightWorldDirection;
    float3 LightViewDirection;
    float3 LightDirection;
};

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

    float  EmitPower;

    bool   HasDiffuseTexture;
    bool   HasSpecularTexture;
    bool   HasNormalTexture;
}

cbuffer LightConstantBuffer : register(b2)
{
    float4    AmbientColor;

    int       LightIndex;
    LightDesc Lights[MAX_LIGHT];
}

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

