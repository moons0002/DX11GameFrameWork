#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::Destroy()
{
	mActive = false;
}

void CObject::SetEnable(bool Enable)
{
	mEnable = Enable;
}
