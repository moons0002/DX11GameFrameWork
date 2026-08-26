#pragma once

#include "../GameInfo.h"
#include "Shader.h"

class CGraphicShader : public CShader
{
	friend class CShaderManager;
public:
	CGraphicShader();
	virtual ~CGraphicShader();

private:
	ComPtr<ID3D11InputLayout> mInputLayout = nullptr;

	std::vector<D3D11_INPUT_ELEMENT_DESC> mvecDesc;

	unsigned int mInputLayerSize = 0;
	
	// VS
	ComPtr<ID3D11VertexShader> mVs = nullptr;
	ComPtr<ID3DBlob> mVsBlob = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> mPs = nullptr;
	ComPtr<ID3DBlob> mPsBlob = nullptr;

	// HS
	ComPtr<ID3D11HullShader> mHs = nullptr;
	ComPtr<ID3DBlob> mHsBlob = nullptr;

	// DS
	ComPtr<ID3D11DomainShader> mDs = nullptr;
	ComPtr<ID3DBlob> mDsBlob = nullptr;

	// GS
	ComPtr<ID3D11GeometryShader> mGs= nullptr;
	ComPtr<ID3DBlob> mGsBlob = nullptr;

public:
	void AddInputLayoutDesc(const char* Sementic, unsigned int SementicIndex ,DXGI_FORMAT Fmt,
		unsigned int InputSlot, unsigned int Size, D3D11_INPUT_CLASSIFICATION InputSlotClass,
		unsigned int InstanceDataStepRate);
	bool CreateInputLayout();

	bool LoadVertexShader(const char* EntryName, const TCHAR* FileName); 
	bool LoadPixelShader(const char* EntryName, const TCHAR* FileName); 
	bool LoadHullShader(const char* EntryName, const TCHAR* FileName); 
	bool LoadDomainShader(const char* EntryName, const TCHAR* FileName); 
	bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName); 
public:
	virtual bool Init() = 0;
	virtual void SetShader() final;
};