#pragma once

#include "GraphicShader.h"

class CColorMeshShader:
    public CGraphicShader
{
	friend class CShaderManager;
public:
	CColorMeshShader();
	virtual ~CColorMeshShader();

public:
	bool Init() override;
};

