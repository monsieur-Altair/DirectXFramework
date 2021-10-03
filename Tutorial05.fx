Texture2D txDiffuse: register(t0);
SamplerState samLinear : register(s0);

cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
};

struct VS_PUT
{
    float4 Pos : POSITION;
   // float4 Color : COLOR0;
    float2 Tex : TEXCOORD0;
};

struct PS_PUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

PS_PUT VS(VS_PUT input)
{
    PS_PUT output = (PS_PUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    //output.Color = Color;
    output.Tex = input.Tex;
    return output;
}

float4 PS(PS_PUT input) : SV_Target
{
    return txDiffuse.Sample(samLinear, input.Tex);
}
