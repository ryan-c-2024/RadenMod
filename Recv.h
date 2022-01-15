#pragma once
#pragma once

class RecvTable;
class ArrayLengthRecvProxyFn;
class CRecvProxyData;
class DVariant;
typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

enum SendPropType
{
	DPT_INT,
	DPT_FLOAT,
	DPT_VECTOR,
	DPT_STRING,
	DPT_ARRAY,
	DPT_DATATABLE,
};

class RecvProp
{
public:
	// This info comes from the receive data table.
	const char              *m_pVarName;
	SendPropType			m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;

	bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.

												// Extra data that certain special property types bind to the property here.
	const void *m_pExtraData;

	// If this is an array (DPT_Array).
	RecvProp				*m_pArrayProp;
	void*	m_ArrayLengthProxy;

	void*			m_ProxyFn;
	void*	m_DataTableProxyFn;	// For RDT_DataTable.

	RecvTable				*m_pDataTable;		// For RDT_DataTable.
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char				*m_pParentArrayPropName;

	RecvVarProxyFn			GetProxyFn() const;
	void	SetProxyFn(RecvVarProxyFn fn);
};

class DVariant
{
public:
	union
	{
		float	m_Float;
		int		m_Int;
		const char	*m_pString;
		void	*m_pData;	// For DataTables.
		float	m_Vector[3];
	};
	SendPropType m_Type;
};

class CRecvProxyData
{
public:
	const RecvProp	*m_pRecvProp;		// The property it's receiving.

	DVariant		m_Value;			// The value given to you to store.

	int				m_iElement;			// Which array element you're getting.

	int				m_ObjectID;			// The object being referred to.
};

class RecvProp;
class CRecvDecoder;

struct RecvTable
{

	typedef RecvProp	PropType;

	// Properties described in a table.
	RecvProp		*m_pProps;
	int				m_nProps;

	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children
	// will have their own decoders that include props for all their children).
	CRecvDecoder	*m_pDecoder;

	const char		*m_pNetTableName;	// The name matched between client and server.

	bool			m_bInitialized;
	bool			m_bInMainList;
};

inline RecvVarProxyFn RecvProp::GetProxyFn() const
{
	return (RecvVarProxyFn)m_ProxyFn;
}

inline void RecvProp::SetProxyFn(RecvVarProxyFn fn)
{
	m_ProxyFn = fn;
}

