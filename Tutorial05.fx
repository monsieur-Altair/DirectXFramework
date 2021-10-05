Texture2D txDiffuse: register(t0);
SamplerState samLinear : register(s0);

cbuffer ConstantBuffer
{
    matrix World;
    matrix View;
    matrix Projection;

    //float4 vOutputColor;
};

cbuffer LightConstantBuffer
{
    float3 vLightDir[2];
    float4 vLightColor[2];
    float4 vLightAmbient[2];
}

struct VS_PUT
{
    float4 Pos : POSITION;
   // float4 Color : COLOR0;
    float2 Tex : TEXCOORD0;
    float3 Norm : NORMAL;
};

struct PS_PUT
{
    float4 Pos : SV_POSITION;
    float2 Tex : TEXCOORD0;
    float3 Norm : NORMAL;
};

PS_PUT VS(VS_PUT input)
{
    PS_PUT output = (PS_PUT)0;
    output.Pos = mul(input.Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Tex = input.Tex;
    output.Norm = mul(input.Norm, World);
    return output;
}

float4 PS(PS_PUT input) : SV_Target
{
    input.Norm = normalize(input.Norm);
    
    float4 diffuse = txDiffuse.Sample(samLinear, input.Tex);
    float3 finalColor=diffuse*vLightAmbient[0];
    for (int i = 0; i < 2; i++)
        finalColor += saturate(dot((float3)vLightDir[i], input.Norm) * vLightColor[i] * diffuse);
    //finalColor.a = diffuse.a;

    return float4(finalColor,diffuse.a);
   // return diffuse;
}
