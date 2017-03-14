#include "stdafx.h"

#include "PathRenderable.h"

#include "../Game/Constants.h"
#include "../Game/Functions.h"
#include "../Game/Game.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameMapEventArgs.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;
using namespace ToD::Events;

PathRenderable::PathRenderable(GameObject* l_owner)
: Renderable(l_owner, RenderablePriority::HUD)
, m_shape()
, m_path()
{
	m_shape.setFillColor(Constants::Visual::WalkableArea);
}

ReferenceType::RuntimeType PathRenderable::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType PathRenderable::RuntimeType()
{
	return "ToD::Components::PathRenderable";
}

void PathRenderable::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::GameMapLoaded) += new EventInvoker<PathRenderable, GameMapEventArgs>(this, &PathRenderable::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::TurnSystemCharacterWalkablePathUpdated) += new EventInvoker<PathRenderable, WalkablePathEventArgs>(this, &PathRenderable::OnTurnSystemCharacterWalkablePathUpdated);
}

void PathRenderable::Activate2()
{
	Activateable::Activate2();
}

void PathRenderable::Deactivate1()
{
	Activateable::Deactivate1();
}

void PathRenderable::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::GameMapLoaded) -= new EventInvoker<PathRenderable, GameMapEventArgs>(this, &PathRenderable::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::TurnSystemCharacterWalkablePathUpdated) -= new EventInvoker<PathRenderable, WalkablePathEventArgs>(this, &PathRenderable::OnTurnSystemCharacterWalkablePathUpdated);
}

void PathRenderable::Process(const Time l_gameTime)
{
	for (auto cell : m_path)
	{
		m_shape.setPosition(Vector2f(cell->GetMapPosition().x * 16.f, cell->GetMapPosition().y * 16.f));
		Get<Game::Shared>()->GetRenderWindow().draw(m_shape);
	}
}

void PathRenderable::OnGameMapLoaded(GameMapEventArgs* l_args)
{
	m_shape.setSize(Functions::ToVector2f(l_args->GetTileSize()));
}

void PathRenderable::OnTurnSystemCharacterWalkablePathUpdated(WalkablePathEventArgs* l_args)
{
	m_path = l_args->GetPath();
}
