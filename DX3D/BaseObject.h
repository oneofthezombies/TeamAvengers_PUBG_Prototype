#pragma once

class BaseObject
{
private:
	int m_refCount;
public:
	BaseObject();
	virtual ~BaseObject();

	virtual void AddRef();
	virtual void Release();
};

