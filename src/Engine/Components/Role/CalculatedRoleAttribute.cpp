#include "stdafx.h"

#include "CalculatedRoleAttribute.h"
#include "CharacterRole.h"

using namespace ToD;
using namespace ToD::Components::Role;

CalculatedRoleAttribute::CalculatedRoleAttribute(CharacterRole* l_owner, const string l_attributeName, const int l_levelModifiere, const int l_baseValue, const bool l_canBeBelowBase)
: ARoleAttribute(l_owner, l_attributeName)
, m_modValue(l_levelModifiere)
, m_baseValue(l_baseValue)
, m_canBeBelowBase(l_canBeBelowBase)
{
	UpdateMaxValue();
	m_currentValue = m_maxValue;
}

CalculatedRoleAttribute::~CalculatedRoleAttribute()
{
}

ReferenceType::RuntimeType CalculatedRoleAttribute::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType CalculatedRoleAttribute::RuntimeType()
{
	return "ToD::Components::Role::CalculatedRoleAttribute";
}

int CalculatedRoleAttribute::GetMaxValue() const
{
	return m_maxValue;
}

int CalculatedRoleAttribute::GetCurrentValue()
{
	return m_currentValue;
}

void CalculatedRoleAttribute::ModCurrentValue(const int l_modValue)
{
	m_currentValue += l_modValue;

	if (m_canBeBelowBase)
	{
		if (m_currentValue < 1)
		{
			// ToDo
			// Raise attribute <= 0 event
		}
	}
	else
	{
		if (m_currentValue < m_baseValue)
		{
			m_currentValue = m_baseValue;
		}
	}
}

void CalculatedRoleAttribute::UpdateMaxValue()
{
	m_maxValue = (m_owner->GetLevel() * m_modValue) + m_baseValue;
	LOG(INFO) << "Role: " << m_owner->GetName() << " --- max. value of Attribute: " << m_name << " updated!";

	// ToDo
	// raise attribute max value changed event
}
