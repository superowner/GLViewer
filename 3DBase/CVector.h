#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

namespace Base3D
{
	// This class is exported from the 3DBase.dll
	class MY3DBASE_API CVector3d {
	public:
		CVector3d();
		CVector3d(double x, double y, double z);
		CVector3d(const CVector3d& v);

		CVector3d&	operator+=(const CVector3d& rhs);
		CVector3d&	operator-=(const CVector3d& rhs);
		CVector3d&	operator*=(double dVal);
		CVector3d&	operator*=(const CVector3d& rhs);
		CVector3d	operator*(const CVector3d& rhs);
		CVector3d	operator^(const CVector3d& rhs);

		double	Len();
		double	Normalize();

		double x, y, z;
	};

	// This class is exported from the 3DBase.dll
	class MY3DBASE_API CVector4d {
	public:
		CVector4d();

		double x, y, z, w;
	};
};