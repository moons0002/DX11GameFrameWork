#include "Texture.h"

#include "../../Device.h"

#ifdef _DEBUG
#pragma comment(lib, "../Bin/DirectXTex_Debug.lib")
#else
#pragma comment(lib, "../Bin/DirectXTex.lib")
#endif

CTexture::CTexture()
{
	mAssetType = EAssetType::Texture;
}

CTexture::~CTexture()
{
	for (auto o : mTextureList)
	{
		SAFE_DELETE(o.second);
	}
	mTextureList.clear();
}

bool CTexture::LoadTexture(const std::string TextureInfoName, const TCHAR * FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, gRootPath);

	lstrcat(FullPath, TEXT("Asset\\"));
	lstrcat(FullPath, FileName);

	return LoadTextureFullPath(TextureInfoName, FullPath);
}

bool CTexture::LoadTextureFullPath(const std::string TextureInfoName, const TCHAR * FullPath)
{
	FTextureInfo* Texture = new FTextureInfo;

	int Length = lstrlen(FullPath);

	for (int i = 0; i < Length; ++i)
	{
		if (gRootPath[i] != FullPath[i])
		{
			lstrcpy(Texture->FileName, &FullPath[i]);
			break;
		}
	}

	TCHAR FileExt[_MAX_EXT] = {};

	_wsplitpath_s(FullPath,
		nullptr, 0,
		nullptr, 0,
		nullptr, 0,
		FileExt, _MAX_EXT
	);

	char ConvertExt[_MAX_EXT] = {};

	int Count = WideCharToMultiByte(CP_ACP, 0, FileExt, -1, nullptr, 0, nullptr, nullptr);

	WideCharToMultiByte(CP_ACP, 0, FileExt, -1, ConvertExt, Count, nullptr, nullptr);

	_strupr_s(ConvertExt);

	DirectX::ScratchImage* Image = new DirectX::ScratchImage;

	if (strcmp(ConvertExt, ".DOS") == 0)
	{
		if (FAILED(DirectX::LoadFromDDSFile(FullPath, DirectX::DDS_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Texture);
			SAFE_DELETE(Image);
			return false;
		}
	}
	else if (strcmp(ConvertExt, ".TGA") == 0)
	{
		if (FAILED(DirectX::LoadFromTGAFile(FullPath, nullptr, *Image)))
		{
			SAFE_DELETE(Texture);
			SAFE_DELETE(Image);
			return false;
		}
	}
	else
	{
		if (FAILED(DirectX::LoadFromWICFile(FullPath, DirectX::WIC_FLAGS_NONE, nullptr, *Image)))
		{
			SAFE_DELETE(Texture);
			SAFE_DELETE(Image);
			return false;
		}	
	}

	Texture->Image = Image;
	mTextureList.insert(std::make_pair(TextureInfoName, Texture));

	return CreateResoureceView(TextureInfoName);
}

void CTexture::SetShader(int Register,int ShaderBufferType, const std::string& Name)
{
	if (ShaderBufferType & EShaderBufferType::Vertex)
	{
		CDevice::GetInstance().GetContext()->VSSetShaderResources(Register, 1, &mTextureList[Name]->SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Pixel)
	{
		CDevice::GetInstance().GetContext()->PSSetShaderResources(Register, 1, &mTextureList[Name]->SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Hull)
	{
		CDevice::GetInstance().GetContext()->HSSetShaderResources(Register, 1, &mTextureList[Name]->SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Domain)
	{
		CDevice::GetInstance().GetContext()->DSSetShaderResources(Register, 1, &mTextureList[Name]->SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Geometry)
	{
		CDevice::GetInstance().GetContext()->GSSetShaderResources(Register, 1, &mTextureList[Name]->SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Compute)
	{
		CDevice::GetInstance().GetContext()->CSSetShaderResources(Register, 1, &mTextureList[Name]->SRV);
	}
}

void CTexture::ResetShader(int Register,int ShaderBufferType)
{
	ID3D11ShaderResourceView* SRV = nullptr;

	if (ShaderBufferType & EShaderBufferType::Vertex)
	{
		CDevice::GetInstance().GetContext()->VSSetShaderResources(Register, 1, &SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Pixel)
	{
		CDevice::GetInstance().GetContext()->PSSetShaderResources(Register, 1, &SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Hull)
	{
		CDevice::GetInstance().GetContext()->HSSetShaderResources(Register, 1, &SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Domain)
	{
		CDevice::GetInstance().GetContext()->DSSetShaderResources(Register, 1, &SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Geometry)
	{
		CDevice::GetInstance().GetContext()->GSSetShaderResources(Register, 1, &SRV);
	}
	if (ShaderBufferType & EShaderBufferType::Compute)
	{
		CDevice::GetInstance().GetContext()->CSSetShaderResources(Register, 1, &SRV);
	}
}

bool CTexture::CreateResoureceView(const std::string& Name)
{
	if (FAILED(DirectX::CreateShaderResourceView(
		CDevice::GetInstance().GetDevice(),
		mTextureList[Name]->Image->GetImages(),
		mTextureList[Name]->Image->GetImageCount(),
		mTextureList[Name]->Image->GetMetadata(),
		&mTextureList[Name]->SRV)))
	{
		return false;
	}
	mTextureList[Name]->Width = static_cast<unsigned int>(mTextureList[Name]->Image->GetImages()[0].width);
	mTextureList[Name]->Height = static_cast<unsigned int>(mTextureList[Name]->Image->GetImages()[0].height);

	return true;
}
