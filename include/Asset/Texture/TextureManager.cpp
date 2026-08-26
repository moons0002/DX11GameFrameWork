#include "TextureManager.h"

#include "Texture.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}

bool CTextureManager::Init()
{
    return true;
}

bool CTextureManager::LoadTexture(const std::string & Name,const TCHAR * FileName, const std::string& LoadTextureName)
{
    std::shared_ptr<CTexture> Texture = FindTexture(Name);

    if (Texture)
    {
        return true;
    }

    Texture = std::make_shared<CTexture>();

    if (!Texture->LoadTexture(LoadTextureName, FileName))
    {
        return false;
    }

    mTextureMap.insert(std::make_pair(Name, Texture));

    return true;
}

bool CTextureManager::LoadTextureFullPath(const std::string & Name, const TCHAR * FullPath, const std::string& LoadTextureName)
{
       std::shared_ptr<CTexture> Texture = FindTexture(Name);

    if (Texture)
    {
        return true;
    }

    Texture = std::make_shared<CTexture>();

    if (!Texture->LoadTexture(LoadTextureName, FullPath))
    {
        return false;
    }

    mTextureMap.insert(std::make_pair(Name, Texture));

    return true;
}

std::shared_ptr<CTexture> CTextureManager::FindTexture(const std::string& Name)
{
    auto iter = mTextureMap.find(Name);

    if (iter == mTextureMap.end())
    {
        return nullptr;
    }
    return iter->second;
}

void CTextureManager::ReleaseTexture(CAsset* Texture)
{
    auto iter = mTextureMap.find(Texture->GetName());

    if (iter != mTextureMap.end())
    {
        if (iter->second.use_count() == 1)
        {
            mTextureMap.erase(iter);
        }
    }
}

bool CTextureManager::PushBackLoadTexture(const std::string& TextureName,const TCHAR * FileName, const std::string& TextureInfoName)
{
    std::shared_ptr<CTexture> Texture = FindTexture(TextureName);

    if (!Texture)
    {
        return false;
    }

    if (!Texture->LoadTexture(TextureInfoName, FileName))
    {
        return false;
    }

    return true;
}
