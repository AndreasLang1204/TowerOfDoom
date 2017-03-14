#include "stdafx.h"

#include "ArtificialCharacterControllerInstance.h"

using namespace ToD;
using namespace ToD::Components::CharacterControllers;

ArtificialCharacterControllerInstance::ArtificialCharacterControllerInstance(GameObject* l_owner)
: ACharacterControllerInstance(l_owner)
{
}

ReferenceType::RuntimeType ArtificialCharacterControllerInstance::GetRuntimeType() const
{
	return "ToD::Components::CharacterControllers::ArtificialCharacterControllerInstance";
}

void ArtificialCharacterControllerInstance::Process(const Time l_gameTime)
{
	SetAction(CharacterControllerAction::EndTurn);
}
