#include "stdafx.h"

#include "GameMapEventArgs.h"

#include "../Components/MapLayerRenderable.h"

using namespace ToD;
using namespace ToD::Events;

GameMapEventArgs::GameMapEventArgs(MapLayerRenderable* l_map)
: EventArgs()
, m_tileSize(l_map->GetTileSize())
{
	auto tileSize = l_map->GetTileSize();
	auto size = l_map->GetSize();

	m_mapSize = Vector2i(size.x * tileSize.x, size.y * tileSize.y);
}

ReferenceType::RuntimeType GameMapEventArgs::GetRuntimeType() const
{
	return "ToD::Events::GameMapEventArgs";
}

Vector2i GameMapEventArgs::GetMapSize() const
{
	return m_mapSize;
}

Vector2i GameMapEventArgs::GetTileSize() const
{
	return m_tileSize;
}
