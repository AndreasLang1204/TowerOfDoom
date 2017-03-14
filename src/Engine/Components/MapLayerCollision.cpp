#include "stdafx.h"

#include "MapLayerCollision.h"
#include "../Events/EventInvoker.h"
#include "../Events/GridCellClickedEventArgs.h"
#include "../Events/GridCursorClickedEventArgs.h"
#include "../Events/RequestWalkableAreaEventArgs.h"
#include "../Events/RequestWalkablePathEventArgs.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;

MapLayerCollision::MapLayerCollision(GameObject* l_owner, const Vector2i l_layerSize, const Vector2i l_tileSize)
: AGameComponent(l_owner, GameComponentType::None) 
, m_layerSize(l_layerSize)
, m_tileSize(l_tileSize)
, m_layer(l_layerSize.y)
{
	for (auto row = size_t(0); row < m_layer.size(); row++)
	{
		m_layer[row].resize(m_layerSize.x);

		for (auto col = size_t(0); col < m_layer[row].size(); col++)
		{
			auto mapPosition = Vector2i(col, row);
			auto worldPosition = Vector2f(static_cast<float>(col * m_tileSize.x), static_cast<float>(row * m_tileSize.y));

			m_layer[row][col] = new MapLayerCellInfo(true, mapPosition, worldPosition);
		}
	}
}

MapLayerCollision::~MapLayerCollision()
{
	Clear();
}

ReferenceType::RuntimeType MapLayerCollision::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType MapLayerCollision::RuntimeType()
{
	return "ToD::Components::MapLayerCollision";
}

Vector2i MapLayerCollision::GetLayerSize() const
{
	return m_layerSize;
}

void MapLayerCollision::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::TurnSystemCharacterRequestsWalkableArea) += new EventInvoker<MapLayerCollision, RequestWalkableAreaEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterRequestsWalkableArea);
	Get<EventBus>().Get(EventType::TurnSystemCharacterRequestsWalkablePath) += new EventInvoker<MapLayerCollision, RequestWalkablePathEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterRequestsWalkablePath);
	Get<EventBus>().Get(EventType::TurnSystemCharacterStartsMoving) += new EventInvoker<MapLayerCollision, GameObjectEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterStartsMoving);
	Get<EventBus>().Get(EventType::TurnSystemCharacterEndsMoving) += new EventInvoker<MapLayerCollision, GameObjectEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterEndsMoving);
	Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) += new EventInvoker<MapLayerCollision, GameObjectEventArgs>(this, &MapLayerCollision::OnPlayableCharacterDeactivated);
	Get<EventBus>().Get(EventType::GridCursorClicked) += new EventInvoker<MapLayerCollision, GridCursorClickedEventArgs>(this, &MapLayerCollision::OnGridCursorClicked);
}

void MapLayerCollision::Activate2()
{
	Activateable::Activate2();

	auto objects = Get<GameObjectManager>().GetGameObjects({ GameObjectTag::MapObject });
	for (auto object : objects)
	{
		auto cellPosition = GetCellPosition(object);
		auto cell = GetCell(cellPosition);

		cell->AddOccupant(object);
	}
}

void MapLayerCollision::Deactivate1()
{
	Activateable::Deactivate1();

	Get<EventBus>().Get(EventType::TurnSystemCharacterRequestsWalkableArea) -= new EventInvoker<MapLayerCollision, RequestWalkableAreaEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterRequestsWalkableArea);
	Get<EventBus>().Get(EventType::TurnSystemCharacterRequestsWalkablePath) -= new EventInvoker<MapLayerCollision, RequestWalkablePathEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterRequestsWalkablePath);
	Get<EventBus>().Get(EventType::TurnSystemCharacterStartsMoving) -= new EventInvoker<MapLayerCollision, GameObjectEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterStartsMoving);
	Get<EventBus>().Get(EventType::TurnSystemCharacterEndsMoving) -= new EventInvoker<MapLayerCollision, GameObjectEventArgs>(this, &MapLayerCollision::OnTurnSystemCharacterEndsMoving);
	Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) -= new EventInvoker<MapLayerCollision, GameObjectEventArgs>(this, &MapLayerCollision::OnPlayableCharacterDeactivated);
	Get<EventBus>().Get(EventType::GridCursorClicked) -= new EventInvoker<MapLayerCollision, GridCursorClickedEventArgs>(this, &MapLayerCollision::OnGridCursorClicked);
}

void MapLayerCollision::Deactivate2()
{
	Activateable::Deactivate2();
}

