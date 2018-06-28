#include "../Include/Common.hlsli"
#include "../Include/Texture.hlsli"

struct VS_INPUT
{
    float4 Position : POSITION;
    float4 Color : COLOR0;
    float2 Texture : TEXCOORD0;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
};

struct VS_OUTPUT
{
    float4 DepthPosition : POSITION;
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
    float2 Texture : TEXCOORD0;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
    float3 ViewWorldDirection : COLOR1;
};

VS_OUTPUT VS_MAIN( VS_INPUT IN )
{
    VS_OUTPUT output     = (VS_OUTPUT)0;

    IN.Position.w = 1.0f;
    
    output.Position      = mul( IN.Position, World );
    output.Position      = mul( output.Position, View );
    output.Position      = mul( output.Position, Projection );
    output.DepthPosition = output.Position;

    return output;
}