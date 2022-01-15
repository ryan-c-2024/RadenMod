#pragma once


/*

class IClientRenderable
{
public:
	virtual IClientUnknown*	GetIClientUnknown() = 0;
	virtual Vector const&			GetRenderOrigin(void) = 0;
	virtual QAngle const&			GetRenderAngles(void) = 0;
	virtual bool					ShouldDraw(void) = 0;
	virtual bool					IsTransparent(void) = 0;
	virtual bool					UsesPowerOfTwoFrameBufferTexture() = 0;
	virtual bool					UsesFullFrameBufferTexture() = 0;
	virtual ClientShadowHandle_t	GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&	RenderHandle() = 0;
	virtual const model_t*			GetModel() const = 0;
	virtual int						DrawModel(int flags) = 0;
	virtual int		GetBody() = 0;
	virtual void	ComputeFxBlend() = 0;
	virtual int		GetFxBlend(void) = 0;
	virtual void	GetColorModulation(float* color) = 0;
	virtual bool	LODTest() = 0;
	virtual bool	SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0; //index 16	
	virtual void	SetupWeights(const matrix3x4_t *pBoneToWorld, int nFlexWeightCount, float *pFlexWeights, float *pFlexDelayedWeights) = 0;
	virtual void	DoAnimationEvents(void) = 0;
	virtual IPVSNotify* GetPVSNotifyInterface() = 0;
	virtual void	GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void	GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void	GetShadowRenderBounds(Vector &mins, Vector &maxs, ShadowType_t shadowType) = 0;
	virtual bool	ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool	GetShadowCastDistance(float *pDist, ShadowType_t shadowType) const = 0;
	virtual bool	GetShadowCastDirection(Vector *pDirection, ShadowType_t shadowType) const = 0;
	virtual bool	IsShadowDirty() = 0;
	virtual void	MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable *GetShadowParent() = 0;
	virtual IClientRenderable *FirstShadowChild() = 0;
	virtual IClientRenderable *NextShadowPeer() = 0;
	virtual ShadowType_t ShadowCastType() = 0;
	virtual void CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t GetModelInstance() = 0;
	virtual const matrix3x4_t &RenderableToWorldTransform() = 0;
	virtual int LookupAttachment(const char *pAttachmentName) = 0;
	virtual	bool GetAttachment(int number, Vector &origin, QAngle &angles) = 0;
	virtual bool GetAttachment(int number, matrix3x4_t &matrix) = 0;
	virtual float *GetRenderClipPlane(void) = 0;
	virtual int		GetSkin() = 0;
	virtual bool	IsTwoPass(void) = 0;
	virtual void	OnThreadedDrawSetup() = 0;
	virtual bool	UsesFlexDelayedWeights() = 0;
	virtual void	RecordToolMessage() = 0;
	virtual bool	IgnoresZBuffer(void) const = 0;
};

class IClientNetworkable
{
public:
	// Gets at the containing class...
	virtual IClientUnknown*	GetIClientUnknown() = 0;

	// Called by the engine when the server deletes the entity.
	virtual void			Release() = 0;

	// Supplied automatically by the IMPLEMENT_CLIENTCLASS macros.
	virtual ClientClass*	GetClientClass() = 0;

	// This tells the entity what the server says for ShouldTransmit on this entity.
	// Note: This used to be EntityEnteredPVS/EntityRemainedInPVS/EntityLeftPVS.
	virtual void			NotifyShouldTransmit(ShouldTransmitState_t state) = 0;

	// In 90% of the cases, you should hook OnPreDataChanged/OnDataChanged instead of 
	// PreDataUpdate/PostDataUpdate.

	// The DataChanged events are only called once per frame whereas Pre/PostDataUpdate
	// are called once per packet (and sometimes multiple times per frame).

	virtual void			OnPreDataChanged(DataUpdateType_t updateType) = 0;
	virtual void			OnDataChanged(DataUpdateType_t updateType) = 0;

	// Called when data is being updated across the network.
	// Only low-level entities should need to know about these.
	virtual void			PreDataUpdate(DataUpdateType_t updateType) = 0;
	virtual void			PostDataUpdate(DataUpdateType_t updateType) = 0;

	// Objects become dormant on the client if they leave the PVS on the server.
	virtual bool			IsDormant(void) = 0;

	// Ent Index is the server handle used to reference this entity.
	// If the index is < 0, that indicates the entity is not known to the server
	virtual int				entindex(void) const = 0;

	// Server to client entity message received
	virtual void			ReceiveMessage(int classID, bf_read &msg) = 0;

	// Get the base pointer to the networked data that GetClientClass->m_pRecvTable starts at.
	// (This is usually just the "this" pointer).
	virtual void*			GetDataTableBasePtr() = 0;

	// Tells the entity that it's about to be destroyed due to the client receiving
	// an uncompressed update that's caused it to destroy all entities & recreate them.
	virtual void			SetDestroyedOnRecreateEntities(void) = 0;

	virtual void			OnDataUnchangedInPVS() = 0;
};
*/