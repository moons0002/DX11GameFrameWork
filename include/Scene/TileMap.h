#pragma once

#include "../GameInfo.h"

class CTile;
class CAnimation;

class CTileMap
{
public:
	CTileMap();
	virtual ~CTileMap();

private:
	int** mTileMap;

	// index와 Tile를 연결
	std::vector<std::shared_ptr<CTile>> mTileList;

	FVector2D StartPoint;

	int mWidth = 0;
	int mHeight = 0;

	float mWidthSize = 32;
	float mHeightSize = 32;

public:
	void SetWidthSize(float Size);
	void SetHeightSize(float Size);

	void AddTile();

	void ChangeTileIndex(int Col, int Row, int Index);

public:
	bool Init();
	bool Init(int Width, int Height);

	void Render();
};

