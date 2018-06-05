cbuffer ConstantBuffer : register(b0)
{
    matrix View;
    matrix Projection;
    matrix World;

    float4 AmbientColor;

    float4 CameraPosition;

    float4 LightColor;
    float4 LightDirection;
    float4 LightPosition;
    float4 LightRadius;

    float4 SpecularColor;
    float4 SpecularPower;
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

    float3 ViewWorldDirection : COLOR1;
    
    //float4 LightWorldDirection : COLOR2;
    //float3 LightViewDirection : COLOR3;
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

    float3 worldPosition = mul(IN.Position, World).xyz;

    //Compute Camera vector from model
    output.ViewWorldDirection = normalize(worldPosition - CameraPosition.xyz);

    //Compute Camera vector from model
    //float3 lightWorldDirection = (LightPosition.xyz) - worldPosition;
    //output.LightWorldDirection.xyz = normalize(-(lightWorldDirection.xyz));
   // output.LightWorldDirection.w = saturate(1.0f - (length(-lightWorldDirection) / LightRadius.x));

    //Compute Light vector from camera
    //output.LightViewDirection = normalize(CameraPosition.xyz - worldPosition);

    return output;
}