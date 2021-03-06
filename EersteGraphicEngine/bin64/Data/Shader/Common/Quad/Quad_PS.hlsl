#include "../../Forward/Include/Texture.hlsli"

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 Texture  : TEXCOORD0;
};

Texture2D FinalTexture  : register(t7);

float4 PS_MAIN(PS_INPUT IN) : SV_Target
{
    float4 OUT = FinalTexture.Sample(AnisotropicColorSampler, IN.Texture);
    return OUT;
}