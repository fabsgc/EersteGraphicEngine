cbuffer ConstantBuffer : register( b0 )
{
    matrix View;
    matrix Projection;
    matrix World;
}

SamplerState ColorSampler : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
    float2 Texture  : TEXCOORD0;
    float3 Normal   : NORMAL;
	float3 Tangent  : TANGENT;
	float3 Binormal : BINORMAL;
};

float4 PS_MAIN( PS_INPUT IN ) : SV_Target
{
	return IN.Color;
}