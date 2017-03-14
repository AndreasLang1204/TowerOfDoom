#include "stdafx.h"

#include "GameObjectEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

GameObjectEventArgs::GameObjectEventArgs(GameObject* l_object)
: EventArgs()
, m_object(l_object)
{
}

ReferenceType::RuntimeType GameObjectEventArgs::GetRuntimeType() const
{
	return "ToD::Events::GameObjectEventArgs";
}

GameObject* GameObjectEventArgs::GetGameObject() const
{
	return m_object;
}
