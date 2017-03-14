#include "stdafx.h"

#include "PlayableCharacter.h"

#include "CharacterControllers/ACharacterControllerInstance.h"
#include "../Game/Constants.h"
#include "../Game/GameObject.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Events/GridCellClickedEventArgs.h"
#include "../Events/RequestWalkableAreaEventArgs.h"
#include "../Events/RequestWalkablePathEventArgs.h"
#include "../Managers/EventBus.h"

using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;
using namespace ToD::Components::Role;

PlayableCharacter::PlayableCharacter(GameObject* l_owner, CharacterRole* l_role)
: AGameComponent(l_owner, GameComponentType::TurnSystemCharacterState)
, m_role(l_role)
, m_controller()
, m_currentCharacterState(TurnSystemCharacterState::Inactive)
, m_walkableArea()
{
}

ReferenceType::RuntimeType PlayableCharacter::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType PlayableCharacter::RuntimeType()
{
	return "ToD::Components::PlayableCharacter";
}

//Value::Unit PlayableCharacter::GetAttribute(const string l_name) const
//{
//	if (l_name == Constants::Attribute::Initiative)
//	{
//		return m_initiative.GetValue();
//	}
//	
//	if (l_name == Constants::Attribute::ActionPoints)
//	{
//		return m_actionPoints.GetValue();
//	}
//
//	if (l_name == Constants::Attribute::HitPoints)
//	{
//		return m_hitPoints.GetValue();
//	}
//
//	throw exception(string("Character " + GetOwner()->GetName() + " has not attribute " + l_name + ".").c_str());
//}

CharacterRole* PlayableCharacter::GetRole() const
{
	return m_role;
}

void PlayableCharacter::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) += new EventInvoker<PlayableCharacter, GameObjectEventArgs>(this, &PlayableCharacter::OnTurnSystemNextCharacter);
}

void PlayableCharacter::Activate2()
{
	Activateable::Activate2();

	Get<EventBus>().Raise(EventType::PlayableCharacterActivated, new GameObjectEventArgs(GetOwner()));

	m_controller = GetOwner()->GetComponent<ACharacterControllerInstance>(true);
}

void PlayableCharacter::Deactivate1()
{
	Activateable::Deactivate1();

	Get<EventBus>().Raise(EventType::PlayableCharacterDeactivated, new GameObjectEventArgs(GetOwner()));
}

void PlayableCharacter::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) -= new EventInvoker<PlayableCharacter, GameObjectEventArgs>(this, &PlayableCharacter::OnTurnSystemNextCharacter);
	
	m_currentCharacterState = TurnSystemCharacterState::Inactive;
	m_controller = nullptr;
}

void PlayableCharacter::Process(const Time l_gameTime)
{
	switch (m_currentCharacterState->GetValue())
	{
	case TurnSystemCharacterState::ValueInactive:
		break;

	case TurnSystemCharacterState::ValueStarting:
		StartCharacterTurn();
		break;

	case TurnSystemCharacterState::ValueRequestWalkableArea:
		RequestWalkableArea();
		break;

	case TurnSystemCharacterState::ValueIdle:
		PollControllerAction();
		break;

	case TurnSystemCharacterState::ValueActionMove:
		break;

	case TurnSystemCharacterState::ValueActionRole:
		break;

	case TurnSystemCharacterState::ValueEnding:
		EndCharacterTurn();
		break;

	default: 
		throw exception(string("The turn system does not support character state " + m_currentCharacterState->ToString() + ".").c_str());
	}
}

void PlayableCharacter::StartCharacterTurn()
{
	m_currentCharacterState = TurnSystemCharacterState::RequestWalkableArea;
}

void PlayableCharacter::RequestWalkableArea()
{
	Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkableArea) += new EventInvoker<PlayableCharacter, WalkableAreaEventArgs>(this, &PlayableCharacter::OnTurnSystemCharacterResponseWalkableArea);
	Get<EventBus>().Raise(EventType::TurnSystemCharacterRequestsWalkableArea, new RequestWalkableAreaEventArgs(GetOwner(), m_role->GetMainAttribute(Constants::Attribute::ActionPoints)->GetCurrentValue()));
	Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkableArea) -= new EventInvoker<PlayableCharacter, WalkableAreaEventArgs>(this, &PlayableCharacter::OnTurnSystemCharacterResponseWalkableArea);
}

