#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CVector.h"

namespace Base3D
{
	class CPositionTransform
	{
	public:
		CPositionTransform();

		void		SetPosition(const CVector3d& pos) { m_Position = pos; }
		CVector3d	GetPosition() { return m_Position; }

		void		SetScale(const CVector3d& scale) { m_Scale = scale; }
		CVector3d	GetScale() { return m_Scale; }

		void		SetRotate(const CVector3d& rotate) { m_Rotate = rotate; }
		CVector3d	GetRotate() { return m_Rotate; }

	private:
		CVector3d	m_Position;
		CVector3d	m_Scale;
		CVector3d	m_Rotate;
	};
}