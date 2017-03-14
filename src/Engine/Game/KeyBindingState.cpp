#include "stdafx.h"

#include "KeyBindingState.h"

using namespace ToD;

int Enumeration<KeyBindingState>::s_nextIndex;

EnumerationDefinition__(KeyBindingState, IsPressed)
EnumerationDefinition__(KeyBindingState, WasPressed)
EnumerationDefinition__(KeyBindingState, IsReleased)
EnumerationDefinition__(KeyBindingState, WasReleased)

void Enumeration<KeyBindingState>::Initialize()
{
	Create();

	Add(KeyBindingState::IsPressed);
	Add(KeyBindingState::WasPressed);
	Add(KeyBindingState::IsReleased);
	Add(KeyBindingState::WasReleased);
}

string KeyBindingState::RuntimeType()
{
	return "ToD::KeyBindingState";
}
