#define FLIP_TEXTURE_Y 1

SamplerState AnisotropicColorSampler : register(s0)
{
    Filter = COMPARISON_ANISOTROPIC;
    MaxAnisotropy = 8;
    AddressU = Wrap;
    AddressV = Wrap;
    AddressW = Wrap;
    MinLOD = 0;
    MaxLOD = FLOAT32_MAX;
};

float2 GetCorrectedTextureCoordinate(float2 textureCoordinate)
{
#if FLIP_TEXTURE_Y
    return float2(textureCoordinate.x, 1.0 - textureCoordinate.y);
#else
    return textureCoordinate;
#endif
}