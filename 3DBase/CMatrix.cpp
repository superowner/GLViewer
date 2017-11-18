#include "CMatrix.h"

using namespace Base3D;

CMatrix3d::CMatrix3d()
{
}

CMatrix4d::CMatrix4d()
{
	Identity();
}

void CMatrix4d::Identity()
{
	mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = 0;
	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = 0;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;
}

CMatrix4d CMatrix4d::Transpose()
{
	CMatrix4d m;
	for (int ii = 0; ii < 4; ++ii)
	{
		for (int jj = 0; jj < 4; ++jj)
		{
			m.mat[ii][jj] = mat[jj][ii];
		}
	}

	return m;
}

CMatrix4d	CMatrix4d::operator*(const CMatrix4d& rhs)
{
	CMatrix4d	matRet;

	for (int ii = 0; ii < 4; ++ii)
	{
		for (int jj = 0; jj < 4; ++jj)
		{
			matRet.mat[ii][jj] = 
				  mat[ii][0] * rhs.mat[0][jj]
				+ mat[ii][1] * rhs.mat[1][jj]
				+ mat[ii][2] * rhs.mat[2][jj]
				+ mat[ii][3] * rhs.mat[3][jj];
		}
	}

	return matRet;
}

CVector4d	CMatrix4d::operator*(const CVector4d& rhs)
{
	CVector4d	vecRet;

	vecRet.x = mat[0][0] * rhs.x + mat[0][1] * rhs.y + mat[0][2] * rhs.z + mat[0][3] * rhs.w;
	vecRet.y = mat[1][0] * rhs.x + mat[1][1] * rhs.y + mat[1][2] * rhs.z + mat[1][3] * rhs.w;
	vecRet.z = mat[2][0] * rhs.x + mat[2][1] * rhs.y + mat[2][2] * rhs.z + mat[2][3] * rhs.w;
	vecRet.w = mat[3][0] * rhs.x + mat[3][1] * rhs.y + mat[3][2] * rhs.z + mat[3][3] * rhs.w;

	return vecRet;
}