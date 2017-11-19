#pragma once

#ifdef MY3DBASE_EXPORTS
#define MY3DBASE_API __declspec(dllexport)
#else
#define MY3DBASE_API __declspec(dllimport)
#endif

#include "CBaseDrawObject.h"

#include <string>
#include <vector>
#include <memory>

namespace Base3D
{
	class MY3DBASE_API CDrawGroup : public CBaseDrawObject
	{
	public:
		CDrawGroup();

	private:
		std::string	m_strName;
		std::vector<std::shared_ptr<CBaseDrawObject>>	m_vChildren;
	};
}