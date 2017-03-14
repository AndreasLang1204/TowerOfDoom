#include "stdafx.h"

#include "GameStateManager.h"

#include "../States/GameStateUpdateResult.h"

using namespace sf;
using namespace std;
using namespace ToD;
using namespace ToD::Managers;
using namespace ToD::States;

GameStateManager::Component::Component(GameObject* l_owner, GameStateManager* l_manager)
: AGameComponent(l_owner, GameComponentType::GameStateManagerIntegration)
, m_manager(l_manager)
{
}

ReferenceType::RuntimeType GameStateManager::Component::GetRuntimeType() const
{
	return "ToD::Managers::GameStateManager::Component";
}

GameStateManager::GameStateManager()
: m_states()
{
}

ReferenceType::RuntimeType GameStateManager::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GameStateManager::RuntimeType()
{
	return "ToD::Managers::GameStateManager";
}

AGameState* GameStateManager::GetCurrentState()
{
	return m_states.top();
}

void GameStateManager::SetInitialState(AGameState* l_state)
{
	if (IsEmpty())
	{
		SetNextState(l_state);
	}
	else
	{
		throw exception("The initial state has already been set.");
	}
}

void GameStateManager::Update(Time l_gameTime)
{
	AGameState* nextState = nullptr;

	auto result = GetCurrentState()->Update(l_gameTime, nextState);

	switch (result->GetValue())
	{
	case GameStateUpdateResult::ValueKeepState:
		return;

	case GameStateUpdateResult::ValueNextState:
		SetNextState(nextState);
		return;

	case GameStateUpdateResult::ValueCloseState:
		CloseCurrentState();
		return;

	default:
		throw exception(string("The game state update result " + result->ToString() + " is not supported.").c_str());
	}
}

bool GameStateManager::IsEmpty() const
{
	return m_states.empty();
}

void GameStateManager::SetNextState(AGameState* l_state)
{
	if (!IsEmpty())
	{
		GetCurrentState()->Exit();
	}

	l_state->Enter();

	m_states.push(move(l_state));
}

void GameStateManager::CloseCurrentState()
{
	GetCurrentState()->Exit();

	delete m_states.top();
	m_states.pop();

	if (!IsEmpty())
	{
		GetCurrentState()->Enter();
	}
}
