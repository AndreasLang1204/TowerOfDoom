#include "stdafx.h"

#include "GameObject.h"

#include "GameObjectTag.h"

using namespace ToD;

GameObject::GameObject(const string l_name, initializer_list<GameObjectTag::EntryPtr> l_tags)
: Activateable()
, m_components()
, m_componentPtrs()
, m_tags(l_tags)
{
	m_name = l_name + to_string(GetRuntimeID());

	LOG(INFO) << "Game object " << GetName() << " was created.";
}

GameObject::~GameObject()
{
	for (auto component : m_componentPtrs)
	{
		delete component;
	}

	LOG(INFO) << "Game object " << GetName() << " was destroyed.";
}

ReferenceType::RuntimeType GameObject::GetRuntimeType() const
{
	return "ToD::GameObject";
}

string GameObject::GetName() const
{
	return m_name;
}

Vector2f GameObject::GetPosition() const 
{
	return m_position;
}

void GameObject::Activate1()
{
	Activateable::Activate1();

	for (auto pair : m_components)
	{
		for (auto component : pair.second)
		{
			component->Activate1();
		}
	}
}

void GameObject::Activate2()
{
	Activateable::Activate2();

	for (auto pair : m_components)
	{
		for (auto component : pair.second)
		{
			component->Activate2();
		}
	}
}

void GameObject::Deactivate1()
{
	Activateable::Deactivate1();

	for (auto pair : m_components)
	{
		for (auto component : pair.second)
		{
			component->Deactivate1();
		}
	}
}

void GameObject::Deactivate2()
{
	Activateable::Deactivate2();

	for (auto pair : m_components)
	{
		for (auto component : pair.second)
		{
			component->Deactivate2();
		}
	}
}

bool GameObject::HasTag(GameObjectTag::EntryPtr l_tag) const
{
	return find(m_tags.begin(), m_tags.end(), l_tag) != m_tags.end();
}

bool GameObject::HasAnyTag(initializer_list<GameObjectTag::EntryPtr> l_tags) const
{
	for (auto tag : l_tags)
	{
		if (HasTag(tag))
		{
			return true;
		}
	}

	return false;
}

void GameObject::AddTag(GameObjectTag::EntryPtr l_tag)
{
	if (!HasTag(l_tag))
	{
		m_tags.push_back(l_tag);
	}
}

void GameObject::RemoveTag(GameObjectTag::EntryPtr l_tag)
{
	if (HasTag(l_tag))
	{
		m_tags.erase(find(m_tags.begin(), m_tags.end(), l_tag));
	}
}

void GameObject::Move(Vector2f l_offset)
{
	m_position += l_offset;
}

GameObject::Iterator GameObject::begin()
{
	return m_componentPtrs.begin();
}

GameObject::Iterator GameObject::end()
{
	return m_componentPtrs.end();
}

void GameObject::AddComponent(AGameComponent* l_component)
{
	m_components[l_component->GetRuntimeType()].push_back(l_component);
	m_componentPtrs.push_back(l_component);
}
