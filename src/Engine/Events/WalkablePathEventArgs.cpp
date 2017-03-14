#include "stdafx.h"

#include "WalkablePathEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

WalkablePathEventArgs::WalkablePathEventArgs(const WalkablePath l_path, MapLayerCellInfo* l_target)
: EventArgs()
, m_path(l_path)
, m_target(l_target)
{
}

ReferenceType::RuntimeType WalkablePathEventArgs::GetRuntimeType() const
{
	return "ToD::Events::WalkablePathEventArgs";
}

const WalkablePathEventArgs::WalkablePath& WalkablePathEventArgs::GetPath() const
{
	return m_path;
}

MapLayerCellInfo* WalkablePathEventArgs::GetTarget() const
{
	return m_target;
}
