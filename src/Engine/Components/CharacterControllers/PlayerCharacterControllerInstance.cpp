#include "stdafx.h"

#include "PlayerCharacterControllerInstance.h"
#include "../../Managers/ObjectContainer.h"
#include "../../Managers/EventBus.h"
#include "../../Events/EventInvoker.h"
#include "../../Events/GameObjectEventArgs.h"
#include "../../Managers/ResourceManager.h"

using namespace ToD;
using namespace ToD::Components::CharacterControllers;
using namespace ToD::Managers;

PlayerCharacterControllerInstance::PlayerCharacterControllerInstance(GameObject* l_owner)
: ACharacterControllerInstance(l_owner)
{
}

ReferenceType::RuntimeType PlayerCharacterControllerInstance::GetRuntimeType() const
{
	return "ToD::Components::CharacterControllers::PlayerCharacterControllerInstance";
}

void PlayerCharacterControllerInstance::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) += new EventInvoker<PlayerCharacterControllerInstance, GameObjectEventArgs>(this, &PlayerCharacterControllerInstance::OnTurnSystemNextCharacter);
	Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) += new EventInvoker<PlayerCharacterControllerInstance, GameObjectEventArgs>(this, &PlayerCharacterControllerInstance::OnPlayableCharacterDeactivated);
}

void PlayerCharacterControllerInstance::Activate2()
{
	Activateable::Activate2();
}

void PlayerCharacterControllerInstance::Deactivate1()
{
	Activateable::Deactivate1();
}

void PlayerCharacterControllerInstance::Deactivate2()
{
	Activateable::Deactivate2();
}

void PlayerCharacterControllerInstance::Process(const Time l_gameTime)
{
}

void PlayerCharacterControllerInstance::OnGuiEndTurnButtonClicked(EventArgs* l_args)
{
	SetAction(CharacterControllerAction::EndTurn);
}

void PlayerCharacterControllerInstance::OnGuiReturnToMainMenuButtonClicked(EventArgs* l_args)
{
	SetAction(CharacterControllerAction::ReturnToMainMenu);
}

void PlayerCharacterControllerInstance::OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args)
{
	if (l_args->GetGameObject() == GetOwner())
	{
		Get<EventBus>().Get(EventType::TurnSystemNextCharacter) -= new EventInvoker<PlayerCharacterControllerInstance, GameObjectEventArgs>(this, &PlayerCharacterControllerInstance::OnTurnSystemNextCharacter);
		Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) -= new EventInvoker<PlayerCharacterControllerInstance, GameObjectEventArgs>(this, &PlayerCharacterControllerInstance::OnPlayableCharacterDeactivated);
		
		Get<EventBus>().Get(EventType::GuiEndTurnButtonClicked) -= new EventInvoker<PlayerCharacterControllerInstance, EventArgs>(this, &PlayerCharacterControllerInstance::OnGuiEndTurnButtonClicked);
		Get<EventBus>().Get(EventType::GuiReturnToMainMenuButtonClicked) -= new EventInvoker<PlayerCharacterControllerInstance, EventArgs>(this, &PlayerCharacterControllerInstance::OnGuiReturnToMainMenuButtonClicked);

		SetAction(CharacterControllerAction::None);
	}
}

void PlayerCharacterControllerInstance::OnTurnSystemNextCharacter(GameObjectEventArgs* l_args)
{
	if (l_args->GetGameObject() == GetOwner())
	{
		Get<ResourceManager>().PlaySound("IWILLFIGHT_YELL");
		Get<EventBus>().Get(EventType::GuiEndTurnButtonClicked) += new EventInvoker<PlayerCharacterControllerInstance, EventArgs>(this, &PlayerCharacterControllerInstance::OnGuiEndTurnButtonClicked);
		Get<EventBus>().Get(EventType::GuiReturnToMainMenuButtonClicked) += new EventInvoker<PlayerCharacterControllerInstance, EventArgs>(this, &PlayerCharacterControllerInstance::OnGuiReturnToMainMenuButtonClicked);
	}
	else
	{
		Get<EventBus>().Get(EventType::GuiEndTurnButtonClicked) -= new EventInvoker<PlayerCharacterControllerInstance, EventArgs>(this, &PlayerCharacterControllerInstance::OnGuiEndTurnButtonClicked);
		Get<EventBus>().Get(EventType::GuiReturnToMainMenuButtonClicked) -= new EventInvoker<PlayerCharacterControllerInstance, EventArgs>(this, &PlayerCharacterControllerInstance::OnGuiReturnToMainMenuButtonClicked);

		SetAction(CharacterControllerAction::None);
	}
}
