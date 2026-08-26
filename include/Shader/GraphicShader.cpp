#include "GraphicShader.h"

#include "../Device.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
}

void CGraphicShader::AddInputLayoutDesc(const char* Sementic, unsigned int SementicIndex ,DXGI_FORMAT Fmt,
		unsigned int InputSlot, unsigned int Size, D3D11_INPUT_CLASSIFICATION InputSlotClass,
		unsigned int InstanceDataStepRate)
{
	D3D11_INPUT_ELEMENT_DESC Desc = {};
	Desc.SemanticName = Sementic;
	Desc.SemanticIndex = SementicIndex;

	Desc.Format = Fmt;

	Desc.InputSlot = InputSlot;
	Desc.InputSlotClass = InputSlotClass; 
	Desc.InstanceDataStepRate = InstanceDataStepRate;
		
	Desc.AlignedByteOffset = mInputLayerSize;
	mInputLayerSize += Size;
	
	mvecDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{
	if(FAILED(CDevice::GetInstance().GetDevice()->CreateInputLayout(&mvecDesc[0],
		(UINT)mvecDesc.size(), mVsBlob->GetBufferPointer(),
		mVsBlob->GetBufferSize(), &mInputLayout)))
	{
		return false;
	}

	return true;
}

bool CGraphicShader::LoadVertexShader(const char * EntryName,const TCHAR * FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);

	ComPtr<ID3DBlob> ErrorBlob = nullptr;
	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif

	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName, "vs_5_0", Flag, 0, &mVsBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // DEBUG
		return false;
	}

	CDevice::GetInstance().GetDevice()->CreateVertexShader(mVsBlob->GetBufferPointer(),
		mVsBlob->GetBufferSize(), nullptr, &mVs);

	return true;
}

bool CGraphicShader::LoadPixelShader(const char * EntryName,const TCHAR * FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);

	ComPtr<ID3DBlob> ErrorBlob = nullptr;
	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // DEBUG

	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName, "ps_5_0", Flag, 0, &mPsBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // DEBUG
		return false;
	}

	CDevice::GetInstance().GetDevice()->CreatePixelShader(mPsBlob->GetBufferPointer(),
		mPsBlob->GetBufferSize(), nullptr, &mPs);

	return true;
}

bool CGraphicShader::LoadHullShader(const char * EntryName,const TCHAR * FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);

	ComPtr<ID3DBlob> ErrorBlob = nullptr;
	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // DEBUG


	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName, "hs_5_0", Flag, 0, &mHsBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // DEBUG
		return false;
	}

	CDevice::GetInstance().GetDevice()->CreateHullShader(mHsBlob->GetBufferPointer(),
		mHsBlob->GetBufferSize(), nullptr, &mHs);

	return true;
}

bool CGraphicShader::LoadDomainShader(const char * EntryName,const TCHAR * FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);

	ComPtr<ID3DBlob> ErrorBlob = nullptr;
	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // DEBUG


	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName, "ds_5_0", Flag, 0, &mDsBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // DEBUG
		return false;
	}

	CDevice::GetInstance().GetDevice()->CreateDomainShader(mDsBlob->GetBufferPointer(),
		mDsBlob->GetBufferSize(), nullptr, &mDs);

	return true;
}

bool CGraphicShader::LoadGeometryShader(const char * EntryName,const TCHAR * FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);

	ComPtr<ID3DBlob> ErrorBlob = nullptr;
	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // DEBUG


	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName, "gs_5_0", Flag, 0, &mGsBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // DEBUG
		return false;
	}

	CDevice::GetInstance().GetDevice()->CreateGeometryShader(mGsBlob->GetBufferPointer(),
		mGsBlob->GetBufferSize(), nullptr, &mGs);

	return true;
}

void CGraphicShader::SetShader()
{
	CDevice::GetInstance().GetContext()->VSSetShader(mVs.Get(), nullptr, 0);
	CDevice::GetInstance().GetContext()->PSSetShader(mPs.Get(), nullptr, 0);
	CDevice::GetInstance().GetContext()->HSSetShader(mHs.Get(), nullptr, 0);
	CDevice::GetInstance().GetContext()->DSSetShader(mDs.Get(), nullptr, 0);
	CDevice::GetInstance().GetContext()->GSSetShader(mGs.Get(), nullptr, 0);

	CDevice::GetInstance().GetContext()->IASetInputLayout(mInputLayout.Get());
}
