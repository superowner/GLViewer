#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CBaseDrawObject.h"

#include <vector>
#include <Eigen/Eigen>

namespace Base3D
{
	class MY3DBASE_API CDrawObject : public CBaseDrawObject
	{
	private:
		std::vector<Eigen::Vector3d>	m_Vertex;
		std::vector<Eigen::Vector3d>	m_Normal;
		std::vector<Eigen::Vector3d>	m_Color;
	};
};