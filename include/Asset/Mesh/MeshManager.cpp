#include "MeshManager.h"

#include "Mesh.h"

CMeshManager::CMeshManager()
{
}

CMeshManager::~CMeshManager()
{
}

bool CMeshManager::CreateMesh(const std::string& Name, void * VertexData,int Size,int Count,D3D11_USAGE VertexUsage,D3D11_PRIMITIVE_TOPOLOGY Primitive,void * IndexData,int IndexSize,int IndexCount,DXGI_FORMAT Fmt,D3D11_USAGE IndexUsage)
{
	std::shared_ptr<CMesh> Mesh = FindMesh(Name);

	if (Mesh)
	{
		return true;
	}

	Mesh = std::make_shared<CMesh>();

	if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage, Primitive, IndexData, IndexSize, IndexCount, Fmt, IndexUsage))
	{
		return false;
	}

	mMeshMap.insert(std::make_pair(Name, std::shared_ptr<CMesh>(Mesh)));

	return true;
}

std::shared_ptr<CMesh> CMeshManager::FindMesh(const std::string & name)
{
	std::unordered_map<std::string, std::shared_ptr<CMesh>>::iterator iter = mMeshMap.find(name);
	if (iter == mMeshMap.end())
	{
		return nullptr;
	}
	return iter->second;
}

bool CMeshManager::Init() {

	// 이 밑은 언젠간 수정해야할 부분

	// 정육면체
	FVertexColor BoxVtx[8] = {
		FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),
		FVertexColor(0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f),
		FVertexColor(-0.5f, -0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, 1.f),

		FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 1.f, 1.f),
		FVertexColor(0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 1.f),
		FVertexColor(-0.5f, -0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 1.f, 0.f, 1.f)
	};

	unsigned short BoxIdx[36] = {
		0,1,2, 1,3,2, // 앞
		5,4,7, 4,6,7, // 뒤
		4,5,0, 5,1,0, // 위
		2,3,6, 3,7,6, // 밑
		4,0,6, 0,2,6, // 좌
		1,5,3, 5,7,3 // 우
	};

	if(!CreateMesh("Box", BoxVtx, sizeof(FVertexColor), 8, D3D11_USAGE_DEFAULT, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		BoxIdx, sizeof(unsigned short), 36, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}

	// 정사각형
	FVertexColor CenterRect[4] =
	{
		FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),
		FVertexColor(0.5f, 0.5f, 0.f, 1.f, 1.f, 0.f, 1.f),
		FVertexColor(-0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.f)
	};

	unsigned short CenterRectIdx[6] = {
		0,1,2, 1,3,2
	};

	if(!CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 4, D3D11_USAGE_DEFAULT, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		CenterRectIdx, sizeof(unsigned short), 6, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}
	
	// 텍스처 사각형
	FVertexTexture CenterTexRect[4]
	{
		FVertexTexture(0.5f, 0.5f, 0.f, 1.f, 0.f),
		FVertexTexture(-0.5f, 0.5f, 0.f, 0.f, 0.f),
		FVertexTexture(-0.5f, -0.5f, 0.f, 0.f, 1.f),
		FVertexTexture(0.5f, -0.5f, 0.f, 1.f, 1.f)
	};

	unsigned short CenterTexRectIdx[6] = {
		1,0,2, 3,2,0
	};

	if (!CreateMesh("CenterTexRect", CenterTexRect, sizeof(FVertexTexture), 4, D3D11_USAGE_DEFAULT,
		D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, CenterTexRectIdx, sizeof(unsigned short), 6, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}

	// 사각형 와이어 프레임
	FVector3D FrameCenterRect[4] =
	{
		FVector3D(-0.5f, 0.5f, 0.f),
		FVector3D(0.5f, 0.5f, 0.f),
		FVector3D(-0.5f, -0.5f, 0.f),
		FVector3D(0.5f, -0.5f, 0.f)
	};

	unsigned short FrameRectIdx[5] = {
		0, 1, 3, 2, 0
	};

	if (!CreateMesh("FrameCenterRect", FrameCenterRect, sizeof(FVector3D),4, D3D11_USAGE_DEFAULT,
		D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, FrameRectIdx, sizeof(unsigned short), 5, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}

	return true;
}

void CMeshManager::ReleaseMesh(CAsset * Texture)
{
	auto iter = mMeshMap.find(Texture->GetName());

    if (iter != mMeshMap.end())
    {
        if (iter->second.use_count() == 1)
        {
            mMeshMap.erase(iter);
        }
    }
}
