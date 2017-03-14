#include "stdafx.h"

#include "AGameState.h"
#include "../Game/GameComponentRegistration.h"
#include "../Game/Game.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/EventBus.h"

using namespace ToD;
using namespace ToD::Managers;

AGameState::AGameState()
: ReferenceType()
, m_objects()
, m_isEntered(false)
{
	Get<EventBus>().Get(EventType::GameObjectDeleting) += new EventInvoker<AGameState, GameObjectEventArgs>(this, &AGameState::OnGameObjectDeleting);
}

AGameState::~AGameState()
{
	Get<EventBus>().Get(EventType::GameObjectDeleting) -= new EventInvoker<AGameState, GameObjectEventArgs>(this, &AGameState::OnGameObjectDeleting);
	
	for (auto pair : m_objects)
	{
		auto object = pair.second;

		Get<GameObjectManager>().RemoveGameObject(object);
	}

	m_objects.clear();
}

const AGameState::ObjectDictionary& AGameState::GetObjects() const
{
	return m_objects;
}

void AGameState::Enter()
{
	auto objects = GameObject::Array();
	for (auto pair : m_objects)
	{
		auto object = pair.second;
		objects.push_back(object);
	}

	Get<GameComponentRegistration>().Register(objects);

	m_isEntered = true;
}

void AGameState::Exit()
{
	auto objects = GameObject::Array();
	for (auto pair : m_objects)
	{
		auto object = pair.second;
		objects.push_back(object);
	}

	Get<GameComponentRegistration>().Deregister(objects);

	Get<Game::Shared>()->UseDefaultView();

	m_isEntered = false;
}

void AGameState::AddObject(GameObject* l_object)
{
	Get<GameObjectManager>().RegisterGameObject(l_object);

	m_objects[l_object->GetRuntimeID()] = l_object;
}

void AGameState::OnGameObjectDeleting(GameObjectEventArgs* l_args)
{
	auto object = l_args->GetGameObject();
	auto identifier = object->GetRuntimeID();

	if (m_objects.find(identifier) == m_objects.end())
	{
		return;
	}

	m_objects.erase(identifier);
}
