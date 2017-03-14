#include "stdafx.h"

#include "MapLayerCellInfo.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;

MapLayerCellInfo::MapLayerCellInfo(const bool l_isWalkable, const Vector2i l_mapPosition, const Vector2f l_worldPosition)
: ReferenceType()
, m_isWalkable(l_isWalkable)
, m_mapPosition(l_mapPosition)
, m_worldPosition(l_worldPosition)
, m_pathRecord()
, m_occupants()
{
	m_pathRecord.Reset();
}

ReferenceType::RuntimeType MapLayerCellInfo::GetRuntimeType() const
{
	return "ToD::Components::MapLayerCellInfo";
}

bool MapLayerCellInfo::GetIsWalkable() const
{
	return m_isWalkable;
}

void MapLayerCellInfo::SetWalkable(const bool l_value)
{
	m_isWalkable = l_value;
}

bool MapLayerCellInfo::GetIsOccupied() const
{
	return m_occupants.size() > 0;
}

vector<GameObject*> MapLayerCellInfo::GetOccupants() const
{
	vector<GameObject*> occupants;

	for (auto& occupant : m_occupants)
	{
		occupants.push_back(occupant.second);
	}
	
	return occupants;
}

GameObject* MapLayerCellInfo::GetOccupantWithAnyTag(initializer_list<GameObjectTag::EntryPtr> l_tags) const
{
	for (auto occupant : m_occupants)
	{
		if (occupant.second->HasAnyTag(l_tags))
		{
			return occupant.second;
		}
	}

	return nullptr;
}

Vector2i MapLayerCellInfo::GetMapPosition() const
{
	return m_mapPosition;
}

Vector2f MapLayerCellInfo::GetWorldPosition() const
{
	return m_worldPosition;
}

MapLayerCellInfo::PathRecord& MapLayerCellInfo::GetPathRecord()
{
	return m_pathRecord;
}

void MapLayerCellInfo::Clear()
{
	m_isWalkable = false;
	m_occupants.clear();
}

void MapLayerCellInfo::AddOccupant(GameObject * l_occupant)
{
	if (l_occupant->HasTag(GameObjectTag::Blocking))
	{
		m_isWalkable = false;
	}

	m_occupants[l_occupant->GetRuntimeID()] = l_occupant;
}

void MapLayerCellInfo::RemoveOccupant(GameObject * l_occupant)
{
	if (m_occupants.erase(l_occupant->GetRuntimeID()) == 1)
	{
		if (l_occupant->HasTag(GameObjectTag::Blocking))
		{
			m_isWalkable = true;
		}
	}
}

void MapLayerCellInfo::ResetPathRecord()
{
	m_pathRecord.Reset();
}

bool MapLayerCellInfo::IsOccupant(RuntimeID l_occupantIdentifier)
{
	return m_occupants.find(l_occupantIdentifier) != m_occupants.end();
}
