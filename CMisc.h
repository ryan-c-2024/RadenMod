#pragma once

class CRecvProxyData;

class CMisc
{
public:
	void RunAllMisc();

	//proxied so it only updates when alpha resets - more efficient. Thus it does not run in RunAllMisc
	static void ChangeFlashAlpha(const CRecvProxyData* pData, void* pStruct, void* pOut);
private:
	void ChatSpamPositions();
	void ChatSpamJebhook();
	void DoSlowFall();
	void DoFakeLag();
};

namespace GMisc
{
	extern CMisc misc;
}
