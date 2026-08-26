#pragma once
#include "GraphicShader.h"


class CAnimationShader : public CGraphicShader
{
public:
	CAnimationShader();
	virtual ~CAnimationShader();

public:
	bool Init();
};