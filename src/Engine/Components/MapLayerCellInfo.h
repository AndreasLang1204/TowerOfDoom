#pragma once

#include "../Game/GameObject.h"

using namespace sf;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds relevant information about a map grid cell.
		///
		////////////////////////////////////////////////////////////
		class MapLayerCellInfo :
			public ReferenceType
		{
			/// Nested classes & structs
		public:
			////////////////////////////////////////////////////////////
			/// \brief Holds relevant information about a map grid cell used by path finding algorithms.
			///
			////////////////////////////////////////////////////////////
			struct PathRecord
			{
				MapLayerCellInfo*											m_parent; ///< The parent path record.
				int															m_cost = 1; ///< The walking cost.
				int															m_costSoFar; ///< The walk cost so far.
				int															m_estimatedCost; ///< The estimated walk cost.

				////////////////////////////////////////////////////////////
				/// \brief Resets the path record data.
				///
				////////////////////////////////////////////////////////////
				void Reset()
				{
					m_parent = nullptr;
					m_costSoFar = 0;
					m_estimatedCost = 0;
				}
			};

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_isWalkable Indicates whether the map cell is walkable or not.
			/// \param l_mapPosition The cell's grid position in tiles.
			/// \param l_worldPosition The cell's absolute map position in pixel.
			///
			////////////////////////////////////////////////////////////
			MapLayerCellInfo(const bool l_isWalkable, const Vector2i l_mapPosition, const Vector2f l_worldPosition);

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
			/// \brief Gets a value indicating whether the map cell is walkable or not.
			///
			/// \return True if the map cell is walkable; otherwise false.
			///
			////////////////////////////////////////////////////////////
			bool GetIsWalkable() const;

			////////////////////////////////////////////////////////////
			/// \brief Sets a value indicating whether the map cell is walkable or not.
			///
			/// \param l_value The value to set.
			///
			////////////////////////////////////////////////////////////
			void SetWalkable(const bool l_value);

			////////////////////////////////////////////////////////////
			/// \brief Gets a value indicating whether the map cell is occupied by any game object or not.
			///
			/// \return True if the map cell is occupied by any game object; otherwise false.
			///
			////////////////////////////////////////////////////////////
			bool GetIsOccupied() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets all occupants for the cell.
			///
			/// \return A vector holding all occupants for the cell.
			///
			////////////////////////////////////////////////////////////
			vector<GameObject*> GetOccupants() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the first occupant with one of the specified Tags.
			///
			/// \return the first occupants with one of the specified Tags.
			///
			////////////////////////////////////////////////////////////
			GameObject* GetOccupantWithAnyTag(initializer_list<GameObjectTag::EntryPtr> l_tags) const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the cell's grid position in tiles.
			///
			/// \return The cell's grid position in tiles.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetMapPosition() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the cell's absolute map position in pixel.
			///
			/// \return The cell's absolute map position in pixel.
			///
			////////////////////////////////////////////////////////////
			Vector2f GetWorldPosition() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the cell's path record.
			///
			/// \return The cell's path record.
			///
			////////////////////////////////////////////////////////////
			PathRecord& GetPathRecord();

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Clears all information of the cell.
			///
			////////////////////////////////////////////////////////////
			void Clear();

			////////////////////////////////////////////////////////////
			/// \brief Adds an occupant to the cell.
			///
			/// \param l_occupant The occupant to add.
			///
			////////////////////////////////////////////////////////////
			void AddOccupant(GameObject* l_occupant);

			////////////////////////////////////////////////////////////
			/// \brief Removes an occupant from the cell.
			///
			/// \param l_occupant The occupant to remove.
			///
			////////////////////////////////////////////////////////////
			void RemoveOccupant(GameObject * l_occupant);

			////////////////////////////////////////////////////////////
			/// \brief Restes the cell's path record information.
			///
			////////////////////////////////////////////////////////////
			void ResetPathRecord();

			////////////////////////////////////////////////////////////
			/// \brief Determines whether a specific game object is an occupant of the cell.
			///
			/// \param l_occupantIdentifier The game object's identifier.
			///
			/// \return True if the game object is an occupant of the cell; otherwise false.
			///
			////////////////////////////////////////////////////////////
			bool IsOccupant(RuntimeID l_occupantIdentifier);

			/// Members
		private:
			bool															m_isWalkable; ///< Indicates whether the map cell is walkable or not.
			Vector2i														m_mapPosition; ///< The cell's grid position in tiles.
			Vector2f														m_worldPosition; ///< The cell's absolute map position in pixel.
			PathRecord														m_pathRecord; ///< The cell's path record.
			unordered_map<RuntimeID, GameObject*>							m_occupants; ///< Contains all occupants for the cell.
		};
	}
}