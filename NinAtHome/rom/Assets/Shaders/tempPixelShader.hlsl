Texture2D Texture : register(t0);
SamplerState SamLiner : register(s0);

struct VS_OUTPUT
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float4 ColorW : COLOR;
    float2 TexCoordL : TEXCOORD;
};

float4 main(VS_OUTPUT input) : SV_TARGET
{
    float4 texColor = Texture.Sample(SamLiner,input.TexCoordL);

    return texColor * input.ColorW;
}