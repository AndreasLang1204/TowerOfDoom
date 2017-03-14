#include "stdafx.h"

#include "CharacterControllerAction.h"

using namespace ToD;
using namespace ToD::Components::CharacterControllers;

int Enumeration<CharacterControllerAction>::s_nextIndex;

EnumerationDefinition__(CharacterControllerAction, None)
EnumerationDefinition__(CharacterControllerAction, ReturnToMainMenu)
EnumerationDefinition__(CharacterControllerAction, EndTurn)

void Enumeration<CharacterControllerAction>::Initialize()
{
	Create();

	Add(CharacterControllerAction::None);
	Add(CharacterControllerAction::ReturnToMainMenu);
	Add(CharacterControllerAction::EndTurn);
}

string CharacterControllerAction::RuntimeType()
{
	return "ToD::Components::CharacterControllers::CharacterControllerAction";
}
