#pragma once

class CVFHook
{
public:
	//CVFHook() = default;
	CVFHook(void* ppVMT);
	~CVFHook();
	void HookFunc(int index, void* newfunction);
	void UnhookFunc(int index);

	template <typename T>
	T CallOriginalFunc(int index)
	{
		return reinterpret_cast<T>(m_pVMT[index]);
	}

private:
	bool ReplaceVMTPointer();
	bool CalculateVMTSize();

	void** m_ppOldVMT = nullptr;
	uintptr_t* m_pVMT = nullptr;
	void** m_ppNewVMT = nullptr;
	uintptr_t* m_pNewVMT;

	int m_iNumVMTFuncs = 0;
};