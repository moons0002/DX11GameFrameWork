#include "ConstantBuffer.h"

#include "../../Device.h"

CConstantBuffer::CConstantBuffer()
{
}

CConstantBuffer::~CConstantBuffer()
{
}

bool CConstantBuffer::Init(int Size,int Register,int ShaderBufferType)
{
	mSize = Size;
    mRegister = Register;
    mShaderBufferType = ShaderBufferType;

    D3D11_BUFFER_DESC Desc = {};

    Desc.Usage = D3D11_USAGE_DYNAMIC;

    Desc.ByteWidth = Size;

    Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if(FAILED(CDevice::GetInstance().GetDevice()->CreateBuffer(&Desc, nullptr, &mBuffer)))
    {
        return false;
    }

	return true;
}

void CConstantBuffer::Update(void* Data)
{
    D3D11_MAPPED_SUBRESOURCE Map = {};

    CDevice::GetInstance().GetContext()->Map(mBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Map);

    memcpy(Map.pData, Data, mSize);

    CDevice::GetInstance().GetContext()->Unmap(mBuffer.Get(), 0);

    if(mShaderBufferType & EShaderBufferType::Vertex)
    {
        CDevice::GetInstance().GetContext()->VSSetConstantBuffers(mRegister, 1, mBuffer.GetAddressOf());
    }
    if(mShaderBufferType & EShaderBufferType::Pixel)
    {
        CDevice::GetInstance().GetContext()->PSSetConstantBuffers(mRegister, 1, mBuffer.GetAddressOf());
    }
    if(mShaderBufferType & EShaderBufferType::Domain)
    {
        CDevice::GetInstance().GetContext()->DSSetConstantBuffers(mRegister, 1, mBuffer.GetAddressOf());
    }
    if(mShaderBufferType & EShaderBufferType::Geometry)
    {
        CDevice::GetInstance().GetContext()->GSSetConstantBuffers(mRegister, 1, mBuffer.GetAddressOf());
    }
    if(mShaderBufferType & EShaderBufferType::Compute)
    {
        CDevice::GetInstance().GetContext()->CSSetConstantBuffers(mRegister, 1, mBuffer.GetAddressOf());
    }
}
