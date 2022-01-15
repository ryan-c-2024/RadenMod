#pragma once

namespace MenuUtil
{
	//checks whether you clicked in within coordinates passed as arguments 
	bool IsBeingClicked(int elementX0, int elementY0, int elementX1, int elementY1);
	//also takes into consideration tick of the click so it doesn't toggle on and off really fast
	bool IsValidClick(int elementX0, int elementY0, int elementX1, int elementY1);
}