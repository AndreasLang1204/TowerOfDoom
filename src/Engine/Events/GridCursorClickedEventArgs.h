#pragma once

#include "GridCursorEventArgs.h"

using namespace sf;
using namespace ToD;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a grid cursor clicked event.
		///
		////////////////////////////////////////////////////////////
		class GridCursorClickedEventArgs :
			public GridCursorEventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_position The grid cursor position in world coordinates.
			/// \param l_isVisible Indicates whether the grid cursor is visible or not.
			/// \param l_button The clicked mouse button.
			///
			////////////////////////////////////////////////////////////
			explicit GridCursorClickedEventArgs(const Vector2f l_position, const bool l_isVisible, const Mouse::Button l_button);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GridCursorClickedEventArgs() IsDefault__;

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
			/// \brief Gets the clicked mouse button.
			///
			/// \return The clicked mouse button.
			///
			////////////////////////////////////////////////////////////
			Mouse::Button GetButton() const;

			/// Members
		private:
			Mouse::Button													m_button; ///< The clicked mouse button.
		};
	}
}
