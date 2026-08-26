#include "Animaiton.h"

#include "../AssetManager.h"
#include "../Texture/Texture.h"

CAnimation::CAnimation()
{
	mOffset = new FVector2D*[mRow]();

	for (int i = 0; i < mRow; i++)
	{
		mOffset[i] = new FVector2D[mCol]();
	}
}

CAnimation::~CAnimation()
{
	SAFE_DELETE_ARRAY(mOffset);
}

void CAnimation::SetStart(FVector2D & Start)
{
	mStart = Start;
}

void CAnimation::SetSize(FVector2D & Size)
{
	mSize = Size;
}

void CAnimation::SetPadding(FVector2D & Padding)
{
	mPadding = Padding;
}

void CAnimation::SetPivot(float x, float y)
{
	mPivot = {x, y};
}

void CAnimation::SetRowCol(int Row,int Col)
{
	mRow = Row;
	mCol = Col;

	SAFE_DELETE_ARRAY(mOffset);

	mOffset = new FVector2D*[mRow]();

	for (int i = 0; i < mRow; i++)
	{
		mOffset[i] = new FVector2D[mCol]();
	}

	SetOffset();
}

void CAnimation::SetWidth(int Width)
{
	mWidth = Width;
}

void CAnimation::SetHeight(int Height)
{
	mHeight = Height;
}

void CAnimation::SetPlayOption(FAnimationPlayOption PlayOption)
{
	mPlayOption = PlayOption;
}

void CAnimation::SetSpeed(float Speed)
{
	mSpeed = Speed;
}

void CAnimation::SetRepeatIndex(int Index)
{
	mRepeatIndex = Index;
}

void CAnimation::SetHorizontalFlip(bool HorizontalFlip)
{
	mHorizontalFlip = HorizontalFlip;
}

void CAnimation::SetVerticalFlip(bool VerticalFlip)
{
	mVerticalFlip = VerticalFlip;
}

void CAnimation::SetTextureInfoName(const std::string & Name)
{
	mTextureInfoName = Name;
}

void CAnimation::SetOffset()
{
	for (int i = 0; i < mRow; i++)
	{
		for (int j = 0; j < mCol; j++)
		{
			mOffset[i][j] = {mStart.x + mSize.x*j + mPadding.x*j, mStart.y + mSize.y*i + mPadding.y*i};
			mOffset[i][j] = {mOffset[i][j].x / mWidth, mOffset[i][j].y / mHeight};
		}
	}
}

FVector2D & CAnimation::GetStart()
{
	return mStart;
}

FVector2D& CAnimation::GetSize()
{
	return mSize;
}

FVector2D & CAnimation::GetPadding()
{
	return mPadding;
}

FVector2D & CAnimation::GetPivot()
{
	return mPivot;
}

int CAnimation::GetIndex()
{
	return mIndex;
}

FAnimationPlayOption CAnimation::GetPlayOption()
{
	return mPlayOption;
}

FVector2D & CAnimation::GetNormalSize()
{
	mNormalSize = {mSize.x/mWidth, mSize.y/mHeight};
	return mNormalSize;
}

int CAnimation::GetFrameSize()
{
	return mRow * mCol;
}

bool CAnimation::GetHorizontalFlip()
{
	return mHorizontalFlip;
}

bool CAnimation::GetVerticalFlip()
{
	return mVerticalFlip;
}

std::string & CAnimation::GetTextureInfoName()
{
	return mTextureInfoName;
}

FVector2D& CAnimation::GetFrame(int FrameIndex)
{
	mIndex = FrameIndex;

	if (FrameIndex >= GetFrameSize() || 0 > FrameIndex)
		return mOffset[0][0];

	int i = FrameIndex / mCol;
	int j = FrameIndex % mCol;
	return mOffset[i][j];
}

FVector2D & CAnimation::GetNextFrame(float DeltaTime)
{
	if (mSpeed <= 0) return GetFrame(mIndex);
	mTime += DeltaTime;
	while (mTime >= 3 / mSpeed)
	{
		mTime -= 3 / mSpeed;
		
		mIndex += mDirection;

		switch (mPlayOption)
		{
		case FAnimationPlayOption::Loop:
			mIndex = mIndex % GetFrameSize();
			break;
		case FAnimationPlayOption::PingPong:
			if (mIndex >= GetFrameSize())
			{
				--mIndex;
				--mIndex;
				mDirection = -1;
			}
			else if (mIndex < 0)
			{
				++mIndex;
				++mIndex;
				mDirection = 1;
			}
			break;
		case FAnimationPlayOption::Once:
			if (mIndex >= GetFrameSize())
			{
				--mIndex;
			}
			break;
		case FAnimationPlayOption::LoopAB:
			if (mIndex >= GetFrameSize())
			{
				mIndex = mRepeatIndex;
			}
			break;
		default:
			break;
		}
	}

	return GetFrame(mIndex);
}

void CAnimation::Init()
{
	//mPlayOption = FAnimationPlayOption::Loop;
	
	//mSpeed = 1;
	
	mDirection = 1;
	
	mIndex = 0;
	
	mTime = 0;

	bool mHorizontalFlip = false;

	bool mVerticalFlip = false;
}
