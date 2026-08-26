#pragma once

#include "../Share/Object.h"

class CShader : public CObject
{
	friend class CShaderManager;
public:
	CShader() = default;
	virtual ~CShader() = default;
	CShader(const CShader&) = delete;
    CShader& operator=(const CShader&) = delete;

public:
	virtual bool Init() = 0;
	virtual void SetShader() = 0;
};

