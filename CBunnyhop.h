#pragma once

class CBunnyhop
{
public:
	void Run();
	bool m_bunnyHopping;
private:
	void DoAutoStrafe();
	void JumpIfOnGround();
};

namespace GMisc
{
	extern CBunnyhop bhop;
}
