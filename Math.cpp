#include "stdafx.h"
#include "Math.h"
#include "Vector.h"
#include "QAngle.h"
#include "mathlib.h"

void Math::SinCos(float radians, float *sine, float *cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}
void Math::VectorAngles(const Vector& forward, QAngle &angles)
{
	float	tmp, yaw, pitch;

	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		if (forward[2] > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else
	{
		yaw = (atan2(forward[1], forward[0]) * 180 / M_PI);
		if (yaw < 0)
			yaw += 360;

		tmp = FastSqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = (atan2(-forward[2], tmp) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}
void Math::AngleVectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up)
{
	float sr, sp, sy, cr, cp, cy;
	SinCos(DEG2RAD(angles.x), &sy, &cy);
	SinCos(DEG2RAD(angles.y), &sp, &cp);
	SinCos(DEG2RAD(angles.z), &sr, &cr);

	if (forward)
	{
		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr*sp*cy + -1 * cr*-sy);
		right->y = (-1 * sr*sp*sy + -1 * cr*cy);
		right->z = -1 * sr*cp;
	}

	if (up)
	{
		up->x = (cr*sp*cy + -sr*-sy);
		up->y = (cr*sp*sy + -sr*cy);
		up->z = cr*cp;
	}
}

float Math::GetFovDistance(Vector vecLocalPlayerPosition, Vector vecEnemyPosition, QAngle angLocalPlayer)
{
	Vector vecForward;
	Math::AngleVectors(angLocalPlayer, &vecForward, nullptr, nullptr);
	Vector vecDelta = vecEnemyPosition - vecLocalPlayerPosition;
	vecDelta.Normalize();
	vecForward.Normalize();

	float flDotProductResult = DotProduct(vecDelta, vecForward);

	if (flDotProductResult < -1.0f)
		flDotProductResult = -1.0f;

	if (flDotProductResult > 1.0f)
		flDotProductResult = 1.0f;

	return RAD2DEG(acos(flDotProductResult));
}
float Math::GetFovDistance(const QAngle& viewAngle, const QAngle& aimAngle)
{

	Vector ang, aim;

	AngleVectors(viewAngle, &aim, 0, 0);
	AngleVectors(aimAngle, &ang, 0, 0);

	return RAD2DEG(acos(aim.Dot(ang) / aim.LengthSqr()));
}