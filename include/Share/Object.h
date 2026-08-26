#pragma once

class CObject
{
protected:
	CObject();
	virtual ~CObject();

protected:
	bool mActive = true;
	bool mEnable = true;

public:
	bool IsActive() {return mActive;}

	bool IsEnable() {return mEnable;}


public:
	virtual void Destroy();
	virtual void SetEnable(bool Enable);
};

