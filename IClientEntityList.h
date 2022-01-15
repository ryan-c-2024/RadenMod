#pragma once

//Not worth doing a forward declare of some of these classes because chances are, if this class is being included
// they're going to be using GetClientEntity
class IClientNetworkable;
class IClientUnknown;
class CBasePlayer;
class CBaseHandle;

class IClientEntityList
{
public:
	// Get IClientNetworkable interface for specified entity
	virtual IClientNetworkable*	GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable*	GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown*		GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	inline virtual CBasePlayer*		GetClientEntity(int entnum) = 0;
	virtual CBasePlayer*		GetClientEntityFromHandle(void* hEnt) = 0;

	// Returns number of entities currently in use
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	// Returns highest index actually used
	virtual int					GetHighestEntityIndex(void) = 0;

	// Sizes entity list to specified size
	virtual void				SetMaxEntities(int maxents) = 0;
	inline virtual int					GetMaxEntities() = 0;
};