#pragma once
#include "IBaseClientDLL.h"
#include <vector>
#include <list>

class RecvTable;
class RecvProp;
class CRecvProxyData;
typedef void(*RecvVarProxyFn)(const CRecvProxyData *pData, void *pStruct, void *pOut);

class CNetvarManager
{
public:
	void Init();
	uintptr_t GetNetvarOffset(const char* tableName, const char* netvarName);
	int GetNumberOfProps(const char* tableName);
	void DumpTables();
private:
	std::vector<RecvTable*> m_RecvTables;

	//Recordkeeping for all current proxied netvar RecvProps. This way I don't have to find it again when removing proxy.
	//It's a list because I don't need indexing and I want to be able to quickly delete elements
	std::list<RecvProp*> m_ProxiedNetvars; 
	RecvTable* GetRecvTable(const char* tableName);
	RecvProp* GetRecvProp(const char* tableName, const char* propName);
	RecvProp* GetRecvProp(RecvTable* pTable, const char* propName);
	void PrintTableName(std::string tableName);
	void PrintSubTables(RecvTable* pTable);
	bool HasSubTables(RecvTable* pTable);
	void SetupProxies();
	void AddProxy(const char* tableName, const char* netvarName, RecvVarProxyFn proxyFunction);
	void RemoveProxy(const char* netvarName);

	uintptr_t m_dwCumulativeOffset = 0;
};