#include "stdafx.h"

#include "Activateable.h"

using namespace ToD;

Activateable::Activateable()
: ReferenceType()
, m_isActivated(false)
{
}

bool Activateable::GetIsActivated() const
{
	return m_isActivated;
}

void Activateable::Activate1()
{
	m_isActivated = true;
}

void Activateable::Activate2()
{
}

void Activateable::Deactivate1()
{
	m_isActivated = false;
}

void Activateable::Deactivate2()
{
}
