#include "../Include/Common.hlsli"
#include "../Include/Texture.hlsli"

struct PS_INPUT
{
    float4 DepthPosition      : POSITION;
    float4 Position           : SV_POSITION;
    float4 Color              : COLOR0;
    float2 Texture            : TEXCOORD0;
    float3 Normal             : NORMAL;
    float3 Tangent            : TANGENT;
    float3 Binormal           : BINORMAL;
    float3 ViewWorldDirection : COLOR1;
};

struct PS_OUTPUT
{
    float4 Specular : SV_Target0;
    float4 Normal : SV_Target1;
    float4 Depth : SV_Target2;
};

Texture2D DiffuseTexture  : register(t0);
Texture2D SpecularTexture : register(t1);
Texture2D NormalTexture   : register(t2);

PS_OUTPUT ComputeSpecularBuffer(PS_INPUT IN, PS_OUTPUT OUT);
PS_OUTPUT ComputeNormalBuffer(PS_INPUT IN, PS_OUTPUT OUT);
PS_OUTPUT ComputeDepthBuffer(PS_INPUT IN, PS_OUTPUT OUT);

PS_OUTPUT PS_MAIN(PS_INPUT IN)
{
    PS_OUTPUT OUT;

    OUT = ComputeSpecularBuffer(IN, OUT);
    OUT = ComputeNormalBuffer(IN, OUT);
    OUT = ComputeDepthBuffer(IN, OUT);

    return OUT;
}

PS_OUTPUT ComputeSpecularBuffer(PS_INPUT IN, PS_OUTPUT OUT)
{
    if (HasSpecular == true)
    {
        if (HasSpecularTexture == true)
        {
            OUT.Specular = float4(SpecularTexture.Sample(AnisotropicColorSampler, IN.Texture).xyz, 1.0f);
        }
        else
        {
            OUT.Specular = float4(SpecularColor.xyz, (SpecularPower) / 255.0f);
        }
    }
    else
    {
        OUT.Specular = float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
    

    return OUT;
}

PS_OUTPUT ComputeNormalBuffer(PS_INPUT IN, PS_OUTPUT OUT)
{
    if (HasNormalTexture)
    {
        float3 sampledNormal = (2 * NormalTexture.Sample(AnisotropicColorSampler, IN.Texture).xyz) - 1.0f;
        float3x3 tbn = float3x3(IN.Tangent, IN.Binormal, IN.Normal);
        float3 normal = mul(sampledNormal, tbn);

        OUT.Normal.x = (normal.x + 1.0) / 2.0f;
        OUT.Normal.y = (normal.y + 1.0) / 2.0f;
        OUT.Normal.z = (normal.z + 1.0) / 2.0f;
        OUT.Normal.w = 1.0f;
    }
    else
    {
        OUT.Normal.x = (IN.Normal.x + 1.0) / 2.0f;
        OUT.Normal.y = (IN.Normal.y + 1.0) / 2.0f;
        OUT.Normal.z = (IN.Normal.z + 1.0) / 2.0f;
        OUT.Normal.w = 1.0f;
    }

    return OUT;
}

PS_OUTPUT ComputeDepthBuffer(PS_INPUT IN, PS_OUTPUT OUT)
{
    float depthValue = 1.0 - (IN.DepthPosition.z / 256.0f);

    OUT.Depth.r = depthValue;
    OUT.Depth.g = depthValue;
    OUT.Depth.b = depthValue;
    OUT.Depth.a = 1.0f;

    return OUT;
}