#include "CCamera.h"

using namespace Base3D;

CCamera::CCamera()
	: m_nProjectionType(None), m_nWndWidth(0), m_nWndHeight(0)
{
}

CCamera::CCamera(int nWndWidth, int nWndHeight)
	: m_nWndWidth(nWndWidth), m_nWndHeight(nWndHeight)
{

}

CCamera::CCamera(int nWndWidth, int nWndHeight, const CVector3d & pos, const CVector3d & target, const CVector3d & up)
	: m_Pos(pos), m_Target(target), m_Up(up), m_nWndWidth(nWndWidth), m_nWndHeight(nWndHeight)
{
}
