#pragma once

#include "EventArgs.h"

namespace ToD
{
	namespace Components
	{
		class MapLayerRenderable;
	}
}

using namespace sf;
using namespace ToD::Components;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a map load / unload event.
		///
		////////////////////////////////////////////////////////////
		class GameMapEventArgs :
			public EventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_map A layer of the loaded map.
			///
			////////////////////////////////////////////////////////////
			explicit GameMapEventArgs(MapLayerRenderable* l_map);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GameMapEventArgs() IsDefault__;

			/// Properies
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

			////////////////////////////////////////////////////////////
			/// \brief Gets the map size in pixel.
			///
			/// \return The map size in pixel.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetMapSize() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the tile size in pixel.
			///
			/// \return The tile size in pixel.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetTileSize() const;

			/// Members
		private:
			Vector2i														m_mapSize; ///< The map size in pixel.
			Vector2i														m_tileSize; ///< The tile size in pixel.
		};
	}
}
