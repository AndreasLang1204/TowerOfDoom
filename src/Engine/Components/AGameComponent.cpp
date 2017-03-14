#include "stdafx.h"

#include "AGameComponent.h"

#include "GameComponentType.h"
#include "../Game/GameObject.h"

using namespace ToD;
using namespace ToD::Components;

AGameComponent::AGameComponent(GameObject* l_owner, const GameComponentType::EntryPtr l_type)
: Activateable()
, m_owner(l_owner)
, m_type(l_type)
{
}

GameObject* AGameComponent::GetOwner() const
{
	return m_owner;
}

GameComponentType::EntryPtr AGameComponent::GetType() const
{
	return m_type;
}
