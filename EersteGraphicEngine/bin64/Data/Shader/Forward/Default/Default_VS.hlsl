#include "../Include/Common.hlsli"
#include "../Include/Texture.hlsli"

struct VS_INPUT
{
    float4 Position    : POSITION;
    float4 Color       : COLOR0;
    float2 Texture     : TEXCOORD0;
    float3 Normal      : NORMAL;
    float3 Tangent     : TANGENT;
    float3 Binormal    : BINORMAL;
    float3 instancePos : INSTANCEPOS;
    uint instanceID    : SV_InstanceID;
};

struct VS_OUTPUT
{
    float4 Localposition      : POSITION;
    float4 Position           : SV_POSITION;
    float4 Color              : COLOR0;
    float2 Texture            : TEXCOORD0;
    float3 Normal             : NORMAL;
    float3 Tangent            : TANGENT;
    float3 Binormal           : BINORMAL;
    float3 ViewWorldDirection : COLOR1;
};

VS_OUTPUT VS_MAIN( VS_INPUT IN )
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    
    output.Localposition = IN.Position;
    output.Position      = mul( IN.Position, World );
    output.Position      = mul( output.Position, View );
    output.Position      = mul( output.Position, Projection );
    output.Color         = IN.Color;
    output.Texture       = GetCorrectedTextureCoordinate(IN.Texture);
    output.Normal        = normalize(mul(float4(IN.Normal, 0.0f), World)).xyz;
    output.Tangent       = normalize(mul(float4(IN.Tangent, 0.0f), World)).xyz;
    output.Binormal      = cross(output.Normal, output.Tangent);

    float3 worldPosition = mul(IN.Position, World).xyz;
    output.ViewWorldDirection = normalize(worldPosition - CameraPosition);

    return output;
}