#pragma once
#include "Util.h"

struct matrix3x4_t;

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {};
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ~IClientUnknown() {};
};

class IClientThinkable
{
public:
	virtual ~IClientThinkable() {};
};

class IClientNetworkable
{
public:
	virtual ~IClientNetworkable() {};
};

class IClientRenderable 
{
public:
	virtual ~IClientRenderable() {};

	inline bool	SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) //this is actually iclientrenderable
	{
		typedef bool(__thiscall* tFunc) (void*, matrix3x4_t*, int, int, float);
		return Util::CallVirtualFunction<tFunc>(this, 13)(this, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
	}

};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual ~IClientEntity() {};
};

