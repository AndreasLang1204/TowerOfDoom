#include "stdafx.h"

#include "TurnSystemRoundState.h"

using namespace ToD;
using namespace ToD::Components;

int Enumeration<TurnSystemRoundState>::s_nextIndex;

EnumerationDefinition__(TurnSystemRoundState, Staring)
EnumerationDefinition__(TurnSystemRoundState, ChangeCharacter)
EnumerationDefinition__(TurnSystemRoundState, Waiting)
EnumerationDefinition__(TurnSystemRoundState, Ending)

void Enumeration<TurnSystemRoundState>::Initialize()
{
	Create();

	Add(TurnSystemRoundState::Staring);
	Add(TurnSystemRoundState::ChangeCharacter);
	Add(TurnSystemRoundState::Waiting);
	Add(TurnSystemRoundState::Ending);
}

string TurnSystemRoundState::RuntimeType()
{
	return "ToD::Components::TurnSystemRoundState";
}
