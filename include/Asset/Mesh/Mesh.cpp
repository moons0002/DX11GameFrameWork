#include "mesh.h"
#include "../../Device.h"
#include "../AssetManager.h"
#include "../Material/Material.h"
#include "../Material/MaterialManager.h"

CMesh::CMesh()
{
	mAssetType = EAssetType::Mesh;
}

CMesh::~CMesh()
{
}

bool CMesh::CreateMesh(void * VertexData,int Size,int Count,
	D3D11_USAGE VertexUsage,D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData,
	int IndexSize,int IndexCount,DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
	mVertexBuffer.Size = Size;
	mVertexBuffer.Count = Count;
	mVertexBuffer.Data = std::shared_ptr<void>(new char[Size * Count], std::default_delete<char[]>());
	memcpy((std::static_pointer_cast<char>(mVertexBuffer.Data)).get(), VertexData, Size * Count);

	if(!(CreateBuffer(&mVertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER,
		VertexData, Size, Count, VertexUsage))) {
		return false;
	}

	mPrimitive = Primitive;

	if (IndexData) {
		std::shared_ptr<FMeshSlot> slot = std::make_shared<FMeshSlot>();
		slot->IndexBuffer.Size = IndexSize;
		slot->IndexBuffer.Count = IndexCount;
		slot->IndexBuffer.Fmt = Fmt;
		slot->IndexBuffer.Data = std::shared_ptr<void>(new char[IndexSize * IndexCount], std::default_delete<char[]>());
		memcpy((std::static_pointer_cast<char>(slot->IndexBuffer.Data)).get(), IndexData, IndexSize * IndexCount);
			
		if(!CreateBuffer(&slot->IndexBuffer.Buffer, D3D11_BIND_INDEX_BUFFER, IndexData, IndexSize, IndexCount, IndexUsage)) {
			return false;
		}

		slot->Material = CAssetManager::GetInstance().GetMaterialManager()->FindMaterial("DefaultMaterial");

		mMeshSlot.push_back(slot);
	}
	return true;
}

bool CMesh::CreateBuffer(ID3D11Buffer ** Buffer,D3D11_BIND_FLAG Flag,void * Data,int Size,int Count,D3D11_USAGE Usage)
{
	D3D11_BUFFER_DESC BufferDesc = {};

	BufferDesc.ByteWidth = Size * Count;
	BufferDesc.BindFlags = Flag;

	if (Usage == D3D11_USAGE_DYNAMIC)
	{
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;	
	}
	if (Usage == D3D11_USAGE_STAGING)
	{
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	}

	D3D11_SUBRESOURCE_DATA BufferData = {};
	BufferData.pSysMem = Data;

	if(FAILED(CDevice::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &BufferData, Buffer)))
	{
		return false;
	}

	return true;
}

void CMesh::Render()
{
	CDevice::GetInstance().GetContext()->IASetPrimitiveTopology(mPrimitive);

	UINT stride = mVertexBuffer.Size;
	UINT Offset = 0;
	CDevice::GetInstance().GetContext()->IASetVertexBuffers(0, 1, mVertexBuffer.Buffer.GetAddressOf(), 
		&stride, &Offset);

	size_t SlotSize = mMeshSlot.size();

	if (SlotSize > 0)
	{
		for(size_t i = 0; i < SlotSize; i++)
		{
			CDevice::GetInstance().GetContext()->IASetIndexBuffer(mMeshSlot[i]->IndexBuffer.Buffer.Get(),
				mMeshSlot[i]->IndexBuffer.Fmt, 0);

			CDevice::GetInstance().GetContext()->DrawIndexed(mMeshSlot[i]->IndexBuffer.Count,
				0, 0);
		}
	}
	else
	{
		CDevice::GetInstance().GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		CDevice::GetInstance().GetContext()->Draw(mVertexBuffer.Count, 0);
	}
}

void CMesh::Render(int SlotIndex)
{
	// 그려줄 도형 타입을 지정해준다. 
	CDevice::GetInstance().GetContext()->IASetPrimitiveTopology(mPrimitive);

	//버텍스 버퍼 셋팅 해준다. 
	UINT stride = mVertexBuffer.Size;
	UINT Offset = 0;
	CDevice::GetInstance().GetContext()->IASetVertexBuffers(0, 1, &mVertexBuffer.Buffer, &stride, &Offset);

	//인덱스 버퍼 유무 판단 
	size_t SlotSize = mMeshSlot.size();

	if (SlotSize > 0)
	{
		CDevice::GetInstance().GetContext()->IASetIndexBuffer(mMeshSlot[SlotIndex]->IndexBuffer.Buffer.Get(), mMeshSlot[SlotIndex]->IndexBuffer.Fmt, 0);

		// 인덱스 참고하여 화면에 도형을 그린다. 
		// 인덱스 갯수, 인덱스 위치, 버텍스의 시작 위치 
		CDevice::GetInstance().GetContext()->DrawIndexed(mMeshSlot[SlotIndex]->IndexBuffer.Count, 0, 0);

	}
	else
	{
		// 인덱스 버퍼가 없으므로 그냥 그려줄것이다. 
		CDevice::GetInstance().GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
		//정점만 출력해라!
		CDevice::GetInstance().GetContext()->Draw(mVertexBuffer.Count, 0);
	}

}