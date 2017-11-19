#include "stdafx.h"
#include "CVector.h"

using namespace Base3D;

CVector3d::CVector3d()
	: x(0), y(0), z(0)
{
}

CVector3d::CVector3d(double x, double y, double z)
	: x(x), y(y), z(z)
{
}

CVector3d::CVector3d(const CVector3d & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

CVector3d & CVector3d::operator+=(const CVector3d & rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

CVector3d & CVector3d::operator-=(const CVector3d & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

CVector3d & CVector3d::operator*=(double dVal)
{
	x *= dVal;
	y *= dVal;
	z *= dVal;
	return *this;
}

CVector3d& CVector3d::operator*=(const CVector3d& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	z *= rhs.z;
	return *this;
}

CVector3d CVector3d::operator*(const CVector3d & rhs)
{
	return CVector3d(x * rhs.x, y * rhs.y, z * rhs.z);
}

CVector3d CVector3d::operator^(const CVector3d & rhs)
{
	double dXTmp = y * rhs.z - z * rhs.y;
	double dYTmp = z * rhs.x - x * rhs.z;
	double dZTmp = x * rhs.y - y * rhs.x;

	return CVector3d(dXTmp, dYTmp, dZTmp);
}

double CVector3d::Len()
{
	return sqrtl(x * x + y * y + z * z);
}

double CVector3d::Normalize()
{
	double dLen = Len();
	x /= dLen;
	y /= dLen;
	z /= dLen;

	return dLen;
}

CVector4d::CVector4d()
{
}


