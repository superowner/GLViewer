#include "CCamera.h"
#include <limits>
#include <cmath>
#include <cmath>

using namespace Base3D;

CCamera::CCamera()
	: m_nProjectionType(None)
	, m_nWndWidth(0)
	, m_nWndHeight(0)
	, m_bDirty(true)
	, m_dPI(3.14159265358979323846)
{
}

CCamera::CCamera(int nWndWidth, int nWndHeight)
	: m_nWndWidth(nWndWidth)
	, m_nWndHeight(nWndHeight)
	, m_bDirty(true)
	, m_dPI(3.14159265358979323846)
{

}

CCamera::CCamera(int nWndWidth, int nWndHeight, const Eigen::Vector3d & pos, const Eigen::Vector3d & target, const Eigen::Vector3d & up)
	: m_Pos(pos)
	, m_Target(target)
	, m_Up(up)
	, m_nWndWidth(nWndWidth)
	, m_nWndHeight(nWndHeight)
	, m_bDirty(true)
	, m_dPI(3.14159265358979323846)
{
}

Eigen::Matrix4d CCamera::GetCameraMatrix()
{
	if (m_bDirty == false)
	{
		return m_matCamera;
	}

	Eigen::Matrix4d	matRet;
	switch (m_nProjectionType)
	{
	case Perspective:
		m_bDirty = false;
		break;
	case Ortho:
		m_bDirty = false;
		break;
	default:
		break;
	}

	return matRet;

	Eigen::AngleAxisd rotation_vector(3.14 / 4, Eigen::Vector3d(0, 0, 1));     //ÑØ Z ÖáÐý×ª 45 ¶È 
}

Eigen::Matrix4d CCamera::GetPerspectiveCameraMatrix()
{
	if (m_PerspectiveProjection.m_dHeight == 0)
	{
		m_PerspectiveProjection.m_dHeight = UINT_MAX;
	}
	double dAR = m_PerspectiveProjection.m_dWidth / m_PerspectiveProjection.m_dHeight;
	double dRange = m_PerspectiveProjection.m_dNear - m_PerspectiveProjection.m_dFar;
	double dTanHalfFOV = m_PerspectiveProjection.m_dFOV / 2 * m_dPI / 180;

	double dTmp = (-m_PerspectiveProjection.m_dNear - m_PerspectiveProjection.m_dFar) / dRange;
	double dTmp2 = 2.0f * m_PerspectiveProjection.m_dFar * m_PerspectiveProjection.m_dNear / dRange;

	Eigen::Matrix4d mat;

	mat(0, 0) = 1.0f / (dTanHalfFOV * dAR); mat(0, 1) = 0.0f;				mat(0, 2) = 0.0f; mat(0, 3) = 0.0f;
	mat(1, 0) = 0.0f;						mat(1, 1) = 1.0f / dTanHalfFOV; mat(1, 2) = 0.0f; mat(1, 3) = 0.0f;
	mat(2, 0) = 0.0f;						mat(2, 1) = 0.0f;				mat(2, 2) = dTmp; mat(2, 3) = dTmp2;
	mat(3, 0) = 0.0f;						mat(3, 1) = 0.0f;				mat(3, 2) = 1.0f; mat(3, 3) = 0.0f;
	
	return mat;
}

Eigen::Matrix4d CCamera::GetOrthoCameraMatrix()
{
	Eigen::Matrix4d	mat;
	
	double dL = m_OrthoProjection.m_dLeft;
	double dR = m_OrthoProjection.m_dRight;
	double dT = m_OrthoProjection.m_dTop;
	double dB = m_OrthoProjection.m_dBottom;
	double dN = m_OrthoProjection.m_dNear;
	double dF = m_OrthoProjection.m_dFar;

	mat(0, 0) = 2.0f / (dR - dL);	mat(0, 1) = 0.0f;				mat(0, 2) = 0.0f;				mat(0, 3) = -(dR + dL) / (dR - dL);
	mat(1, 0) = 0.0f;				mat(1, 1) = 2.0f / (dT - dB);	mat(1, 2) = 0.0f;				mat(1, 3) = -(dT + dB) / (dT - dB);
	mat(2, 0) = 0.0f;				mat(2, 1) = 0.0f;				mat(2, 2) = 2.0f / (dF - dN);	mat(2, 3) = -(dF + dN) / (dF - dN);
	mat(3, 0) = 0.0f;				mat(3, 1) = 0.0f;				mat(3, 2) = 0.0f;				mat(3, 3) = 1.0f;

	return mat;
}
