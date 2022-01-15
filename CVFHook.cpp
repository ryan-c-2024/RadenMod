#include "stdafx.h"
#include "CVFHook.h"


CVFHook::CVFHook(void* ppVMT) //Note: pVMT should simply be an interface with no dereferencing or typecasting required
{

	m_ppOldVMT = static_cast<void**>(ppVMT);

	if (!m_ppOldVMT)
		return;

	m_pVMT = *reinterpret_cast<uintptr_t**>(m_ppOldVMT);

	CalculateVMTSize();
	ReplaceVMTPointer();
}

void CVFHook::HookFunc(int index, void* newfunction)
{
	if (index >= m_iNumVMTFuncs)
		return;
	m_pNewVMT[index] = reinterpret_cast<uintptr_t>(newfunction);
}

void CVFHook::UnhookFunc(int index)
{
	m_pNewVMT[index] = m_pVMT[index];
}

bool CVFHook::CalculateVMTSize()
{
	if (!m_pVMT)
		return false;

	m_iNumVMTFuncs = 0;

	while (m_pVMT[m_iNumVMTFuncs])
	{
		m_iNumVMTFuncs++;
	} 

	return true;
}

bool CVFHook::ReplaceVMTPointer()
{
	if (m_iNumVMTFuncs == 0)
		return false;

	m_pNewVMT = new uintptr_t[m_iNumVMTFuncs];
	memcpy(m_pNewVMT, m_pVMT, m_iNumVMTFuncs * 4);
	*m_ppOldVMT = m_pNewVMT;

	return true;
}

CVFHook::~CVFHook()
{
	*m_ppOldVMT = m_pVMT;
	delete m_pNewVMT;
}
