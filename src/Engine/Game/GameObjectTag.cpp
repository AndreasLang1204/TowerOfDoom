#include "stdafx.h"

#include "GameObjectTag.h"

using namespace ToD;

int Enumeration<GameObjectTag>::s_nextIndex;

EnumerationDefinition__(GameObjectTag, Unspecified)
EnumerationDefinition__(GameObjectTag, Player)
EnumerationDefinition__(GameObjectTag, Enemy)
EnumerationDefinition__(GameObjectTag, Dead)
EnumerationDefinition__(GameObjectTag, GUI)
EnumerationDefinition__(GameObjectTag, Map)
EnumerationDefinition__(GameObjectTag, MapObject)
EnumerationDefinition__(GameObjectTag, Trigger)
EnumerationDefinition__(GameObjectTag, Blocking)

void Enumeration<GameObjectTag>::Initialize()
{
	Create();

	Add(GameObjectTag::Unspecified);
	Add(GameObjectTag::Player);
	Add(GameObjectTag::Enemy);
	Add(GameObjectTag::Dead);
	Add(GameObjectTag::GUI);
	Add(GameObjectTag::Map);
	Add(GameObjectTag::MapObject);
	Add(GameObjectTag::Trigger);
	Add(GameObjectTag::Blocking);
}

string GameObjectTag::RuntimeType()
{
	return "ToD::GameObjectTag";
}
