#include "stdafx.h"

#include "GridCursorLogic.h"

#include "../Events/EventInvoker.h"
#include "../Events/EventArgs.h"
#include "../Events/GameMapEventArgs.h"
#include "../Events/GridCursorClickedEventArgs.h"
#include "../Events/GridCursorEventArgs.h"
#include "../Events/MouseEventArgs.h"
#include "../Game/Game.h"
#include "../Managers/EventBus.h"
#include "../Managers/InputManager.h"

using namespace ToD::Components;
using namespace ToD::Managers;

GridCursorLogic::GridCursorLogic(GameObject* l_owner)
: AGameComponent(l_owner, GameComponentType::Transition)
, m_position()
, m_gridX()
, m_gridY()
, m_isVisible(false)
, m_tileSize()
{
}

ReferenceType::RuntimeType GridCursorLogic::GetRuntimeType() const
{
	return "ToD::Components::GridCursorLogic";
}

void GridCursorLogic::SetIsVisible(const bool l_value)
{
	m_isVisible = l_value;
	Get<Game::Shared>()->GetRenderWindow().setMouseCursorVisible(!l_value);
}

void GridCursorLogic::Activate1()
{
	Activateable::Activate1();

	SetIsVisible(true);
	
	Get<EventBus>().Get(EventType::GameMapLoaded) += new EventInvoker<GridCursorLogic, GameMapEventArgs>(this, &GridCursorLogic::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::MouseMoved) += new EventInvoker<GridCursorLogic, MouseEventArgs>(this, &GridCursorLogic::OnMouseMoved);
	Get<EventBus>().Get(EventType::GuiElementEntering) += new EventInvoker<GridCursorLogic, EventArgs>(this, &GridCursorLogic::OnGuiElementEntering);
	Get<EventBus>().Get(EventType::GuiElementLeaving) += new EventInvoker<GridCursorLogic, EventArgs>(this, &GridCursorLogic::OnGuiElementLeaving);
}

void GridCursorLogic::Activate2()
{
	Activateable::Activate2();
}

void GridCursorLogic::Deactivate1()
{
	Activateable::Deactivate1();
}

void GridCursorLogic::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::GameMapLoaded) -= new EventInvoker<GridCursorLogic, GameMapEventArgs>(this, &GridCursorLogic::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::MouseMoved) -= new EventInvoker<GridCursorLogic, MouseEventArgs>(this, &GridCursorLogic::OnMouseMoved);
	Get<EventBus>().Get(EventType::GuiElementEntering) -= new EventInvoker<GridCursorLogic, EventArgs>(this, &GridCursorLogic::OnGuiElementEntering);
	Get<EventBus>().Get(EventType::GuiElementLeaving) -= new EventInvoker<GridCursorLogic, EventArgs>(this, &GridCursorLogic::OnGuiElementLeaving);
	
	SetIsVisible(false);
}

void GridCursorLogic::Process(const Time l_gameTime)
{
	if (!m_isVisible)
	{
		return;
	}

	if (Get<InputManager>().IsMouseButtonPressed(Mouse::Button::Left))
	{
		Get<EventBus>().Raise(EventType::GridCursorClicked, new GridCursorClickedEventArgs(m_position, m_isVisible, Mouse::Button::Left));
	}
	else if (Get<InputManager>().IsMouseButtonPressed(Mouse::Button::Right))
	{
		Get<EventBus>().Raise(EventType::GridCursorClicked, new GridCursorClickedEventArgs(m_position, m_isVisible, Mouse::Button::Right));
	}
}

void GridCursorLogic::OnGameMapLoaded(GameMapEventArgs* l_args)
{
	m_tileSize = l_args->GetTileSize();
}

void GridCursorLogic::OnMouseMoved(MouseEventArgs* l_args)
{
	if (m_tileSize.x == 0 || m_tileSize.y == 0)
	{
		return;
	}

	m_position = l_args->GetPosition();

	auto xf = floor(m_position.x / m_tileSize.x) * m_tileSize.x;
	auto yf = floor(m_position.y / m_tileSize.y) * m_tileSize.y;

	auto x = static_cast<int>(xf);
	auto y = static_cast<int>(yf);

	if (x != m_gridX || y  != m_gridY)
	{
		Get<EventBus>().Raise(EventType::GridCursorUpdated, new GridCursorEventArgs({ xf, yf }, m_isVisible));
	}

	m_gridX = x;
	m_gridY = y;
}

void GridCursorLogic::OnGuiElementEntering(EventArgs* l_args)
{
	SetIsVisible(false);
}

void GridCursorLogic::OnGuiElementLeaving(EventArgs* l_args)
{
	SetIsVisible(true);
}
