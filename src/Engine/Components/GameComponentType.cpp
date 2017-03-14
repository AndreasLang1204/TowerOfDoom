#include "stdafx.h"

#include "GameComponentType.h"

using namespace ToD;
using namespace ToD::Components;

int Enumeration<GameComponentType>::s_nextIndex;

EnumerationDefinition__(GameComponentType, None)
EnumerationDefinition__(GameComponentType, Render)
EnumerationDefinition__(GameComponentType, TurnSystemRoundState)
EnumerationDefinition__(GameComponentType, TurnSystemCharacterController)
EnumerationDefinition__(GameComponentType, TurnSystemCharacterState)
EnumerationDefinition__(GameComponentType, Camera)
EnumerationDefinition__(GameComponentType, Transition)
EnumerationDefinition__(GameComponentType, GameObjectManagerIntegration)
EnumerationDefinition__(GameComponentType, InputManagerIntegration)
EnumerationDefinition__(GameComponentType, GameStateManagerIntegration)

void Enumeration<GameComponentType>::Initialize()
{
	Create();

	Add(GameComponentType::None);
	Add(GameComponentType::Render);
	Add(GameComponentType::TurnSystemRoundState);
	Add(GameComponentType::TurnSystemCharacterController);
	Add(GameComponentType::TurnSystemCharacterState);
	Add(GameComponentType::Camera);
	Add(GameComponentType::Transition);
	Add(GameComponentType::GameObjectManagerIntegration);
	Add(GameComponentType::InputManagerIntegration);
	Add(GameComponentType::GameStateManagerIntegration);
}

string GameComponentType::RuntimeType()
{
	return "ToD::Components::GameComponentType";
}
