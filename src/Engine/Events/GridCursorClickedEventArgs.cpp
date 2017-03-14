#include "stdafx.h"

#include "GridCursorClickedEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

GridCursorClickedEventArgs::GridCursorClickedEventArgs(const Vector2f l_position, const bool l_isVisible, const Mouse::Button l_button)
: GridCursorEventArgs(l_position, l_isVisible)
, m_button(l_button)
{
}

ReferenceType::RuntimeType GridCursorClickedEventArgs::GetRuntimeType() const
{
	return "ToD::Events::GridCursorClickedEventArgs";
}

Mouse::Button GridCursorClickedEventArgs::GetButton() const
{
	return m_button;
}
