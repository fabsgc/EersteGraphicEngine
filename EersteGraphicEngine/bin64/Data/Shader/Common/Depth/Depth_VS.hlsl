struct VS_INPUT
{
    float4 Position : POSITION;
};

struct VS_OUTPUT
{
    float4 Position      : SV_POSITION;
    float4 DepthPosition : TEXCOORD0;
};

VS_OUTPUT VS_MAIN( VS_INPUT IN )
{
    VS_OUTPUT output     = (VS_OUTPUT)0;

    IN.position.w        = 1.0f;
    
    output.Localposition = IN.Position;
    output.Position      = mul( IN.Position, World );
    output.Position      = mul( output.Position, View );
    output.Position      = mul( output.Position, Projection );
    output.DepthPosition = output.Position;

    return output;
}