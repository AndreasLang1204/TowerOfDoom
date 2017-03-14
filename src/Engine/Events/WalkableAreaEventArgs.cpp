#include "stdafx.h"

#include "WalkableAreaEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

WalkableAreaEventArgs::WalkableAreaEventArgs(const WalkableArea l_area)
: EventArgs()
, m_area(l_area)
{
}

ReferenceType::RuntimeType WalkableAreaEventArgs::GetRuntimeType() const
{
	return "ToD::Events::WalkableAreaEventArgs";
}

const WalkableAreaEventArgs::WalkableArea& WalkableAreaEventArgs::GetArea() const
{
	return m_area;
}
