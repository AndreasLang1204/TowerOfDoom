#include "stdafx.h"

#include "MouseEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

MouseEventArgs::MouseEventArgs(const Vector2f l_position)
: EventArgs()
, m_position(l_position)
{
}

ReferenceType::RuntimeType MouseEventArgs::GetRuntimeType() const
{
	return "ToD::Events::MouseMovedEventArgs";
}

Vector2f MouseEventArgs::GetPosition() const
{
	return m_position;
}
