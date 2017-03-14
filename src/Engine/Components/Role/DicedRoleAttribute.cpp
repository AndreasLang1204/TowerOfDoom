#include "stdafx.h"

#include "DicedRoleAttribute.h"

#include "CalculatedRoleAttribute.h"
#include "CharacterRole.h"

#include "../Game/Randomizer.h"

using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;

DicedRoleAttribute::DicedRoleAttribute(CharacterRole* l_owner, const string l_attributeName, const string l_modifyingAttributeName, const float l_attributeModifier)
: ARoleAttribute(l_owner, l_attributeName)
, m_attributeModifier(l_attributeModifier)
, m_lastValidValue(0)
{
	m_modifyingAttribute = m_owner->GetMainAttribute(l_modifyingAttributeName);

	if (m_modifyingAttribute == nullptr)
	{
		throw exception(string("Role: " + m_owner->GetName() + " has no attribute: " + l_modifyingAttributeName).c_str());
	}
}

DicedRoleAttribute::DicedRoleAttribute(CharacterRole* l_owner, const string l_attributeName, CalculatedRoleAttribute* l_modifyingAttribute, const float l_attributeModifier)
: ARoleAttribute(l_owner, l_attributeName)
, m_attributeModifier(l_attributeModifier)
, m_lastValidValue(0)
{
	if (l_modifyingAttribute == nullptr || 
		l_modifyingAttribute->GetRole() != m_owner)
	{
		throw exception(string("modifyingAttribute must be a valid attribute of the same role").c_str());
	}
}

DicedRoleAttribute::~DicedRoleAttribute()
{
	m_modifyingAttribute = nullptr;
}

ReferenceType::RuntimeType DicedRoleAttribute::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType DicedRoleAttribute::RuntimeType()
{
	return "ToD::Components::Role::DicedRoleAttribute";
}

int DicedRoleAttribute::GetCurrentValue()
{
	m_lastValidValue = Get<Randomizer>().Random(1, static_cast<int>(m_modifyingAttribute->GetCurrentValue() * m_attributeModifier));
	return m_lastValidValue;
}

int DicedRoleAttribute::GetLastValidValue() const
{
	return m_lastValidValue;
}