void MapLayerCollision::Process(const Time l_gameTime)
{
}

void MapLayerCollision::Clear()
{
	for (auto row : m_layer)
	{
		for (auto cell : row)
		{
			if (cell != nullptr)
			{
				delete cell;
			}
		}
	}

	m_layer.clear();
}

void MapLayerCollision::AddCell(const Vector2i l_position, MapLayerCellInfo* l_cellInfo)
{
	if (IsOutOfBounds(l_position))
	{
		LOG(ERROR) << "Invalid cell position (cell position: " << l_position.x << ", " << l_position.y << ") map size: " << m_layerSize.x << ", " << m_layerSize.y << endl;
		throw exception("error: Invalid cell index!");
	}

	if (m_layer[l_position.y][l_position.x] != nullptr)
	{
		delete m_layer[l_position.y][l_position.x];
	}

	m_layer[l_position.y][l_position.x] = l_cellInfo;
}

MapLayerCellInfo* MapLayerCollision::GetCell(const Vector2i l_position) const
{
	if (IsOutOfBounds(l_position))
	{
		return nullptr;
	}

	return m_layer.at(l_position.y).at(l_position.x);
}

bool MapLayerCollision::IsOutOfBounds(const Vector2i l_position) const
{
	return l_position.x < 0 || l_position.x >= m_layerSize.x || l_position.y < 0 || l_position.y >= m_layerSize.y;
}

Vector2i MapLayerCollision::GetCellPosition(GameObject* l_object) const
{
	auto x = static_cast<int>(l_object->GetPosition().x / m_tileSize.x);
	auto y = static_cast<int>(l_object->GetPosition().y / m_tileSize.y);

	return Vector2i(x, y);
}

WalkableAreaEventArgs::WalkableArea MapLayerCollision::CalculateWalkableArea(GameObject* l_object, const Value::Unit l_movementRange)
{
	// Todo. refactoring
	auto area = WalkableAreaEventArgs::WalkableArea();

#pragma region Setup & Lambda functions
	//						right			left			top			  bottom			right_top		   left_top        right_bottom	   left_bottom
	Vector2i dir[] = { Vector2i(1, 0) , Vector2i(-1, 0), Vector2i(0, -1), Vector2i(0, 1), Vector2i(1, -1), Vector2i(-1, -1), Vector2i(1, 1), Vector2i(-1, 1) };

	// wipe cell pathRecord
	for (auto& row : m_layer)
	{
		for (auto& cell : row)
		{
			cell->GetPathRecord().Reset();
		}
	}

	auto heuristic = [](MapLayerCellInfo* a, MapLayerCellInfo* b) -> int
	{
		auto pos = a->GetMapPosition() - b->GetMapPosition();
		return abs(pos.x) + abs(pos.y);
	};

	// custom comparison function for cellinfo
	auto comp = [](MapLayerCellInfo* a, MapLayerCellInfo* b) -> bool { return a->GetPathRecord().m_costSoFar < b->GetPathRecord().m_costSoFar; };
#pragma endregion

#pragma region StartCell check
	auto startCellPosX = static_cast<int>(l_object->GetPosition().x / m_tileSize.x);
	auto startCellPosY = static_cast<int>(l_object->GetPosition().y / m_tileSize.y);

	auto startCell = GetCell(Vector2i(startCellPosX, startCellPosY));
	if (startCell == nullptr)
	{
		return area;
	}

#pragma endregion

	//breadth first search
	// closed = m_movementRange, 
	// open list
	list<MapLayerCellInfo*> open;

	open.push_back(startCell);

	MapLayerCellInfo* current = nullptr;

	// ************************************************************
	while (open.size())
	{
		current = *open.begin();
		open.remove(current);
		area.push_back(current);

		// check all 8 directions (neighbors)
		for (auto move : dir)
		{
			auto cell = GetCell(current->GetMapPosition() + move);

			// find cell in closed and open list of CellInfo
			// lambda expression is used to compare with content of Cellinfo directly
			auto itClosed = find_if(area.begin(), area.end(),
				[&cell](MapLayerCellInfo* a)->bool { return a == cell; });

			auto itOpen = find_if(open.begin(), open.end(),
				[&cell](MapLayerCellInfo* a)->bool { return a == cell; });

			int endNodeCost = current->GetPathRecord().m_costSoFar + cell->GetPathRecord().m_cost * heuristic(current, cell);

			if (cell->GetIsWalkable() == false ||
				// prevent corner cutting
				((move == Vector2i(1, 1) || move == Vector2i(-1, 1)) && GetCell(current->GetMapPosition() + Vector2i(0, 1))->GetIsWalkable() == false) ||
				((move == Vector2i(1, -1) || move == Vector2i(-1, -1)) && GetCell(current->GetMapPosition() + Vector2i(0, -1))->GetIsWalkable() == false) ||
				((move == Vector2i(-1, 1) || move == Vector2i(-1, -1)) && GetCell(current->GetMapPosition() + Vector2i(-1, 0))->GetIsWalkable() == false) ||
				((move == Vector2i(1, 1) || move == Vector2i(1, -1)) && GetCell(current->GetMapPosition() + Vector2i(1, 0))->GetIsWalkable() == false))
				continue;

			if (itClosed == area.end() && endNodeCost <= l_movementRange)
			{
				if (itOpen == open.end())
				{
					// update cell info (can be newly created, or the existing one)
					cell->GetPathRecord().m_costSoFar = endNodeCost;
					cell->GetPathRecord().m_parent = current;

					// add neighbor to the open list
					open.push_back(cell);
				}
				else // if neighbor has already been calculated for the open list
				{
					if (endNodeCost <  (*itOpen)->GetPathRecord().m_costSoFar)
					{
						(*itOpen)->GetPathRecord().m_costSoFar = endNodeCost;
						(*itOpen)->GetPathRecord().m_parent = current;
					}
				}
			}

			// resort
			stable_sort(open.begin(), open.end(), comp);
		}
	}

	open.clear();

	area.erase(find(area.begin(), area.end(), startCell));

	return area;
}

