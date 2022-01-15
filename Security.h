#pragma once
#include <string>

class Security
{
public:
	Security();
private:
	//Check if computer is in authorized HWID list
	bool IsAuthorizedComputer();
	//Compute the computers HWID
	void ComputeHWID();
	//Deny access to cheat
	void DenyAccess();
	//Array into uintptr but doesn't actually concatenate
	uintptr_t ToValue(int inputArray[]);
	std::string m_computerHWID;
public:
	//Check if the computer's hwid is in the trusted list. If it isn't, deny access.
	__forceinline void RunCheck()
	{
		if (!IsAuthorizedComputer())
		{
			DenyAccess();
		}
	}
};