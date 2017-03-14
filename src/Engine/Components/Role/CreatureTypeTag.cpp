#include "stdafx.h"

#include "CreatureTypeTag.h"

using namespace ToD::Components::Role;

int Enumeration<CreatureTypeTag>::s_nextIndex;

EnumerationDefinition__(CreatureTypeTag, Human)
EnumerationDefinition__(CreatureTypeTag, Undead)
EnumerationDefinition__(CreatureTypeTag, Humanoid)
EnumerationDefinition__(CreatureTypeTag, Beast)
EnumerationDefinition__(CreatureTypeTag, Elemental)

void Enumeration<CreatureTypeTag>::Initialize()
{
	Create();

	Add(CreatureTypeTag::Human);
	Add(CreatureTypeTag::Undead);
	Add(CreatureTypeTag::Humanoid);
	Add(CreatureTypeTag::Beast);
	Add(CreatureTypeTag::Elemental);
}

string CreatureTypeTag::RuntimeType()
{
	return "ToD::Components::Role::CreatureTypeTag";
}
