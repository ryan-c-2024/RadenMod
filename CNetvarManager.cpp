#include "stdafx.h"
#include "CNetvarManager.h"
#include "Global Interfaces.h"
#include "Recv.h"
#include "ClientClass.h"
#include "ConMsg.h"
#include "Options.h"
#include "CMisc.h"

/*

TODO: ADD NETVAR PROXYING

*/

void CNetvarManager::Init()
{
	ClientClass* pClientClass = IFace::baseclient->GetAllClasses();

	if (!pClientClass)
		return;

	while (pClientClass)
	{
		m_RecvTables.push_back(pClientClass->m_pRecvTable);
		pClientClass = pClientClass->m_pNext;
	}

	SetupProxies();
}

void CNetvarManager::SetupProxies()
{
	AddProxy("DT_CSPlayer", "m_flFlashMaxAlpha", &CMisc::ChangeFlashAlpha);
}

uintptr_t CNetvarManager::GetNetvarOffset(const char* tableName, const char* netvarName)
{
	GetRecvProp(tableName, netvarName);
	return m_dwCumulativeOffset;
}

RecvTable* CNetvarManager::GetRecvTable(const char* tableName)
{
	for (RecvTable* m : m_RecvTables)
	{
		if (!strcmp(tableName, m->m_pNetTableName))
		{
			return m;
		}
	}
	return nullptr;
}

int CNetvarManager::GetNumberOfProps(const char* tableName)
{
	RecvTable* pTable = GetRecvTable(tableName);
	return pTable->m_nProps;
}

RecvProp* CNetvarManager::GetRecvProp(const char* tableName, const char* propName)
{
	m_dwCumulativeOffset = 0;
	RecvTable* pTable = GetRecvTable(tableName);

	if (!pTable)
		return nullptr;

	return GetRecvProp(pTable, propName);
}

RecvProp* CNetvarManager::GetRecvProp(RecvTable* pTable, const char* propName)
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		RecvProp* pProp = &(pTable->m_pProps[i]);

		if (!pProp)
			continue;

		if (IsBadCodePtr((FARPROC)pProp->m_pVarName) || isdigit(pProp->m_pVarName[0]))
			continue;

		if (!strcmp(pProp->m_pVarName, "baseclass"))
			continue;

		if (!strcmp(pProp->m_pVarName, propName)) //crash upon 2nd iteration of loop (when i = 1) because pProp is off by ~12 bytes and points to junk
		{
			m_dwCumulativeOffset += pProp->m_Offset;
			return pProp;
		}

		RecvTable* pTableOfProp = pProp->m_pDataTable;

		if (pTableOfProp && pTableOfProp->m_nProps > 0)
		{
			//m_dwCumulativeOffset += pProp->m_Offset;
			GetRecvProp(pTableOfProp, propName);
		}
	}
	return 0;
}

void CNetvarManager::PrintTableName(std::string tableName)
{
	std::string toPrint = tableName + "\n";
	ConMsg console;
	console.Msg((char*)toPrint.c_str());
}

void CNetvarManager::DumpTables()
{
	if (!Options::NetvarManager::bDumpDataTables)
		return;
	for (RecvTable* m : m_RecvTables)
	{
		if (!HasSubTables(m))
			continue;
	
		std::string baseTableName(m->m_pNetTableName);
		baseTableName = "==== " + baseTableName + " ====\n";
		PrintTableName(baseTableName);
		PrintSubTables(m);
	}
}

void CNetvarManager::PrintSubTables(RecvTable* pTable) //fix this
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		RecvProp* pProp = &(pTable->m_pProps[i]);

		if (!pProp)
			continue;

		if (IsBadCodePtr((FARPROC)pProp->m_pVarName) || isdigit(pProp->m_pVarName[0]))
			continue;

		if (!strcmp(pProp->m_pVarName, "baseclass"))
			continue;

		RecvTable* pTableOfProp = pProp->m_pDataTable;

		if (pTableOfProp && pTableOfProp->m_nProps > 0 && (char)pTableOfProp->m_pNetTableName[0] == 'D')
		{
			//m_dwCumulativeOffset += pProp->m_Offset;
			PrintTableName(pTableOfProp->m_pNetTableName);
			PrintSubTables(pTableOfProp);
		}
	}
}

//inefficient and really bad because i cycle through the props twice  (once here, once printing subtables)
bool CNetvarManager::HasSubTables(RecvTable* pTable) 
{
	for (int i = 0; i < pTable->m_nProps; i++)
	{
		RecvProp* pProp = &(pTable->m_pProps[i]);

		if (!pProp)
			continue;

		if (IsBadCodePtr((FARPROC)pProp->m_pVarName) || isdigit(pProp->m_pVarName[0]))
			continue;

		if (!strcmp(pProp->m_pVarName, "baseclass"))
			continue;

		RecvTable* pTableOfProp = pProp->m_pDataTable;

		if (pTableOfProp && pTableOfProp->m_nProps > 0 && (char)pTableOfProp->m_pNetTableName[0] == 'D')
		{
			return true;
		}
	}
	return false;
}

void CNetvarManager::AddProxy(const char* tableName, const char* netvarName, RecvVarProxyFn proxyFunction)
{
	RecvProp* prop = GetRecvProp(tableName, netvarName);
	prop->SetProxyFn(proxyFunction);
	m_ProxiedNetvars.push_back(prop); //add to bookkeeping list
}

void CNetvarManager::RemoveProxy(const char* netvarName) //uhh... do you need to take into consideration whether the netvar had a proxy to begin with?
{
	for (RecvProp*& prop : m_ProxiedNetvars)
	{
		if (strcmp(prop->m_pVarName, netvarName) == 0) // if the proxy is found in the list of proxied netvars
		{
			prop->m_ProxyFn = nullptr; //reset proxy <---- hmmm... is this good?
			m_ProxiedNetvars.remove(prop); //remove from the list
		}
	}
}