#include "stdafx.h"

#include "RequestWalkableAreaEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

RequestWalkableAreaEventArgs::RequestWalkableAreaEventArgs(GameObject* l_object, const int l_movementRange)
: GameObjectEventArgs(l_object)
, m_movementRange(l_movementRange)
{
}

ReferenceType::RuntimeType RequestWalkableAreaEventArgs::GetRuntimeType() const
{
	return "ToD::Events::RequestWalkableAreaEventArgs";
}

Value::Unit RequestWalkableAreaEventArgs::GetMovementRange() const
{
	return m_movementRange;
}
