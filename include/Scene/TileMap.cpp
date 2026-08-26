#include "TileMap.h"
#include "Tile.h"

CTileMap::CTileMap()
{
	Init();

	// 테스트용 만들어보기
	// 타일 추가할떄 텍스처 정해주고 애니메이션 추가해주기
	SetWidthSize(32);
	SetHeightSize(32);
	Init(20, 20);

	AddTile();
	mTileList[0]->Init();
	mTileList[0]->SetTexture("TileSet");
	mTileList[0]->AddAnimation("Green", FVector2D(0.f, 0.f), FVector2D(32.f, 32.f), FVector2D(0.f, 0.f), 1, 1);

	ChangeTileIndex(0,0,0);
}

CTileMap::~CTileMap()
{
	for (int i = 0; i < mWidth; ++i)
	{
		SAFE_DELETE_ARRAY(mTileMap[i]);
	}
}

void CTileMap::SetWidthSize(float Size)
{
	mWidthSize = Size;
	for (auto o : mTileList)
	{
		o->SetScale(FVector3D(mWidthSize, mHeightSize, 1.f));
	}
}

void CTileMap::SetHeightSize(float Size)
{
	mHeightSize = Size;
	for (auto o : mTileList)
	{
		o->SetScale(FVector3D(mWidthSize, mHeightSize, 1.f));
	}
}

void CTileMap::AddTile()
{
	std::shared_ptr<CTile> Tile = std::make_shared<CTile>();
	
	Tile->SetScale(FVector3D(mWidthSize, mHeightSize, 1.f));

	mTileList.push_back(Tile);
}

void CTileMap::ChangeTileIndex(int Col,int Row, int Index)
{
	mTileList[mTileMap[Col][Row]]->EraseTileInfo(FVector2D(Col, Row));

	mTileMap[Col][Row] = Index;

	mTileList[Index]->AddTileInfo(FVector2D(Col, Row));

	mTileList[Index]->UpdateData();
}

bool CTileMap::Init()
{
	for (int i = 0; i < mWidth; ++i)
	{
		SAFE_DELETE_ARRAY(mTileMap[i]);
	}

	return true;
}

bool CTileMap::Init(int Width, int Height)
{
	for (int i = 0; i < mWidth; ++i)
	{
		SAFE_DELETE_ARRAY(mTileMap[i]);
	}

	mWidth = Width;
	mHeight = Height;

	mTileMap = new int*[mWidth];
	for (int i = 0; i < mWidth; ++i)
	{
		mTileMap[i] = new int[mHeight];
	}

	mTileMap[5][5] = 0;

	return true;
}

void CTileMap::Render()
{
	for (int i = 0; i < mTileList.size(); ++i)
	{
		mTileList[i]->Render();
	}
}
