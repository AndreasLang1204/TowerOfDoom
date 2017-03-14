#include "stdafx.h"

#include "RenderablePriority.h"

using namespace ToD;
using namespace ToD::Components;

int Enumeration<RenderablePriority>::s_nextIndex;

EnumerationDefinition__(RenderablePriority, None)
EnumerationDefinition__(RenderablePriority, Background)
EnumerationDefinition__(RenderablePriority, BackgroundDecoration)
EnumerationDefinition__(RenderablePriority, Object)
EnumerationDefinition__(RenderablePriority, Foreground)
EnumerationDefinition__(RenderablePriority, HUD)
EnumerationDefinition__(RenderablePriority, GUI)

void Enumeration<RenderablePriority>::Initialize()
{
	Create();

	Add(RenderablePriority::None);
	Add(RenderablePriority::Background);
	Add(RenderablePriority::BackgroundDecoration);
	Add(RenderablePriority::Object);
	Add(RenderablePriority::Foreground);
	Add(RenderablePriority::HUD);
	Add(RenderablePriority::GUI);
}

string RenderablePriority::RuntimeType()
{
	return "ToD::Components::RenderablePriority";
}
