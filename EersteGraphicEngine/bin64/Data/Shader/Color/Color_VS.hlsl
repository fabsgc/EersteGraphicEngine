cbuffer ConstantBuffer : register( b0 )
{
    matrix View;
    matrix Projection;
    matrix World;
}

SamplerState ColorSampler : register(s0);

struct VS_INPUT
{
    float4 Position : POSITION;
    float4 Color    : COLOR0;
    float2 Texture  : TEXCOORD0;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float3 Binormal : BINORMAL;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
    float2 Texture  : TEXCOORD0;
    float3 Normal   : NORMAL;
    float3 Tangent  : TANGENT;
    float3 Binormal : BINORMAL;
};

VS_OUTPUT VS_MAIN( VS_INPUT IN )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    output.Position = mul( IN.Position, World );
    output.Position = mul( output.Position, View );
    output.Position = mul( output.Position, Projection );
    output.Color    = IN.Color;
    output.Normal   = normalize(mul(float4(IN.Normal, 0.0f), World)).xyz;
    output.Tangent  = normalize(mul(float4(IN.Tangent, 0.0f), World)).xyz;
    output.Binormal = cross(output.Normal, output.Tangent);

    return output;
}