#include "stdafx.h"
#include "VMatrix.h"
#include "matrix3x4.h"

VMatrix& VMatrix::operator=(const VMatrix &mOther)
{
	m[0][0] = mOther.m[0][0];
	m[0][1] = mOther.m[0][1];
	m[0][2] = mOther.m[0][2];
	m[0][3] = mOther.m[0][3];

	m[1][0] = mOther.m[1][0];
	m[1][1] = mOther.m[1][1];
	m[1][2] = mOther.m[1][2];
	m[1][3] = mOther.m[1][3];

	m[2][0] = mOther.m[2][0];
	m[2][1] = mOther.m[2][1];
	m[2][2] = mOther.m[2][2];
	m[2][3] = mOther.m[2][3];

	m[3][0] = mOther.m[3][0];
	m[3][1] = mOther.m[3][1];
	m[3][2] = mOther.m[3][2];
	m[3][3] = mOther.m[3][3];

	return *this;
}

void VMatrix::Init(const matrix3x4_t& matrix3x4)
{
	memcpy(m, matrix3x4.Base(), sizeof(matrix3x4_t));

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}
