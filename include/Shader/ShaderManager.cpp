#include "ShaderManager.h"
#include "ColorMeshShader.h"
#include "FrameMeshShader.h"
#include "ConstantBuffer/ConstantBuffer.h"
#include "StaticMeshShader.h"
#include "AnimationShader.h"

#include "../Device.h"

bool CShaderManager::Init()
{
	CreateShader<CColorMeshShader>("ColorMeshShader");

	CreateShader<FrameMeshShader>("FrameMeshShader");

	CreateShader<CStaticMeshShader>("StaticMeshShader");

	CreateShader<CAnimationShader>("AnimationShader");


	if (!LoadPixelShader("DefaultMaterialShader", "DefaultMaterialPS", TEXT("Mesh.fx")))
	{
		return false;
	}

	if (!LoadPixelShader("DefaultAnimationShader", "AnimationPS", TEXT("Animation.fx")))
	{
		return false;
	}

	CreateConstantBuffer("Transform", sizeof(FTransformBufferInfo),
		0, EShaderBufferType::Vertex);

	CreateConstantBuffer("Material", sizeof(FMaterialCBufferInfo),
		1, EShaderBufferType::Pixel);

	CreateConstantBuffer("Animation", sizeof(FAnimationCBufferInfo),
		2, EShaderBufferType::Pixel);

	return true;
}

std::shared_ptr<CShader> CShaderManager::FindShader(const std::string& Name)
{
	std::unordered_map<std::string, std::shared_ptr<CShader>>::iterator iter = mShaderMap.find(Name);

	if (iter == mShaderMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CShaderManager::ReleaseShader(const std::string & Name)
{
	std::unordered_map<std::string, std::shared_ptr<CShader>>::iterator iter = mShaderMap.find(Name);
	if (iter != mShaderMap.end())
	{
		mShaderMap.erase(iter);
	}
}

bool CShaderManager::CreateConstantBuffer(const std::string & Name,int Size,int Register,int ShaderBufferType)
{
	std::shared_ptr<CConstantBuffer> CBuffer = FindBuffer(Name);

	if (CBuffer)
	{
		return true;
	}

	// Name 기준으로 찾을수 있게??
	CBuffer = std::make_shared<CConstantBuffer>();

	if (!CBuffer->Init(Size, Register, ShaderBufferType))
	{
		return false;
	}

	mCBufferMap.insert(std::make_pair(Name, CBuffer));
	return true;
}

std::shared_ptr<CConstantBuffer> CShaderManager::FindBuffer(const std::string & Name)
{
	std::unordered_map<std::string, std::shared_ptr<CConstantBuffer>>::iterator iter = mCBufferMap.find(Name);

	if (iter == mCBufferMap.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CShaderManager::ReleaseBuffer(const std::string & Name)
{
	std::unordered_map<std::string, std::shared_ptr<CConstantBuffer>>::iterator iter = mCBufferMap.find(Name);
	
	if (iter != mCBufferMap.end())
	{
		mCBufferMap.erase(iter);
	}
}

bool CShaderManager::LoadPixelShader(const std::string & Name,const char * EntryName,const TCHAR * FileName)
{
	if (FindPixelShader(Name))
	{
		return true;
	}

	//최종 경로가 나온다.
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../Bin/Shader/"));
	lstrcat(FullPath, FileName);

	//컴파일 했는데 에러가나면 여기에 들어올것이다. 
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	FMaterialPixelShader* mps = new FMaterialPixelShader;

	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "ps_5_0", Flag, 0, &mps->Blob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // _DEBUG
		return false;
	}

	// 컴파일이 성공했다. 
	// 성공했다면 쉐이더 객체 만들어야한다. 
	if (FAILED(CDevice::GetInstance().GetDevice()->CreatePixelShader(mps->Blob->GetBufferPointer(), mps->Blob->GetBufferSize(), nullptr, &mps->PS)))
	{
		return false;
	}

	mPixelShaderMap.insert(std::make_pair(Name, mps));

	return true;
}

const std::shared_ptr<FMaterialPixelShader> CShaderManager::FindPixelShader(const std::string & Name)
{
	auto iter = mPixelShaderMap.find(Name);

	if (iter == mPixelShaderMap.end())
	{
		return nullptr;
	}

	return iter->second;
}

CShaderManager::CShaderManager()
{
}

CShaderManager::~CShaderManager()
{
}
