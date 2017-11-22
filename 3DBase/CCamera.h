#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include <Eigen/Eigen>

namespace Base3D
{
	class MY3DBASE_API CPerspectiveProjectionInfo
	{
	public:
		CPerspectiveProjectionInfo()
			: m_dFOV(0), m_dWidth(0), m_dHeight(0), m_dNear(0), m_dFar(0)
		{
		}
		CPerspectiveProjectionInfo(double dFOV, double dWidth, double dHeight, double dNear, double dFar)
			: m_dFOV(dFOV), m_dWidth(dWidth), m_dHeight(dHeight), m_dNear(dNear), m_dFar(dFar)
		{
		}

		double	m_dFOV, m_dWidth, m_dHeight, m_dNear, m_dFar;
	};

	class MY3DBASE_API COrthoProjectionInfo
	{
	public:
		COrthoProjectionInfo()
			: m_dLeft(0), m_dRight(0), m_dTop(0), m_dBottom(0), m_dNear(0), m_dFar(0)
		{
		}
		COrthoProjectionInfo(double	dLeft, double dRight, double dTop, double dBottom, double dNear, double dFar)
			: m_dLeft(dLeft), m_dRight(dRight), m_dTop(dTop), m_dBottom(dBottom), m_dNear(dNear), m_dFar(dFar)
		{
		}

		double	m_dLeft, m_dRight, m_dTop, m_dBottom, m_dNear, m_dFar;
	};

	// This class is exported from the 3DBase.dll
	class MY3DBASE_API CCamera {
	public:
		CCamera();
		CCamera(int nWndWidth, int nWndHeight);
		CCamera(int nWndWidth, int nWndHeight, const Eigen::Vector3d& pos, const Eigen::Vector3d& target, const Eigen::Vector3d& up);

		unsigned int	GetWndWidth() { return m_nWndWidth; }
		void			SetWndWidth(unsigned int nWndWidth) { m_nWndWidth = nWndWidth; }
		unsigned int	GetWndHeight() { return m_nWndHeight; }
		void			SetWndHeight(unsigned int nWndHeight) { m_nWndHeight = nWndHeight; }

		Eigen::Vector3d	GetPos() { return m_Pos; }
		void			SetPos(const Eigen::Vector3d& pos) { m_Pos = pos; }
		Eigen::Vector3d	GetTarget() { return m_Target; }
		void			SetTarget(const Eigen::Vector3d& target) { m_Target = target; }
		Eigen::Vector3d	GetUp() { return m_Up; }
		void			SetUp(const Eigen::Vector3d& up) { m_Up = up; }

		enum PROJECTION_TYPE
		{
			None,
			Perspective,
			Ortho,
		};
		PROJECTION_TYPE				GetProjection() { return m_nProjectionType; }
		void						SetProjection(const PROJECTION_TYPE& pt) { m_nProjectionType = pt; }
		CPerspectiveProjectionInfo&	GetPerspectiveProjectionInfo() { return m_PerspectiveProjection; }
		void						SetPerspectiveProjectionInfo(const CPerspectiveProjectionInfo& ppi) { m_PerspectiveProjection = ppi; }
		COrthoProjectionInfo&		GetOrthoProjectionInfo() { return m_OrthoProjection; }
		void						SetOrthoProjectionInfo(const COrthoProjectionInfo& opi) { m_OrthoProjection = opi; }

		Eigen::Matrix4d	GetCameraMatrix();

		const double m_dPI;

	protected:
		Eigen::Matrix4d	GetPerspectiveCameraMatrix();
		Eigen::Matrix4d	GetOrthoCameraMatrix();

	private:
		Eigen::Vector3d	m_Pos;
		Eigen::Vector3d	m_Target;
		Eigen::Vector3d	m_Up;

		unsigned int	m_nWndWidth;
		unsigned int	m_nWndHeight;

		PROJECTION_TYPE	m_nProjectionType;

		CPerspectiveProjectionInfo	m_PerspectiveProjection;
		COrthoProjectionInfo		m_OrthoProjection;

		Eigen::Matrix4d	m_matCamera;
		bool		m_bDirty;
	};
};