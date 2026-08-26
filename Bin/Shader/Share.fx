
struct PS_Output_Single
{
	float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
    matrix gmatWorld;
    matrix gmatView;
    matrix gmatproj;
    matrix gmatWV;
    matrix gmatWVP;
}

cbuffer Material : register(b1)
{
	// 재질 기본 색상
    float4 gMtrlBaseColor;
	// 재질 투명도
    float gMtrlOpacity;
	// 재질 텍스쳐 가로 크기
    int gMtrlTextureWidth;
	// 재질 텍스쳐 세로 크기
    int gMtrlTextureHeight;
	// 16 바이트 맞추기용 더미 하나 추가해준다. 
    float gMtrlEmpty;
}

cbuffer Animation : register(b2)
{
    float2 UVScale;
    float2 UVPadding;
    
    int HorizontalFlip;
    int VerticalFlip;

    double Empty;
}

SamplerState gBaseSampler : register(s0);

Texture2D gBaseTexture : register(t0);
//Texture2D gBaseTexture2 : register(t1);
//Texture2D gBaseTexture3 : register(t2);
//Texture2D gBaseTexture4 : register(t3);