void PlayableCharacter::EnterIdleState()
{
	Get<EventBus>().Get(EventType::GridCellClicked) += new EventInvoker<PlayableCharacter, GridCellClickedEventArgs>(this, &PlayableCharacter::OnGridCellClicked);

	m_currentCharacterState = TurnSystemCharacterState::Idle;
}

void PlayableCharacter::PollControllerAction()
{
	if (m_controller == nullptr)
	{
		throw exception(string(GetOwner()->GetName() + " has not character controller instance.").c_str());
	}

	switch(m_controller->GetAction()->GetValue())
	{
	case CharacterControllerAction::ValueNone:
		break;

	case CharacterControllerAction::ValueReturnToMainMenu:
		LeaveIdleState(TurnSystemCharacterState::Inactive);
		Get<EventBus>().Raise(EventType::TurnSystemShuttingDown, new EventArgs());
		break;

	case CharacterControllerAction::ValueEndTurn:
		LeaveIdleState(TurnSystemCharacterState::Ending);
		break;

	default: 
		throw exception(string("The character does not understand action " + m_controller->GetAction()->ToString() + ".").c_str());
	}
}

void PlayableCharacter::LeaveIdleState(TurnSystemCharacterState::EntryPtr l_nextState)
{
	Get<EventBus>().Get(EventType::GridCellClicked) -= new EventInvoker<PlayableCharacter, GridCellClickedEventArgs>(this, &PlayableCharacter::OnGridCellClicked);

	m_currentCharacterState = l_nextState;
}

void PlayableCharacter::EndCharacterTurn()
{
	Get<EventBus>().Raise(EventType::TurnSystemCharacterEndsTurn, new GameObjectEventArgs(GetOwner()));

	m_currentCharacterState = TurnSystemCharacterState::Inactive;
}

void PlayableCharacter::OnTurnSystemNextCharacter(GameObjectEventArgs* l_args)
{
	if (l_args->GetGameObject() == GetOwner())
	{
		m_currentCharacterState = TurnSystemCharacterState::Starting;
	}
}

void PlayableCharacter::OnTurnSystemCharacterResponseWalkableArea(WalkableAreaEventArgs* l_args)
{
	m_walkableArea = l_args->GetArea();

	EnterIdleState();
}

void PlayableCharacter::OnTurnSystemCharacterStartsMoving(GameObjectEventArgs* l_args)
{
	Get<EventBus>().Get(EventType::TurnSystemCharacterEndsMoving) += new EventInvoker<PlayableCharacter, GameObjectEventArgs>(this, &PlayableCharacter::OnTurnSystemCharacterEndsMoving);

	LeaveIdleState(TurnSystemCharacterState::ActionMove);
}

void PlayableCharacter::OnTurnSystemCharacterEndsMoving(GameObjectEventArgs* l_args)
{
	Get<EventBus>().Get(EventType::TurnSystemCharacterEndsMoving) -= new EventInvoker<PlayableCharacter, GameObjectEventArgs>(this, &PlayableCharacter::OnTurnSystemCharacterEndsMoving);
	
	m_currentCharacterState = TurnSystemCharacterState::Starting;
}

// Todo. handle by controller, replace by command (command pattern)
void PlayableCharacter::OnGridCellClicked(GridCellClickedEventArgs* l_args)
{
	if (l_args->GetButton() == Mouse::Button::Right)
	{
		auto cell = l_args->GetCell();
		if (find(m_walkableArea.begin(), m_walkableArea.end(), cell) == m_walkableArea.end())
		{
			return;
		}
		
		Get<EventBus>().Get(EventType::TurnSystemCharacterStartsMoving) += new EventInvoker<PlayableCharacter, GameObjectEventArgs>(this, &PlayableCharacter::OnTurnSystemCharacterStartsMoving);
		Get<EventBus>().Raise(EventType::TurnSystemCharacterRequestsWalkablePath, new RequestWalkablePathEventArgs(GetOwner(), m_role->GetMainAttribute(Constants::Attribute::ActionPoints)->GetCurrentValue(), l_args->GetPosition()));
		Get<EventBus>().Get(EventType::TurnSystemCharacterStartsMoving) -= new EventInvoker<PlayableCharacter, GameObjectEventArgs>(this, &PlayableCharacter::OnTurnSystemCharacterStartsMoving);
	}
	else if(l_args->GetButton() == Mouse::Button::Left)
	{
		// Todo. handle left click
	}
}
