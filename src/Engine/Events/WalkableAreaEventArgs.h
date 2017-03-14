#pragma once

#include "EventArgs.h"
#include "../Components/MapLayerCellInfo.h"

using namespace sf;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a walkable area response event.
		///
		////////////////////////////////////////////////////////////
		class WalkableAreaEventArgs :
			public EventArgs
		{
			/// Typedefs
		public:
			////////////////////////////////////////////////////////////
			/// \brief Definition of the walkable area type.
			///
			////////////////////////////////////////////////////////////
			typedef vector<MapLayerCellInfo*>								WalkableArea;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_area The walkable area.
			///
			////////////////////////////////////////////////////////////
			explicit WalkableAreaEventArgs(const WalkableArea l_area);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~WalkableAreaEventArgs() IsDefault__;

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
			/// \brief Gets the walkable area.
			///
			/// \return The walkable area.
			///
			////////////////////////////////////////////////////////////
			const WalkableArea& GetArea() const;

			/// Members
		private:
			WalkableArea													m_area; ///< The walkable area.
		};
	}
}