WalkablePathEventArgs::WalkablePath MapLayerCollision::CalculateWalkablePath(GameObject * l_object, const Value::Unit l_movementRange, const Vector2i l_targetPosition)
{
	//						right			left			top			  bottom			right_top		   left_top        right_bottom	   left_bottom
	Vector2i dir[] = { Vector2i(1, 0) , Vector2i(-1, 0), Vector2i(0, -1), Vector2i(0, 1), Vector2i(1, -1), Vector2i(-1, -1), Vector2i(1, 1), Vector2i(-1, 1) };

	// wipe cell pathRecord
	for (auto& row : m_layer)
	{
		for (auto& cell : row)
		{
			cell->GetPathRecord().Reset();
		}
	}

	// custom comparison function for set
	auto comp = [](MapLayerCellInfo* a, MapLayerCellInfo* b) -> bool { return a->GetPathRecord().m_estimatedCost < b->GetPathRecord().m_estimatedCost; };

	auto heuristic = [](MapLayerCellInfo* a, MapLayerCellInfo* b) -> int
	{
		auto pos = a->GetMapPosition() - b->GetMapPosition();
		return (abs(pos.x) + abs(pos.y));
	};

	auto startCellPosX = static_cast<int>(l_object->GetPosition().x / m_tileSize.x);
	auto startCellPosY = static_cast<int>(l_object->GetPosition().y / m_tileSize.y);

	auto path = WalkablePathEventArgs::WalkablePath();
	auto targetCell = GetCell(l_targetPosition);
	if (targetCell == nullptr)
	{
		return path;
	}

	auto startCell = GetCell(Vector2i(startCellPosX, startCellPosY));

	// closed, open list
	list<MapLayerCellInfo*> open;
	list<MapLayerCellInfo*> closed;

	open.push_back(startCell);

	MapLayerCellInfo* current = nullptr;

	while (open.size())
	{
		current = *open.begin();
		open.remove(current);

		if (current == targetCell)
			break;

		// check all 8 directions
		for (auto move : dir)
		{
			auto cell = GetCell(current->GetMapPosition() + move);

			if (cell->GetIsWalkable() == false ||
				// prevent corner cutting
				((move == Vector2i(1, 1) || move == Vector2i(-1, 1)) && GetCell(current->GetMapPosition() + Vector2i(0, 1))->GetIsWalkable() == false) ||
				((move == Vector2i(1, -1) || move == Vector2i(-1, -1)) && GetCell(current->GetMapPosition() + Vector2i(0, -1))->GetIsWalkable() == false) ||
				((move == Vector2i(-1, 1) || move == Vector2i(-1, -1)) && GetCell(current->GetMapPosition() + Vector2i(-1, 0))->GetIsWalkable() == false) ||
				((move == Vector2i(1, 1) || move == Vector2i(1, -1)) && GetCell(current->GetMapPosition() + Vector2i(1, 0))->GetIsWalkable() == false))
				continue;

			// find cell in closed and open list of CellInfo
			// lambda expression is used to compare with content of Cellinfo directly
			auto itClosed = find_if(closed.begin(), closed.end(),
				[&cell](MapLayerCellInfo* a)->bool { return a == cell; });

			auto itOpen = find_if(open.begin(), open.end(),
				[&cell](MapLayerCellInfo* a)->bool { return a == cell; });

			int endNodeCost = current->GetPathRecord().m_costSoFar + cell->GetPathRecord().m_cost * heuristic(current, cell);
			int estimatedCost = current->GetPathRecord().m_costSoFar + heuristic(current, targetCell);

			MapLayerCellInfo* cell2;

			// get cell info from closed list, open list or create new one
			// check also if an update is necessary (endNodeCost < costSoFar)
			if (itClosed != closed.end())
			{
				continue;
			}
			else if (itOpen != open.end())
			{
				cell2 = *itOpen;
				if (cell2->GetPathRecord().m_costSoFar <= endNodeCost)
					continue;
			}
			else
			{
				cell2 = cell;
			}

			// update cell info (can be newly created, or the existing one)
			cell2->GetPathRecord().m_costSoFar = endNodeCost;
			cell2->GetPathRecord().m_estimatedCost = estimatedCost;
			cell2->GetPathRecord().m_parent = current;

			//LOG(INFO) << "estimatedCost: " << estimatedCost << " eendNodeCost: " << endNodeCost;

			// add noderecord to open list, if it does not exist yet
			if (find(open.begin(), open.end(), cell2) == open.end())
				open.push_back(cell2);
			// resort
			stable_sort(open.begin(), open.end(), comp);
		}

		open.remove(current);
		closed.push_back(current);
	}

	if (current == targetCell)
	{
		while (current != startCell)
		{
			path.push_front(current);
			current = current->GetPathRecord().m_parent;
		}
	}

	open.clear();
	closed.clear();

	return path;
}

