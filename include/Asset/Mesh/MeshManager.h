#pragma once

#include "../../GameInfo.h"
#include "Mesh.h"

class CMeshManager
{
	friend class CAssetManager;
public:
	CMeshManager();
	~CMeshManager();

private:
	std::unordered_map<std::string, std::shared_ptr<CMesh>> mMeshMap;

public:
	bool CreateMesh(const std::string& Name, void* VertexData, int Size, int Count,
		D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData,
		int IndexSize = 0, int IndexCount = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	std::shared_ptr<CMesh> FindMesh(const std::string &name);

	bool Init();

	void ReleaseMesh(CAsset* Texture);
};