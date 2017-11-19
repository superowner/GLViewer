#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CPositionTransform.h"

namespace Base3D
{
	class MY3DBASE_API CBaseDrawObject : public CPositionTransform
	{

	};
}