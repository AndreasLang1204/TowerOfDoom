#include "stdafx.h"

#include "GameStateUpdateResult.h"

using namespace ToD;
using namespace ToD::States;

int Enumeration<GameStateUpdateResult>::s_nextIndex;

EnumerationDefinition__(GameStateUpdateResult, KeepState)
EnumerationDefinition__(GameStateUpdateResult, NextState)
EnumerationDefinition__(GameStateUpdateResult, CloseState)

void Enumeration<GameStateUpdateResult>::Initialize()
{
	Create();

	Add(GameStateUpdateResult::KeepState);
	Add(GameStateUpdateResult::NextState);
	Add(GameStateUpdateResult::CloseState);
}

string GameStateUpdateResult::RuntimeType()
{
	return "ToD::States::GameStateUpdateResult";
}
