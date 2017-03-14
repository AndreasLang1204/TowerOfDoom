#include "stdafx.h"

#include "GridCursorEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

GridCursorEventArgs::GridCursorEventArgs(const Vector2f l_position, const bool l_isVisible)
: EventArgs()
, m_position(l_position)
, m_isVisible(l_isVisible)
{
}

ReferenceType::RuntimeType GridCursorEventArgs::GetRuntimeType() const
{
	return "ToD::Events::GridCursorEventArgs";
}

Vector2f GridCursorEventArgs::GetPosition() const
{
	return m_position;
}

bool GridCursorEventArgs::GetIsVisible() const
{
	return m_isVisible;
}
