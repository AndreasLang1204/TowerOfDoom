#include "stdafx.h"

#include "MapLayerRenderable.h"

#include "../Events/GameMapEventArgs.h"
#include "../Game/Game.h"
#include "../Game/GameObject.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;

bool MapLayerRenderable::TileComparerX::operator()(const Sprite* lhs, const Sprite* rhs) const
{
	return lhs->getPosition().x < rhs->getPosition().x;
}

bool MapLayerRenderable::TileComparerY::operator()(const Sprite* lhs, const Sprite* rhs) const
{
	return lhs->getPosition().y < rhs->getPosition().y;
}

MapLayerRenderable::MapLayerRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, const Vector2i l_size, const Vector2i l_tileSize)
: Renderable(l_owner, l_renderPriority)
, m_size(l_size)
, m_tileSize(l_tileSize)
, m_tiles()
, m_tilesX()
, m_tilesY()
{
}

MapLayerRenderable::~MapLayerRenderable()
{
	for (auto sprite : m_tiles)
	{
		delete sprite;
	}
}

ReferenceType::RuntimeType MapLayerRenderable::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType MapLayerRenderable::RuntimeType()
{
	return "ToD::Components::MapLayerRenderable";
}

Vector2i MapLayerRenderable::GetTileSize() const
{
	return m_tileSize;
}

Vector2i MapLayerRenderable::GetSize() const
{
	return m_size;
}

void MapLayerRenderable::Activate1()
{
	Activateable::Activate1();
}

void MapLayerRenderable::Activate2()
{
	Activateable::Activate2();

	Get<EventBus>().Raise(EventType::GameMapLoaded, new GameMapEventArgs(this));
}

void MapLayerRenderable::Deactivate1()
{
	Activateable::Deactivate1();

	Get<EventBus>().Raise(EventType::GameMapUnloaded, new GameMapEventArgs(this));
}

void MapLayerRenderable::Deactivate2()
{
	Activateable::Deactivate2();
}

void MapLayerRenderable::Process(const Time l_gameTime)
{
	auto& renderTarget = Get<Game::Shared>()->GetRenderWindow();
	auto& view = renderTarget.getView();

	auto viewSize = view.getSize() * 1.1f;
	auto viewSizeHalf = viewSize / 2.f;
	auto viewCenter = view.getCenter();

	auto viewLeft = viewCenter.x - viewSizeHalf.x;
	auto viewRight = viewCenter.x + viewSizeHalf.x;
	auto viewTop = viewCenter.y - viewSizeHalf.y;
	auto viewBottom = viewCenter.y + viewSizeHalf.y;

	auto compareSprite = new Sprite();

	compareSprite->setPosition(viewLeft, viewTop);
	auto xStart = m_tilesX.lower_bound(compareSprite);

	compareSprite->setPosition(viewRight, viewTop);
	auto xEnd = m_tilesX.upper_bound(compareSprite);

	compareSprite->setPosition(viewLeft, viewTop);
	auto yStart = m_tilesY.lower_bound(compareSprite);

	compareSprite->setPosition(viewLeft, viewBottom);
	auto yEnd = m_tilesY.upper_bound(compareSprite);

	delete compareSprite;

	auto visibleTiles = unordered_map<Sprite*, Sprite*>();
	while (xStart != xEnd)
	{
		auto current = *xStart;
		visibleTiles[current] = current;
		++xStart;
	}

	while (yStart != yEnd)
	{
		auto current = *yStart;
		if (visibleTiles.find(current) != visibleTiles.end())
		{
			renderTarget.draw(*current);
		}

		++yStart;
	}
}

void MapLayerRenderable::AddTile(Sprite* l_tile)
{
	m_tilesX.insert(l_tile);
	m_tilesY.insert(l_tile);

	m_tiles.push_back(l_tile);
}
