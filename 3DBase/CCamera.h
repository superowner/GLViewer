#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

namespace Base3D
{
	// This class is exported from the 3DBase.dll
	class MY3DBASE_API CCamera {
	public:
		CCamera();
		// TODO: add your methods here.
	};
};