#pragma once

#include "AGameComponent.h"
#include "MapLayerCellInfo.h"
#include "../Calc/Value.h"
#include "../Events/WalkableAreaEventArgs.h"
#include "../Events/WalkablePathEventArgs.h"

namespace ToD
{
	namespace Events
	{
		class GridCursorClickedEventArgs;
		class GameObjectEventArgs;
		class RequestWalkableAreaEventArgs;
		class RequestWalkablePathEventArgs;
	}
}

using namespace sf;
using namespace ToD::Calc;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to handle collision / path-finding in the map.
		///
		////////////////////////////////////////////////////////////
		class MapLayerCollision
			: public AGameComponent
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_layerSize The layer size in tiles.
			/// \param l_tileSize Size of a single tile, in pixel.
			///
			////////////////////////////////////////////////////////////
			MapLayerCollision(GameObject* l_owner, const Vector2i l_layerSize, const Vector2i l_tileSize);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~MapLayerCollision();

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			static RuntimeType RuntimeType();

			////////////////////////////////////////////////////////////
			/// \brief Gets the layer size in tiles.
			///
			/// \return The layer size in tiles.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetLayerSize() const;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Avtivates the component (first step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Activate1() override;

			////////////////////////////////////////////////////////////
			/// \brief Avtivates the component (second step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Activate2() override;

			////////////////////////////////////////////////////////////
			/// \brief Deactivates the component (first step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Deactivate1() override;

			////////////////////////////////////////////////////////////
			/// \brief Deactivates the component (second step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Deactivate2() override;

			////////////////////////////////////////////////////////////
			/// \brief Processes pending work.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Process(const Time l_gameTime) override;

			////////////////////////////////////////////////////////////
			/// \brief Clears the whole layer and deletes all cells.
			///
			////////////////////////////////////////////////////////////
			void Clear();

			////////////////////////////////////////////////////////////
			/// \brief Adds a cell to the map layer.
			///
			/// \param l_position The cell's position in tiles.
			/// \param l_cellInfo The info to add.
			///
			/// \exception std::exception: l_position is outside the layer dimensions.
			///
			////////////////////////////////////////////////////////////
			void AddCell(const Vector2i l_position, MapLayerCellInfo* l_cellInfo);

			////////////////////////////////////////////////////////////
			/// \brief Gets the cell at a specific position.
			///
			/// \param l_position The cell's position in tiles.
			///
			/// \return The cell at the specified position or nullptr if the position is outside the layer dimensions.
			///
			////////////////////////////////////////////////////////////
			MapLayerCellInfo* GetCell(const Vector2i l_position) const;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Checks whether a cell position is out of bounds or not.
			///
			/// \param l_position The position to check.
			///
			/// \return True if the position is out of bounds; otherwise false.
			///
			////////////////////////////////////////////////////////////
			bool IsOutOfBounds(const Vector2i l_position) const;

			////////////////////////////////////////////////////////////
			/// \brief Retrieves the cell position of a game object.
			///
			/// \param l_object A game object.
			///
			/// \return Returns the game object's position as cell position.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetCellPosition(GameObject* l_object) const;

			////////////////////////////////////////////////////////////
			/// \brief Calculates the walkable area for a specific game object.
			///
			/// \param l_object A game object.
			/// \param l_movementRange The object movement range.
			///
			/// \return Returns the calculated walkable area.
			///
			////////////////////////////////////////////////////////////
			WalkableAreaEventArgs::WalkableArea CalculateWalkableArea(GameObject* l_object, const Value::Unit l_movementRange);

			////////////////////////////////////////////////////////////
			/// \brief Calculates the walkable path for a specific game object.
			///
			/// \param l_object A game object.
			/// \param l_movementRange The object movement range.
			/// \param l_targetPosition The target cell's position.
			///
			/// \return Returns the calculated walkable path.
			///
			////////////////////////////////////////////////////////////
			WalkablePathEventArgs::WalkablePath MapLayerCollision::CalculateWalkablePath(GameObject * l_object, const Value::Unit l_movementRange, const Vector2i l_targetPosition);

			////////////////////////////////////////////////////////////
			/// \brief Calculates the grid position for a world position.
			///
			/// \param l_worldPosition A world position.
			///
			/// \return Returns the calculated grid position.
			///
			////////////////////////////////////////////////////////////
			Vector2i CalculateGridPosition(const Vector2f l_worldPosition) const;

			////////////////////////////////////////////////////////////
			/// \brief Updates the occupants of the cell the specified game object stands on.
			///
			/// \param l_object The game object to subscribe / unsubscribe.
			/// \param l_isSubscribing Indicates whether the game object is subscribing or unsubscribing.
			///
			////////////////////////////////////////////////////////////
			void UpdateCellOccupant(GameObject* l_object, const bool l_isSubscribing);

			////////////////////////////////////////////////////////////
			/// \brief Processes the grid cursor clicked event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGridCursorClicked(GridCursorClickedEventArgs* l_args) const;

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character requests walkable area event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterRequestsWalkableArea(RequestWalkableAreaEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character requests walkable path event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterRequestsWalkablePath(RequestWalkablePathEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character starts moving event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterStartsMoving(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character ends moving event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterEndsMoving(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the playable character deactivated event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args);

			/// Members
		private:
			Vector2i														m_layerSize; ///< The layer size in tiles.
			Vector2i														m_tileSize; ///< Size of a single tile, in pixel.
			vector<vector<MapLayerCellInfo*>>								m_layer; ///< The map layer represented as cells.
		};
	}
}