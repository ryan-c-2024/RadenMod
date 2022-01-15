#pragma once
class Color;

class ConMsg
{
private:
	typedef void(*MsgFn) (char* msg, ...);
	typedef void(*ColorMsgFn) (const Color& clr, const char* pMsg, ...);
public:
	ConMsg();

	MsgFn Msg = nullptr;
	ColorMsgFn ColorMsg = nullptr;

};

namespace Misc
{
	extern ConMsg con;
}
