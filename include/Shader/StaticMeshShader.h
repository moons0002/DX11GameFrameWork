#pragma once
#include "GraphicShader.h"

class CStaticMeshShader : public CGraphicShader
{
public:
	CStaticMeshShader();
	virtual ~CStaticMeshShader();

public:
	bool Init();

};

