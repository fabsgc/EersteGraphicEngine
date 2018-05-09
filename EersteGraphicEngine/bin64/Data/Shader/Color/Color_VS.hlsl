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
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color    : COLOR0;
};

VS_OUTPUT VS_MAIN( VS_INPUT IN )
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	
    output.Position = mul( IN.Position, World );
    output.Position = mul( output.Position, View );
    output.Position = mul( output.Position, Projection );
    output.Color = IN.Color;

    return output;
}