#include "stdafx.h"

#include "Renderable.h"

#include "../Game/GameObject.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;

Renderable::Renderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority)
: AGameComponent(l_owner, GameComponentType::Render)
, m_priority(l_renderPriority)
{
}

RenderablePriority::EntryPtr Renderable::GetPriority() const
{
	return m_priority;
}
