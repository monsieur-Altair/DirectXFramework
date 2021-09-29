////--------------------------------------------------------------------------------------
//// File: Tutorial05.fx
////
//// Copyright (c) Microsoft Corporation. All rights reserved.
////--------------------------------------------------------------------------------------
//
////--------------------------------------------------------------------------------------
//// Constant Buffer Variables
//// ﬂ«€  HLSL
////--------------------------------------------------------------------------------------
//cbuffer ConstantBuffer : register( b0 )
//{
//	matrix World;
//	matrix View;
//	matrix Projection;
//}
//
////--------------------------------------------------------------------------------------
//struct VS_INPUT
//{
//    float4 Pos  :   POSITION;
//    float4 Color:   COLOR;
//};
//
//struct PS_INPUT
//{
//    float4 Pos   :  SV_POSITION;
//    float4 Color :  COLOR;
//};
//
//
////--------------------------------------------------------------------------------------
//// Vertex Shader
////--------------------------------------------------------------------------------------
//PS_INPUT VS( VS_INPUT input )
//{
//    PS_INPUT output = (PS_INPUT)0;
//    output.Pos = mul( input.Pos, World );
//    output.Pos = mul( output.Pos, View );
//    output.Pos = mul( output.Pos, Projection );
//    output.Color = input.Color;
//    
//    return output;
//}
//
//
////--------------------------------------------------------------------------------------
//// Pixel Shader
////--------------------------------------------------------------------------------------
//float4 PS( PS_INPUT input) : SV_Target
//{
//    return input.Color;
//}
//--------------------------------------------------------------------------------------
// File: Tutorial04.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR0;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(float4 Pos : POSITION, float4 Color : COLOR)
{
    VS_OUTPUT output = (VS_OUTPUT)0;
    output.Pos = mul(Pos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Color = Color;
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT input) : SV_Target
{
    return input.Color;
}
