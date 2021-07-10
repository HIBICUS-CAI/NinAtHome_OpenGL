cbuffer ConstantBuffer : register(b0)
{
    matrix Projection;
};
cbuffer ConstantUpdateBuffer : register(b1)
{
    matrix World;
};
struct VS_INPUT
{
    float3 PosL : POSITION;
    float4 ColorL : COLOR;
    float2 TexCoordL : TEXCOORD;
};
struct VS_OUTPUT
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float4 ColorW : COLOR;
    float2 TexCoordL : TEXCOORD;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.PosH = mul(float4(input.PosL, 1.0f), World);
    output.PosW = output.PosH.xyz;
    output.ColorW = input.ColorL;
    output.PosH = mul(output.PosH, Projection);
    output.TexCoordL = input.TexCoordL;
    return output;
}