#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CVector.h"

namespace Base3D
{
	// This class is exported from the 3DBase.dll
	class MY3DBASE_API CMatrix3d {
	public:
		CMatrix3d();
		// TODO: add your methods here.
	};

	// This class is exported from the 3DBase.dll
	class MY3DBASE_API CMatrix4d {
	public:
		CMatrix4d();

		CMatrix4d	operator*(const CMatrix4d& rhs);
		CVector4d	operator*(const CVector4d& rhs);
		
		void Identity();
		CMatrix4d Transpose();

		double mat[4][4];
	};
};