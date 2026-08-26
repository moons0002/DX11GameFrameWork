#pragma once

#include "../Math/Vector2D.h"
#include "../Math/Vector3D.h"
#include "../Math/Vector4D.h"
#include "../Math/Matrix.h"

// 레지스터 0
struct FTransformCBufferInfo
{
	FMatrix matWorld;
	FMatrix matView;
	FMatrix matProj;
	FMatrix matWV;
	FMatrix matWVP;
};

// 레지스터 1
struct FMaterialCBufferInfo
{
	// 재질 기본 색상
	FVector4D BaseColor;
	// 재질 투명도
	float Opacity;
	// 재질 텍스쳐 가로 크기
	int TextureWidth;
	// 재질 텍스쳐 세로 크기
	int TextureHeight;
	// 16 바이트 맞추기용 더미 하나 추가해준다. 
	float Empty;
};


struct FColliderCBufferInfo
{
	FVector4D Color;
};

// 레지스터 2
struct FAnimationCBufferInfo
{
	FVector2D Size;
	FVector2D Padding;
	int HorizontalFlip;
	int VerticalFlip;

	double Empty;
};