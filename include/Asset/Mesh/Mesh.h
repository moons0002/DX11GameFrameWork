#pragma once

#include "../asset.h"
#include "../../GameInfo.h"

class CMaterial;

struct FMeshSlot
{
	FIndexBuffer IndexBuffer;
	std::shared_ptr<CMaterial> Material;
};

class CMesh : public CAsset
{
public:
	CMesh();
	~CMesh();

protected:
	FVertexBuffer mVertexBuffer;
	std::vector<std::shared_ptr<FMeshSlot>> mMeshSlot;
	D3D11_PRIMITIVE_TOPOLOGY mPrimitive;

public:
	int GetSlotCount() const
	{
		return static_cast<int>(mMeshSlot.size());
	}

	std::shared_ptr<FMeshSlot> GetSlot(int SlotIndex) const
	{
		return mMeshSlot[SlotIndex];
	}

public:
	bool CreateMesh(void* VertexData, int Size, int Count,
		D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData,
		int IndexSize = 0, int IndexCount = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN,
		D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

public:
	bool CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, int Size, int Count, D3D11_USAGE Usage);

	void Render();
	void Render(int SlotIndex);
};