#include "stdafx.h"

#include "ACharacterControllerCommand.h"

using namespace ToD::Components::CharacterControllers::ControllerCommands;

ACharacterControllerCommand::ACharacterControllerCommand(ACharacterControllerInstance* l_owner)
: ReferenceType()
, m_owner(l_owner)
{
}

ACharacterControllerInstance* ACharacterControllerCommand::GetOwner() const
{
	return m_owner;
}
