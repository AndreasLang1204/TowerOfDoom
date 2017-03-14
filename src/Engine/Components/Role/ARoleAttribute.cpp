#include "stdafx.h"

#include "ARoleAttribute.h"
#include "CharacterRole.h"

using namespace ToD;
using namespace ToD::Components::Role;


ARoleAttribute::ARoleAttribute(CharacterRole* l_owner, const string l_attributeName)
: ReferenceType()
, m_owner(l_owner)
, m_name(l_attributeName)
, m_currentValue(0)
{
}

string ARoleAttribute::GetName() const
{
	return m_name;
}

CharacterRole* ARoleAttribute::GetRole()
{
	return m_owner;
}
