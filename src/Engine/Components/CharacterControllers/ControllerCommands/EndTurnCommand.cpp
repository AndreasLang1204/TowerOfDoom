#include "stdafx.h"

#include "EndTurnCommand.h"

#include "../ACharacterControllerInstance.h"
#include "../../../Events/GameObjectEventArgs.h"
#include "../../../Managers/ObjectContainer.h"
#include "../../../Managers/EventBus.h"

using namespace ToD;
using namespace ToD::Events;
using namespace ToD::Managers;
using namespace ToD::Components::CharacterControllers::ControllerCommands;

EndTurnCommand::EndTurnCommand(ACharacterControllerInstance* l_owner)
: ACharacterControllerCommand(l_owner)
{
}

ReferenceType::RuntimeType EndTurnCommand::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType EndTurnCommand::RuntimeType()
{
	return "ToD::Components::CharacterControllers::ControllerCommands::EndTurnCommand";
}

void EndTurnCommand::Execute()
{
	Get<EventBus>().Raise(EventType::TurnSystemCharacterEndsTurn, new GameObjectEventArgs(GetOwner()->GetOwner()));
}
