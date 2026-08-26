#include "Share.fx"

cbuffer Collider : register(b2)
{
    float4 ColliderColor;
}

struct VS_Input_Color
{
	float3 Pos : POSITION;
	float4 Color :COLOR;
};

struct VS_Output_Color
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

VS_Output_Color ColorMeshVs(VS_Input_Color Input)
{
	VS_Output_Color output = (VS_Output_Color) 0;
	
    output.Pos = mul(float4(Input.Pos, 1.f), gmatWVP);
	output.Color = Input.Color;
	
	return output;
}

PS_Output_Single ColorMeshPs(VS_Output_Color Input)
{
	PS_Output_Single output = (PS_Output_Single) 0;

	output.Color = Input.Color;

	return output;
}

float4 FrameMeshVs(float3 Pos : POSITION) : SV_POSITION
{
    float4 output = (float4) 0;
	
    output = mul(float4(Pos, 1.f), gmatWVP);
	
    return output;
}

PS_Output_Single FrameMeshPs(float4 Pos : SV_POSITION)
{
    PS_Output_Single output = (PS_Output_Single) 0;
	
    output.Color = float4(0.f, 0.f, 0.f, 1.f);
	
    return output;
}