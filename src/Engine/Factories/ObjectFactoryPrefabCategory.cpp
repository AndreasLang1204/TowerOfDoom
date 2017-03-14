#include "stdafx.h"

#include "ObjectFactoryPrefabCategory.h"

using namespace ToD;
using namespace ToD::Components;

int Enumeration<ObjectFactoryPrefabCategory>::s_nextIndex;

EnumerationDefinition__(ObjectFactoryPrefabCategory, AbilityDeclaration)
EnumerationDefinition__(ObjectFactoryPrefabCategory, RoleDeclaration)

void Enumeration<ObjectFactoryPrefabCategory>::Initialize()
{
	Create();

	Add(ObjectFactoryPrefabCategory::AbilityDeclaration);
	Add(ObjectFactoryPrefabCategory::RoleDeclaration);
}

string ObjectFactoryPrefabCategory::RuntimeType()
{
	return "ToD::Factories::ObjectFactoryPrefabCategory";
}
