#pragma once

#include "ConstantBuffer.h"

class CConstantBufferData
{
public:
	CConstantBufferData();
	virtual ~CConstantBufferData();

protected:
	std::shared_ptr<CConstantBuffer> mBuffer;

	void SetConstantBuffer(const std::string& Name);

public:
	virtual bool Init() = 0;
	virtual void UpdateBuffer() = 0;

	virtual CConstantBufferData* Clone() = 0;
};
