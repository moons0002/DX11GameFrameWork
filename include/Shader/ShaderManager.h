#pragma once

#include "../GameInfo.h"
#include "Shader.h"
#include "ConstantBuffer/ConstantBuffer.h"

struct FMaterialPixelShader
{
	//
	ID3DBlob* Blob = nullptr;
	ID3D11PixelShader* PS = nullptr;

	~FMaterialPixelShader()
	{
		SAFE_RELEASE(Blob);
		SAFE_RELEASE(PS);
	}
};

class CShaderManager
{
public:
	bool Init();

private:
	std::unordered_map<std::string, std::shared_ptr<CShader>> mShaderMap;
	std::unordered_map<std::string, std::shared_ptr<CConstantBuffer>> mCBufferMap;
	std::unordered_map<std::string, std::shared_ptr<FMaterialPixelShader>> mPixelShaderMap;

public:
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		std::shared_ptr<CShader> Shader = FindShader(Name);

		if(Shader)
		{
			return true;
		}

		Shader = std::make_shared<T>();

		if(!Shader->Init())
		{
			return false;
		}

		mShaderMap.insert(make_pair(Name, Shader));
		return true;
	
	}

	std::shared_ptr<CShader> FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);

public:
	bool CreateConstantBuffer(const std::string& Name, int Size, int Register, int ShaderBufferType);

	std::shared_ptr<CConstantBuffer> FindBuffer(const std::string& Name);
	void ReleaseBuffer(const std::string& Name);

public:
	bool LoadPixelShader(const std::string& Name ,const char* EntryName, const TCHAR* FileName);
	const std::shared_ptr<FMaterialPixelShader> FindPixelShader(const std::string& Name);

private:
	CShaderManager();
	~CShaderManager();
	CShaderManager(const CShaderManager&) = delete;
	void operator=(const CShaderManager&) = delete;

public:
	static CShaderManager &GetInstance() {
		static CShaderManager inst;
		return inst;
	}
};
