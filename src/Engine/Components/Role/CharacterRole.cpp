#include "stdafx.h"

#include "CharacterRole.h"

using namespace ToD::Components::Role;

CharacterRole::CharacterRole(GameObject* l_owner, const string l_name, const int l_level, initializer_list<CreatureTypeTag::EntryPtr> l_types)
: AGameComponent(l_owner, GameComponentType::TurnSystemCharacterController)
, m_name(l_name)
, m_level(l_level)
{
}

CharacterRole::~CharacterRole()
{
	for (auto attribute : m_mainAttributes)
	{
		delete attribute.second;
	}

	m_mainAttributes.clear();

	for (auto attribute : m_helpAttributes)
	{
		delete attribute.second;
	}

	m_helpAttributes.clear();
}

ReferenceType::RuntimeType CharacterRole::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType CharacterRole::RuntimeType()
{
	return "ToD::Components::Role::CharacterRole";
}

string CharacterRole::GetName() const
{
	return m_name;
}

int CharacterRole::GetLevel() const
{
	return m_level;
}

void CharacterRole::AddMainAttribute(CalculatedRoleAttribute* l_attribute)
{
	if (m_mainAttributes.find(l_attribute->GetName()) == m_mainAttributes.end())
	{
		m_mainAttributes.insert({ l_attribute->GetName(), l_attribute });
	}
}

void CharacterRole::AddHelpAttribute(DicedRoleAttribute* l_attribute)
{
	if (m_helpAttributes.find(l_attribute->GetName()) == m_helpAttributes.end())
	{
		m_helpAttributes.insert({ l_attribute->GetName(), l_attribute });
	}
}

CalculatedRoleAttribute* CharacterRole::GetMainAttribute(const string l_attributeName)
{
	if (m_mainAttributes.find(l_attributeName) != m_mainAttributes.end())
	{
		return m_mainAttributes[l_attributeName];
	}

	return nullptr;
}

DicedRoleAttribute* CharacterRole::GetHelpAttribute(const string l_attributeName)
{
	if (m_helpAttributes.find(l_attributeName) != m_helpAttributes.end())
	{
		return m_helpAttributes[l_attributeName];
	}

	return nullptr;
}

bool CharacterRole::HasCreatureType(CreatureTypeTag::EntryPtr l_creatureType) const
{
	return false;
}

bool CharacterRole::HasAnyCreatureType(initializer_list<CreatureTypeTag::EntryPtr> l_creatureTypes) const
{
	return false;
}

void CharacterRole::AddCreatureType(CreatureTypeTag::EntryPtr l_creatureType)
{
	if (find(m_creatureTypes.begin(), m_creatureTypes.end(), l_creatureType) == m_creatureTypes.end() )
	{
		m_creatureTypes.push_back(l_creatureType);
	}
}

void CharacterRole::RemoveCreatureType(CreatureTypeTag::EntryPtr l_creatureType)
{
	auto itr = find(m_creatureTypes.begin(), m_creatureTypes.end(), l_creatureType);
	if (itr != m_creatureTypes.end())
	{
		m_creatureTypes.erase(itr);
	}
}

void CharacterRole::Activate1()
{
	Activateable::Activate1();
}

void CharacterRole::Activate2()
{
	Activateable::Activate2();
}

void CharacterRole::Deactivate1()
{
	Activateable::Deactivate1();
}

void CharacterRole::Deactivate2()
{
	Activateable::Deactivate2();
}

void CharacterRole::Process(const Time l_gameTime)
{
}