Vector2i MapLayerCollision::CalculateGridPosition(const Vector2f l_worldPosition) const
{
	auto xf = floor(l_worldPosition.x / m_tileSize.x);
	auto yf = floor(l_worldPosition.y / m_tileSize.y);

	return Vector2i(static_cast<int>(xf), static_cast<int>(yf));
}

void MapLayerCollision::UpdateCellOccupant(GameObject* l_object, const bool l_isSubscribing)
{
	auto gridPosition = CalculateGridPosition(l_object->GetPosition());
	auto cell = GetCell(gridPosition);
	if (cell == nullptr)
	{
		return;
	}

	if (l_isSubscribing)
	{
		cell->AddOccupant(l_object);
	}
	else
	{
		cell->RemoveOccupant(l_object);
	}
}

void MapLayerCollision::OnGridCursorClicked(GridCursorClickedEventArgs* l_args) const
{
	auto gridPosition = CalculateGridPosition(l_args->GetPosition());
	auto cell = GetCell(gridPosition);

	Get<EventBus>().Raise(EventType::GridCellClicked, new GridCellClickedEventArgs(cell, gridPosition, l_args->GetButton()));
}

void MapLayerCollision::OnTurnSystemCharacterRequestsWalkableArea(RequestWalkableAreaEventArgs* l_args)
{
	auto area = CalculateWalkableArea(l_args->GetGameObject(), l_args->GetMovementRange());

	Get<EventBus>().Raise(EventType::TurnSystemCharacterResponseWalkableArea, new WalkableAreaEventArgs(area));
}

void MapLayerCollision::OnTurnSystemCharacterRequestsWalkablePath(RequestWalkablePathEventArgs* l_args)
{
	auto path = CalculateWalkablePath(l_args->GetGameObject(), l_args->GetMovementRange(), l_args->GetTargetCellPosition());
	auto target = GetCell(l_args->GetTargetCellPosition());

	Get<EventBus>().Raise(EventType::TurnSystemCharacterResponseWalkablePath, new WalkablePathEventArgs(path, target));
}

void MapLayerCollision::OnTurnSystemCharacterStartsMoving(GameObjectEventArgs* l_args)
{
	UpdateCellOccupant(l_args->GetGameObject(), false);
}

void MapLayerCollision::OnTurnSystemCharacterEndsMoving(GameObjectEventArgs* l_args)
{
	UpdateCellOccupant(l_args->GetGameObject(), true);
}

void MapLayerCollision::OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args)
{
	UpdateCellOccupant(l_args->GetGameObject(), false);
}
