#include "stdafx.h"

#include "GameObjectManager.h"

#include "EventBus.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Game/GameComponentRegistration.h"

using namespace ToD;
using namespace ToD::Managers;

GameObjectManager::Component::Component(GameObject* l_owner, GameObjectManager* l_manager)
: AGameComponent(l_owner, GameComponentType::GameObjectManagerIntegration)
, m_manager(l_manager)
{
}

ReferenceType::RuntimeType GameObjectManager::Component::GetRuntimeType() const
{
	return "ToD::Managers::GameObjectManager::Component";
}

GameObjectManager::GameObjectManager()
: m_playerObjects()
, m_aiObjects()
, m_otherObjects()
{
}

GameObjectManager::~GameObjectManager()
{
	for (auto pair : m_playerObjects)
	{
		auto object = pair.second;
		RemoveGameObject(object, false);
	}

	for (auto pair : m_aiObjects)
	{
		auto object = pair.second;
		RemoveGameObject(object, false);
	}

	for (auto pair : m_otherObjects)
	{
		auto object = pair.second;
		RemoveGameObject(object, false);
	}
}

ReferenceType::RuntimeType GameObjectManager::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GameObjectManager::RuntimeType()
{
	return "ToD::Managers::GameObjectManager";
}

void GameObjectManager::Update(const Time l_gameTime)
{
	auto deadObjectNames = vector<GameObject*>();

	for (auto& pair : m_playerObjects)
	{
		auto& gameObject = pair.second;
		if (gameObject->HasTag(GameObjectTag::Dead))
		{
			deadObjectNames.push_back(gameObject);
		}
	}

	for (auto& pair : m_aiObjects)
	{
		auto& gameObject = pair.second;
		if (gameObject->HasTag(GameObjectTag::Dead))
		{
			deadObjectNames.push_back(gameObject);
		}
	}

	for (auto& pair : m_otherObjects)
	{
		auto& gameObject = pair.second;
		if (gameObject->HasTag(GameObjectTag::Dead))
		{
			deadObjectNames.push_back(gameObject);
		}
	}

	for (auto name : deadObjectNames)
	{
		RemoveGameObject(name);
	}
}

void GameObjectManager::RegisterGameObject(GameObject* l_gameObject)
{
	auto name = l_gameObject->GetName();

	if (l_gameObject->HasTag(GameObjectTag::Player))
	{
		m_playerObjects[name] = l_gameObject;
	}
	else if (l_gameObject->HasTag(GameObjectTag::Enemy))
	{
		m_aiObjects[name] = l_gameObject;
	}
	else
	{
		m_otherObjects[name] = l_gameObject;
	}
}

void GameObjectManager::RemoveGameObject(GameObject* l_gameObject)
{
	RemoveGameObject(l_gameObject, true);
}

GameObject& GameObjectManager::GetGameObject(GameObjectTag::EntryPtr l_tag)
{
	auto& dictionary = m_otherObjects;

	switch(l_tag->GetValue())
	{
	case GameObjectTag::ValuePlayer:
		dictionary = m_playerObjects;
		break;

	case GameObjectTag::ValueEnemy:
		dictionary = m_aiObjects;
		break;

	default:
		break;
	}

	for (auto pair : dictionary)
	{
		auto object = pair.second;
		if (object->GetIsActivated() && object->HasTag(l_tag))
		{
			return *object;
		}
	}

	throw exception(string("No game object with the tag " + l_tag->ToString() + " is currently available.").c_str());
}

GameObject::Array GameObjectManager::GetGameObjects(vector<GameObjectTag::EntryPtr> l_tags)
{
	auto objects = GameObject::Array();

	for (auto tag : l_tags)
	{
		for (auto pair : m_playerObjects)
		{
			auto object = pair.second;
			if (object->GetIsActivated() && object->HasTag(tag))
			{
				objects.push_back(object);
			}
		}

		for (auto pair : m_aiObjects)
		{
			auto object = pair.second;
			if (object->GetIsActivated() && object->HasTag(tag))
			{
				objects.push_back(object);
			}
		}

		for (auto pair : m_otherObjects)
		{
			auto object = pair.second;
			if (object->GetIsActivated() && object->HasTag(tag))
			{
				objects.push_back(object);
			}
		}
	}

	return objects;
}

void GameObjectManager::RemoveGameObject(GameObject* l_gameObject, bool l_isErased)
{
	auto name = l_gameObject->GetName();

	if (l_isErased)
	{
		m_playerObjects.erase(name);
		m_aiObjects.erase(name);
		m_otherObjects.erase(name);
	}

	Get<EventBus>().Raise(EventType::GameObjectDeleting, new GameObjectEventArgs(l_gameObject));
	Get<GameComponentRegistration>().Deregister({ l_gameObject });
	delete l_gameObject;
}
