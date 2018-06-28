cbuffer QuadConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    matrix World;
}

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
    float4 Position : SV_POSITION;
    float2 Texture  : TEXCOORD0;
};

VS_OUTPUT VS_MAIN( VS_INPUT IN )
{
    VS_OUTPUT OUT     = (VS_OUTPUT)0;

    IN.Position.w = 1.0f;
    
    OUT.Position = mul(IN.Position, World);
    OUT.Position = mul(OUT.Position, View);
    OUT.Position = mul(OUT.Position, Projection);

    OUT.Texture = IN.Texture;

    return OUT;
}