#include "stdafx.h"

#include "TurnSystemCharacterState.h"

using namespace ToD;
using namespace ToD::Components;

int Enumeration<TurnSystemCharacterState>::s_nextIndex;

EnumerationDefinition__(TurnSystemCharacterState, Inactive)
EnumerationDefinition__(TurnSystemCharacterState, Starting)
EnumerationDefinition__(TurnSystemCharacterState, RequestWalkableArea)
EnumerationDefinition__(TurnSystemCharacterState, Idle)
EnumerationDefinition__(TurnSystemCharacterState, ActionMove)
EnumerationDefinition__(TurnSystemCharacterState, ActionRole)
EnumerationDefinition__(TurnSystemCharacterState, Ending)

void Enumeration<TurnSystemCharacterState>::Initialize()
{
	Create();

	Add(TurnSystemCharacterState::Inactive);
	Add(TurnSystemCharacterState::Starting);
	Add(TurnSystemCharacterState::RequestWalkableArea);
	Add(TurnSystemCharacterState::Idle);
	Add(TurnSystemCharacterState::ActionMove);
	Add(TurnSystemCharacterState::ActionRole);
	Add(TurnSystemCharacterState::Ending);
}

string TurnSystemCharacterState::RuntimeType()
{
	return "ToD::Components::TurnSystemCharacterState";
}
