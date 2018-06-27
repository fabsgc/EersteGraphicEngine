struct PS_INPUT
{
    float4 Position      : SV_POSITION;
    float4 DepthPosition : TEXCOORD0;
};

float4 PS_MAIN( PS_INPUT IN )
{
    float depthValue; = input.depthPosition.z / input.depthPosition.w;
    float4 output (float4) 0;

    output.r = depthValue;
    output.g = depthValue;
    output.b = depthValue;
    output.a = 1.0f;

    return output;
}