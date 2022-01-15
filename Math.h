#pragma once
class Vector;
class QAngle;

namespace Math
{
	void SinCos(float radians, float *sine, float *cosine);
	void VectorAngles(const Vector& forward, QAngle &angles);
	void AngleVectors(const QAngle &angles, Vector *forward, Vector *right, Vector *up);
	float GetFovDistance(Vector vecLocalPlayerPosition, Vector vecEnemyPosition, QAngle angLocalPlayer);
	float GetFovDistance(const QAngle& viewAngle, const QAngle& aimAngle);
}
