#pragma once
#include "Vector.h"
#include "VMatrix.h"
#include "Global Interfaces.h"

namespace EspMath
{
	inline bool ScreenTransform(const Vector& point, Vector& screen)
	{
		float w;
		const VMatrix& worldToScreen = IFace::engineclient->WorldToScreenMatrix();

		//screen = worldToScreen * point;
		screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3]; //vector transformation by matrix multiplication
		screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
		w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
		//screen.z = 0.0f;

		screen.z = 0.0f;

		bool behind = false;

		if (w < 0.001f)
		{
			behind = true;
			screen.x *= 100000;
			screen.y *= 100000;
		}
		else
		{
			behind = false;
			float invw = 1.0f / w;
			screen.x *= invw;
			screen.y *= invw;
		}

		return behind;
	}

	inline bool WorldToScreen(const Vector& origin, Vector& screen)
	{
		if (!ScreenTransform(origin, screen))
		{
			int iScreenWidth, iScreenHeight;
			IFace::engineclient->GetScreenSize(iScreenWidth, iScreenHeight);
			float x = iScreenWidth / 2;
			float y = iScreenHeight / 2;
			x += 0.5 * screen.x * iScreenWidth + 0.5;
			y -= 0.5 * screen.y * iScreenHeight + 0.5;
			screen.x = x;
			screen.y = y;
			return true;
		}
		return false;
	}
}