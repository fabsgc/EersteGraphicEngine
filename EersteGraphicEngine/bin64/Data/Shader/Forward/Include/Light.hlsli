#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

#define MAX_LIGHT 8

struct LightDesc
{
    float4 LightColor;
    float3 LightDirection;
    float3 LightPosition;
    float  LightRadius;
    float  LightInnerAngle;
    float  LightOuterAngle;
    int    LightType;
};

struct LightInformation
{
    float4 LightWorldDirection;
    float3 LightViewDirection;
    float3 LightDirection;
};

cbuffer LightConstantBuffer : register(b2)
{
    float4 AmbientColor;

    int LightIndex;
    LightDesc Lights[MAX_LIGHT];
}