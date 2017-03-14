#include "stdafx.h"

#include "TurnSystem.h"

#include "PlayableCharacter.h"
#include "../Game/Constants.h"
#include "../Game/Randomizer.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Managers/EventBus.h"

using namespace ToD::Managers;

TurnSystem::TurnSystem(GameObject * l_owner)
: AGameComponent(l_owner, GameComponentType::TurnSystemRoundState)
, m_combatants()
, m_turnOrder()
, m_currentRoundState(TurnSystemRoundState::Staring)
, m_currentRound(0)
{
}

ReferenceType::RuntimeType TurnSystem::GetRuntimeType() const
{
	return "ToD::Components::TurnSystem";
}

void TurnSystem::Activate1()
{
	Activateable::Activate1();
	
	Get<EventBus>().Get(EventType::PlayableCharacterActivated) += new EventInvoker<TurnSystem, GameObjectEventArgs>(this, &TurnSystem::OnPlayableCharacterActivated);
	Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) += new EventInvoker<TurnSystem, GameObjectEventArgs>(this, &TurnSystem::OnPlayableCharacterDeactivated);
	Get<EventBus>().Get(EventType::TurnSystemCharacterEndsTurn) += new EventInvoker<TurnSystem, EventArgs>(this, &TurnSystem::OnTurnSystemCharacterEndsTurn);
	Get<EventBus>().Get(EventType::TurnSystemShuttingDown) += new EventInvoker<TurnSystem, EventArgs>(this, &TurnSystem::OnTurnSystemShuttingDown);
}

void TurnSystem::Activate2()
{
	Activateable::Activate2();
}

void TurnSystem::Deactivate1()
{
	Activateable::Deactivate1();
}

void TurnSystem::Deactivate2()
{
	Activateable::Deactivate2();
	
	Get<EventBus>().Get(EventType::PlayableCharacterActivated) -= new EventInvoker<TurnSystem, GameObjectEventArgs>(this, &TurnSystem::OnPlayableCharacterActivated);
	Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) -= new EventInvoker<TurnSystem, GameObjectEventArgs>(this, &TurnSystem::OnPlayableCharacterDeactivated);
	Get<EventBus>().Get(EventType::TurnSystemCharacterEndsTurn) -= new EventInvoker<TurnSystem, EventArgs>(this, &TurnSystem::OnTurnSystemCharacterEndsTurn);
	Get<EventBus>().Get(EventType::TurnSystemShuttingDown) -= new EventInvoker<TurnSystem, EventArgs>(this, &TurnSystem::OnTurnSystemShuttingDown);
}

void TurnSystem::Process(const Time l_gameTime)
{
	switch(m_currentRoundState->GetValue())
	{
	case TurnSystemRoundState::ValueStaring:
		StartNextRound();
		break;

	case TurnSystemRoundState::ValueChangeCharacter:
		ChangeCharacter();
		break;

	case TurnSystemRoundState::ValueWaiting:
		break;

	case TurnSystemRoundState::ValueEnding:
		EndCurrentRound();
		break;

	default:
		throw exception(string("The turn system does not support round state " + m_currentRoundState->ToString() + ".").c_str());
	}
}

void TurnSystem::StartNextRound()
{
	m_currentRound++;

	for (auto pair : m_combatants)
	{
		auto combatant = pair.second;
		auto character = combatant->GetComponent<PlayableCharacter>();

		auto initiative = character->GetRole()->GetHelpAttribute(Constants::Attribute::Initiative)->GetCurrentValue();
		auto weight = Get<Randomizer>().Random();

		if (m_turnOrder.find(initiative) == m_turnOrder.end())
		{
			m_turnOrder[initiative][weight] = combatant;
		}
		else
		{
			auto& weights = m_turnOrder[initiative];
			while (weights.find(weight) != weights.end())
			{
				weight = Get<Randomizer>().Random();
			}

			weights[weight] = combatant;
		}
	}

	m_currentRoundState = TurnSystemRoundState::ChangeCharacter;
}

void TurnSystem::ChangeCharacter()
{
	if (m_turnOrder.empty())
	{
		m_currentRoundState = TurnSystemRoundState::Ending;
	}
	else
	{
		auto nextCharacter = (*(*m_turnOrder.begin()).second.begin()).second;
		auto identifier = nextCharacter->GetRuntimeID();

		Get<EventBus>().Raise(EventType::TurnSystemNextCharacter, new GameObjectEventArgs(nextCharacter));
		RemoveCharacter(identifier, false);

		m_currentRoundState = TurnSystemRoundState::Waiting;
	}
}

void TurnSystem::EndCurrentRound()
{
	m_currentRoundState = TurnSystemRoundState::Staring;
}

void TurnSystem::OnPlayableCharacterActivated(GameObjectEventArgs* l_args)
{
	auto object = l_args->GetGameObject();
	auto identifier = object->GetRuntimeID();

	m_combatants[identifier] = object;
}

void TurnSystem::OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args)
{
	auto object = l_args->GetGameObject();

	RemoveCharacter(object->GetRuntimeID(), true);
}

void TurnSystem::OnTurnSystemCharacterEndsTurn(EventArgs* l_args)
{
	m_currentRoundState = TurnSystemRoundState::ChangeCharacter;
}

void TurnSystem::OnTurnSystemShuttingDown(EventArgs* l_args)
{
	m_currentRoundState = TurnSystemRoundState::Waiting;
}

void TurnSystem::RemoveCharacter(const RuntimeID l_identifier, const bool l_eraseCombatant)
{
	if (l_eraseCombatant && m_combatants.find(l_identifier) != m_combatants.end())
	{
		m_combatants.erase(l_identifier);
	}

	for (auto pair1 : m_turnOrder)
	{
		for (auto pair2 : pair1.second)
		{
			auto combantant = pair2.second;
			if (combantant->GetRuntimeID() == l_identifier)
			{
				auto initiative = pair1.first;
				auto weight = pair2.first;

				m_turnOrder[initiative].erase(weight);

				if (m_turnOrder[initiative].empty())
				{
					m_turnOrder.erase(initiative);
				}

				return;
			}
		}
	}
}
