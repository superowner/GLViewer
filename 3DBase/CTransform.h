#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

namespace Base3D
{
	class MY3DBASE_API CTransform
	{
	public:
		CTransform() {}
	};
}