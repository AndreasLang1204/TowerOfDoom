#pragma once

#include "EventArgs.h"
#include "../Components/MapLayerCellInfo.h"

using namespace sf;
using namespace ToD;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a grid cell clicked event.
		///
		////////////////////////////////////////////////////////////
		class GridCellClickedEventArgs :
			public EventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_position The clicked cell.
			/// \param l_position The cell position in grid coordinates.
			/// \param l_button The clicked mouse button.
			///
			////////////////////////////////////////////////////////////
			explicit GridCellClickedEventArgs(MapLayerCellInfo* l_cell, const Vector2i l_position, const Mouse::Button l_button);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GridCellClickedEventArgs() IsDefault__;

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
			/// \brief Gets the clicked cell.
			///
			/// \return The clicked cell.
			///
			////////////////////////////////////////////////////////////
			MapLayerCellInfo* GetCell() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the cell position in grid coordinates.
			///
			/// \return The cell position in grid coordinates.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetPosition() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the clicked mouse button.
			///
			/// \return The clicked mouse button.
			///
			////////////////////////////////////////////////////////////
			Mouse::Button GetButton() const;

			/// Members
		private:
			MapLayerCellInfo*												m_cell; ///< The clicked cell.
			Vector2i														m_position; ///< The cell position in grid coordinates.
			Mouse::Button													m_button; ///< The clicked mouse button.
		};
	}
}
