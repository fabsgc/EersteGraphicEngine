cbuffer FrameConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;

    float3 CameraPosition;

    matrix Worlds[169];
}

cbuffer ObjectConstantBuffer : register(b1)
{
    matrix World;

    float4 SpecularColor;
    float  SpecularPower;

    float  EmitPower;

    bool   HasSpecular;
    bool   HasEmit;
    bool   HasDiffuseTexture;
    bool   HasSpecularTexture;
    bool   HasNormalTexture;

    bool   IsInstance;
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