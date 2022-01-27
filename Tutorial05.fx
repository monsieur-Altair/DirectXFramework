Texture2D txDiffuse: register(t0);
TextureCube txCube : register(t1);
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

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;

	float4 L: COLOR1;
	float4 N: COLOR2;
	float4 L0: COLOR3;
	float4 L1: COLOR4;
	float4 Diffuse: COLOR5;
	float2 Tex : TEXCOORD;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL, float2 Tex : TEXCOORD)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	output.Diffuse = float4(0.4f, 0.4f, 0.4f, 0.0f);
	float4 lviewvec = mul(View,float4(0,0,-1,0));	

	for (int i = 0; i < 2; i++)
		output.Diffuse += dot(normalize(Normal), normalize((float3)vLightDir[i] - (float3)Pos)) * vLightColor[i];

	for (int i = 0; i < 2; i++)
	{
		float3 lpos = (float3)vLightDir[i];
		float a = dot(normalize(Normal), normalize(lpos - (float3)Pos));
		float b = dot(normalize(Normal), (float3)lviewvec);
		float c = 1.0f / (1.0f + (a - b) * (a - b) * 5); 
		c = pow(c, 5);
		output.Color += vLightColor[i] * c* vLightAmbient[i];
	}


	output.L = lviewvec;
	output.N = float4(Normal.x, Normal.y, Normal.z, 0);
	output.L0 = normalize((float4)(vLightDir[0],0) - Pos);
	output.L1 = normalize((float4)(vLightDir[1], 0) - Pos);
	output.Tex = Tex;

	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader 0
//--------------------------------------------------------------------------------------
float4 PS0(VS_OUTPUT input) : SV_Target
{
	float3 refl = reflect((float3)input.L,(float3)input.N);
	return input.Color +txCube.Sample(samLinear, refl) * 0.8f + float4(0.1f, 0, 0.1f, 0);
}

//struct VS_PUT
//{
//    float4 Pos : POSITION;
//   // float4 Color : COLOR0;
//    float2 Tex : TEXCOORD0;
//    float3 Norm : NORMAL;
//};
//
//struct PS_PUT
//{
//    float4 Pos : SV_POSITION;
//    float2 Tex : TEXCOORD0;
//    float3 Norm : NORMAL;
//};
//
//PS_PUT VS(VS_PUT input)
//{
//    PS_PUT output = (PS_PUT)0;
//    output.Pos = mul(input.Pos, World);
//    output.Pos = mul(output.Pos, View);
//    output.Pos = mul(output.Pos, Projection);
//    output.Tex = input.Tex;
//    output.Norm = mul(input.Norm, World);
//    return output;
//}
//
//float4 PS(PS_PUT input) : SV_Target
//{
//    input.Norm = normalize(input.Norm);
//    
//    float4 diffuse = txDiffuse.Sample(samLinear, input.Tex);
//    float3 finalColor=diffuse*vLightAmbient[0];
//    for (int i = 0; i < 2; i++)
//        finalColor += saturate(dot((float3)vLightDir[i], input.Norm) * vLightColor[i] * diffuse);
//    //finalColor.a = diffuse.a;
//
//    return float4(finalColor,diffuse.a);
//   // return diffuse;
//}
