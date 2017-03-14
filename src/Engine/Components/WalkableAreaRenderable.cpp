#include "stdafx.h"

#include "WalkableAreaRenderable.h"

#include "../Game/Constants.h"
#include "../Game/Functions.h"
#include "../Game/Game.h"
#include "../Game/GameObject.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameMapEventArgs.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;
using namespace ToD::Events;

WalkableAreaRenderable::WalkableAreaRenderable(GameObject* l_owner)
: Renderable(l_owner, RenderablePriority::HUD)
, m_shape()
, m_walkableArea()
{
	m_shape.setFillColor(Constants::Visual::WalkableArea);
}

ReferenceType::RuntimeType WalkableAreaRenderable::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType WalkableAreaRenderable::RuntimeType()
{
	return "ToD::Components::WalkableAreaRenderable";
}

void WalkableAreaRenderable::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::GameMapLoaded) += new EventInvoker<WalkableAreaRenderable, GameMapEventArgs>(this, &WalkableAreaRenderable::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkableArea) += new EventInvoker<WalkableAreaRenderable, WalkableAreaEventArgs>(this, &WalkableAreaRenderable::OnTurnSystemCharacterResponseWalkableArea);
	Get<EventBus>().Get(EventType::TurnSystemCharacterStartsMoving) += new EventInvoker<WalkableAreaRenderable, GameObjectEventArgs>(this, &WalkableAreaRenderable::OnTurnSystemCharacterStartsMoving);
}

void WalkableAreaRenderable::Activate2()
{
	Activateable::Activate2();
}

void WalkableAreaRenderable::Deactivate1()
{
	Activateable::Deactivate1();
}

void WalkableAreaRenderable::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::GameMapLoaded) -= new EventInvoker<WalkableAreaRenderable, GameMapEventArgs>(this, &WalkableAreaRenderable::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkableArea) -= new EventInvoker<WalkableAreaRenderable, WalkableAreaEventArgs>(this, &WalkableAreaRenderable::OnTurnSystemCharacterResponseWalkableArea);
	Get<EventBus>().Get(EventType::TurnSystemCharacterStartsMoving) -= new EventInvoker<WalkableAreaRenderable, GameObjectEventArgs>(this, &WalkableAreaRenderable::OnTurnSystemCharacterStartsMoving);
}

void WalkableAreaRenderable::Process(const Time l_gameTime)
{
	for (auto cell : m_walkableArea)
	{
		m_shape.setPosition(Vector2f(cell->GetMapPosition().x * 16.f, cell->GetMapPosition().y * 16.f));
		Get<Game::Shared>()->GetRenderWindow().draw(m_shape);
	}
}

void WalkableAreaRenderable::OnGameMapLoaded(GameMapEventArgs* l_args)
{
	m_shape.setSize(Functions::ToVector2f(l_args->GetTileSize()));
}

void WalkableAreaRenderable::OnTurnSystemCharacterResponseWalkableArea(WalkableAreaEventArgs* l_args)
{
	m_walkableArea = l_args->GetArea();
}

void WalkableAreaRenderable::OnTurnSystemCharacterStartsMoving(GameObjectEventArgs* l_args)
{
	m_walkableArea.clear();
}
