#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CTransform.h"

#include <Eigen/Dense>

namespace Base3D
{
	class MY3DBASE_API CPositionTransform : public CTransform
	{
	public:
		CPositionTransform();

		void		SetPosition(const Eigen::Vector3d& pos) { m_Position = pos; }
		Eigen::Vector3d	GetPosition() { return m_Position; }

		void		SetScale(const Eigen::Vector3d& scale) { m_Scale = scale; }
		Eigen::Vector3d	GetScale() { return m_Scale; }

		void		SetRotate(const Eigen::Vector3d& rotate) { m_Rotate = rotate; }
		Eigen::Vector3d	GetRotate() { return m_Rotate; }

	private:
		Eigen::Vector3d	m_Position;
		Eigen::Vector3d	m_Scale;
		Eigen::Vector3d	m_Rotate;
	};
}