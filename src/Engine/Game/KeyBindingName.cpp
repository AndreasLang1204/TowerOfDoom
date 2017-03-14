#include "stdafx.h"

#include "KeyBindingName.h"

using namespace ToD;

int Enumeration<KeyBindingName>::s_nextIndex;

EnumerationDefinition__(KeyBindingName, None)
EnumerationDefinition__(KeyBindingName, Accept)
EnumerationDefinition__(KeyBindingName, Abort)
EnumerationDefinition__(KeyBindingName, ScrollDown)
EnumerationDefinition__(KeyBindingName, ScrollUp)
EnumerationDefinition__(KeyBindingName, HotkeyAbility1)
EnumerationDefinition__(KeyBindingName, HotkeyAbility2)
EnumerationDefinition__(KeyBindingName, HotkeyAbility3)
EnumerationDefinition__(KeyBindingName, MoveUp)
EnumerationDefinition__(KeyBindingName, MoveDown)
EnumerationDefinition__(KeyBindingName, MoveLeft)
EnumerationDefinition__(KeyBindingName, MoveRight)

void Enumeration<KeyBindingName>::Initialize()
{
	Create();

	Add(KeyBindingName::None);
	Add(KeyBindingName::Accept);
	Add(KeyBindingName::Abort);
	Add(KeyBindingName::ScrollDown);
	Add(KeyBindingName::ScrollUp);
	Add(KeyBindingName::HotkeyAbility1);
	Add(KeyBindingName::HotkeyAbility2);
	Add(KeyBindingName::HotkeyAbility3);
	Add(KeyBindingName::MoveUp);
	Add(KeyBindingName::MoveDown);
	Add(KeyBindingName::MoveLeft);
	Add(KeyBindingName::MoveRight);
}

string KeyBindingName::RuntimeType()
{
	return "ToD::KeyBindingName";
}
