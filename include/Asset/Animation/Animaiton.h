#pragma once

#include "../Asset.h"
#include "../../GameInfo.h"

class CTexture;

enum FAnimationPlayOption
{
	Loop,
	PingPong,
	Once,
	LoopAB,
	ReverseLoop,
	ReversePingPong,
	ReverseOnce
};

class CAnimation : public CAsset 
{
public:
	CAnimation();
	virtual ~CAnimation();

private:
	// 픽셀 단위
	FVector2D mStart;
	FVector2D mSize;
	FVector2D mPadding;

	FVector2D mPivot;

	int mRow = 1;
	int mCol = 1;

	unsigned int mWidth = 1;
	unsigned int mHeight = 1;

	// 재생 옵션
	FAnimationPlayOption mPlayOption = FAnimationPlayOption::Loop;
	// 속도
	float mSpeed = 1;
	// 1 정방향, -1 역방향
	int mDirection = 1;
	// 현재 애니메이션 Index
	int mIndex = 0;
	// 구간 반복 Index
	int mRepeatIndex = 0;
	// 시간 저장
	float mTime = 0;
	

	// 0 ~ 1
	FVector2D** mOffset;

	FVector2D mNormalSize;

	// 좌우 뒤집기
	bool mHorizontalFlip = false;
	bool mVerticalFlip = false;

	// 위아래 뒤집기

	// TextureInfo의 이름
	std::string mTextureInfoName;

public:
	void SetStart(FVector2D& Start);
	void SetSize(FVector2D& Size);
	void SetPadding(FVector2D& Padding);

	void SetPivot(float x, float y);

	void SetRowCol(int Row, int Col);
	void SetWidth(int Width);
	void SetHeight(int Height);

	void SetPlayOption(FAnimationPlayOption PlayOption);
	void SetSpeed(float Speed);

	void SetRepeatIndex(int Index);

	void SetHorizontalFlip(bool HorizontalFlip);
	void SetVerticalFlip(bool VerticalFlip);

	void SetTextureInfoName(const std::string& Name);
private:
	void SetOffset();

public:
	FVector2D& GetStart();
	FVector2D& GetSize();
	FVector2D& GetPadding();

	FVector2D& GetPivot();
	int GetIndex();

	FAnimationPlayOption GetPlayOption();

	FVector2D& GetNormalSize();
	int GetFrameSize();

	bool GetHorizontalFlip();
	bool GetVerticalFlip();

	std::string& GetTextureInfoName();

public:
	// 특정 Frame의 Offset을 반환
	FVector2D& GetFrame(int FrameIndex);
	// 속도에 따라 다음 보여줄 프레임으로 변경하고, 그 Offset을 반환
	FVector2D& GetNextFrame(float DeltaTime);

public:
	void Init();
};

