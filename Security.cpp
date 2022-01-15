#include "stdafx.h"
#include "Security.h"
#include <Windows.h>
#include <Iphlpapi.h>
#include <set>
#include "Cleanup.h"
#include <memory>
#include <cstdlib>

std::set<std::string> authorizedUsers = { "30-B5-C2-2F-81-7B", "4C-CC-6A-2C-63-F9", "D8-CB-8A-CC-79-EF", 
"2C-4D-54-CF-E2-FC", "1C-1B-0D-74-8C-1C", "4C-60-DE-F5-16-57, A4-34-D9-F5-40-BE" };

Security::Security()
{
	ComputeHWID();
}

void Security::ComputeHWID() //thnx stack overflow
{
	char data[4096];
	ZeroMemory(data, 4096);
	unsigned long len = 0;
	PIP_ADAPTER_INFO pinfo = NULL; 
	char sbuf[20];
	
	GetAdaptersInfo(pinfo, &len); //this call will fail and let us know how much memory is needed (by modifying len)
	pinfo = (PIP_ADAPTER_INFO)malloc(len);
	GetAdaptersInfo(pinfo, &len); //call again this time

	std::string hwid;
	for (int k = 0; k < 5; k++)
	{
		sprintf_s(sbuf, "%02X-", pinfo->Address[k]);
		hwid += sbuf;
	}
	sprintf_s(sbuf, "%02X", pinfo->Address[5]);
	hwid += sbuf;
	
	m_computerHWID = hwid;
	delete pinfo;
}

bool Security::IsAuthorizedComputer()
{
	if (authorizedUsers.find(m_computerHWID) == authorizedUsers.end())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Security::DenyAccess()
{
	FreeLibraryAndExitThread(GMisc::hMyDll, 0);
}

uintptr_t Security::ToValue(int inputArray[])
{
	uintptr_t value = 0;
	for (int i = 0; i < sizeof(inputArray); i++)
	{
		value += inputArray[i];
	}
	return value;
}