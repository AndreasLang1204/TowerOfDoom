#include "stdafx.h"

#include "RequestWalkablePathEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

RequestWalkablePathEventArgs::RequestWalkablePathEventArgs(GameObject* l_object, const Value::Unit l_movementRange, const Vector2i l_targetCellPosition)
: RequestWalkableAreaEventArgs(l_object, l_movementRange)
, m_targetCellPosition(l_targetCellPosition)
{
}

ReferenceType::RuntimeType RequestWalkablePathEventArgs::GetRuntimeType() const
{
	return "ToD::Events::RequestWalkablePathEventArgs";
}

Vector2i RequestWalkablePathEventArgs::GetTargetCellPosition() const
{
	return m_targetCellPosition;
}
