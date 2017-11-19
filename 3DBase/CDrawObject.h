#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CBaseDrawObject.h"
#include "CVector.h"

#include <vector>

namespace Base3D
{
	class MY3DBASE_API CDrawObject : public CBaseDrawObject
	{
	private:
		std::vector<CVector3d>	m_Vertex;
		std::vector<CVector3d>	m_Normal;
		std::vector<CVector4d>	m_Color;
	};
};