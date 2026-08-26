#include "ConstantBufferData.h"
#include "../ShaderManager.h"

CConstantBufferData::CConstantBufferData()
{
}

CConstantBufferData::~CConstantBufferData()
{
}

void CConstantBufferData::SetConstantBuffer(const std::string& Name)
{
	mBuffer = CShaderManager::GetInstance().FindBuffer(Name);
}