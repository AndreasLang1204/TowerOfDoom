#include "stdafx.h"

#include "GridCursorRenderable.h"

#include "../Events/EventArgs.h"
#include "../Events/GridCursorEventArgs.h"
#include "../Events/EventInvoker.h"
#include "../Game/Game.h"
#include "../Managers/EventBus.h"

using namespace ToD::Components;
using namespace ToD::Managers;

GridCursorRenderable::GridCursorRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, Texture* l_texture)
: Renderable(l_owner, l_renderPriority)
, m_cursor()
, m_isVisible(false)
{
	m_cursor.setTexture(*l_texture);
	m_cursor.setTextureRect(IntRect(0, 0, 16, 16));
}

ReferenceType::RuntimeType GridCursorRenderable::GetRuntimeType() const
{
	return "ToD::Components::GridCursorRenderable";
}

void GridCursorRenderable::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::GridCursorUpdated) += new EventInvoker<GridCursorRenderable, GridCursorEventArgs>(this, &GridCursorRenderable::OnGridCursorUpdated);
}

void GridCursorRenderable::Activate2()
{
	Activateable::Activate2();
}

void GridCursorRenderable::Deactivate1()
{
	Activateable::Deactivate1();
}

void GridCursorRenderable::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::GridCursorUpdated) -= new EventInvoker<GridCursorRenderable, GridCursorEventArgs>(this, &GridCursorRenderable::OnGridCursorUpdated);
}

void GridCursorRenderable::Process(const Time l_gameTime)
{
	if (m_isVisible)
	{
		Get<Game::Shared>()->GetRenderWindow().draw(m_cursor);
	}
}

void GridCursorRenderable::OnGridCursorUpdated(GridCursorEventArgs* l_args)
{
	m_cursor.setPosition(l_args->GetPosition());
	m_isVisible = l_args->GetIsVisible();
}
