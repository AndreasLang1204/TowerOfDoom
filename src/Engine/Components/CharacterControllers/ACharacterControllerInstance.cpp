#include "stdafx.h"

#include "ACharacterControllerInstance.h"

using namespace ToD;
using namespace ToD::Components::CharacterControllers;

ACharacterControllerInstance::ACharacterControllerInstance(GameObject* l_owner)
: AGameComponent(l_owner, GameComponentType::TurnSystemCharacterController)
, m_action(CharacterControllerAction::None)
{
}

CharacterControllerAction::EntryPtr ACharacterControllerInstance::GetAction() const
{
	return m_action;
}

void ACharacterControllerInstance::SetAction(CharacterControllerAction::EntryPtr l_value)
{
	m_action = l_value;
}
