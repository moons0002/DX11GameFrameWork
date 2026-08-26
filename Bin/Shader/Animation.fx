#include "Share.fx"

struct VS_Input_Tex
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VS_Output_Tex
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};


VS_Output_Tex AnimationVS(VS_Input_Tex input)
{
    VS_Output_Tex output = (VS_Output_Tex) 0;
    
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
    
    output.UV = input.UV;
    
    return output;
}

float4 AdjustGamma(float4 Color, float Gamma)
{
    return pow(Color, 1.0 / Gamma);
}

PS_Output_Single AnimationPS(VS_Output_Tex input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    float2 UV = input.UV;
    if (HorizontalFlip == 1)
        UV.x = 1 - UV.x;
    if (VerticalFlip == 1)
        UV.y = 1 - UV.y;
    
    float4 Color = gBaseTexture.Sample(gBaseSampler, UV * UVScale + UVPadding);
    
    Color = AdjustGamma(Color, 1.5);
    
    Color.rgb *= gMtrlBaseColor.rgb;
    
    Color.a *= gMtrlOpacity;
    
    output.Color = Color;
    
    return output;
}