#pragma once

namespace Util
{
	template <typename T>
	inline T CallVirtualFunction(void* baseclass, int index) //Pass the class' this pointer			
	{
		/*
		THIS DOESN'T WORK... TRIED MULTIPLE INDEXES AND INDEXES I KNEW WERE CORRECT
		EVEN TRIED MULTIPLE WAYS TO CALL THE VFUNC WITH THE RIGHT INDEXES TO NO AVAIL.
		COPYPASTING OFF OF THE INTERNET USING KNOWN WORKING SOURCES DIDN'T WORK EITHER

		?????
		*/

		/*
		FIXED AS OF 7/31/17: THE ISSUE RESULTED FROM ME USING CallVirtualFunction in virtual class funcs
		off of a class pointer. The issue was the virtual specifier on the function which made it call 
		through the pointer VMT (which wasn't aligned because I was using CallVirtualFunction) and thus fail.
		*/

		/*
		Remember: Nullsub functions in IDA count as functions in that they have an index.
		Also, make sure to make the function typedefs __thiscall and pass the this pointer as the first parameter.
		*/
		
		uintptr_t** pVMT = (uintptr_t**)baseclass;
		uintptr_t* VMT = *pVMT;
		uintptr_t dwAddress = VMT[index];
		return reinterpret_cast<T>(dwAddress);
	}
}