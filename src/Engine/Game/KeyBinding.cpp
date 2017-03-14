#include "stdafx.h"

#include "KeyBinding.h"

using namespace ToD;

KeyBinding::KeyBinding(KeyBindingName::EntryPtr l_name)
: ReferenceType()
, m_keyState(KeyBindingState::WasReleased)
, m_name(l_name)  
{
}
ReferenceType::RuntimeType KeyBinding::GetRuntimeType() const
{
	return "ToD::KeyBinding";
}

KeyBindingName::EntryPtr KeyBinding::GetName() const
{
	return m_name;
}

KeyBindingState::EntryPtr KeyBinding::GetKeyState() const
{
	return m_keyState;
}

void KeyBinding::GotPressed()
{
	if (m_keyState == KeyBindingState::WasReleased ||
		m_keyState == KeyBindingState::IsReleased)
	{
		m_keyState = KeyBindingState::IsPressed;
	}	
	else if(m_keyState == KeyBindingState::IsPressed)
	{
		m_keyState = KeyBindingState::WasPressed;
	}
}

void KeyBinding::GotReleased()
{
	if (m_keyState == KeyBindingState::WasPressed ||
		m_keyState == KeyBindingState::IsPressed)
	{
		m_keyState = KeyBindingState::IsReleased;
	}
	else if (m_keyState == KeyBindingState::IsReleased)
	{
		m_keyState = KeyBindingState::WasReleased;
	}
}
