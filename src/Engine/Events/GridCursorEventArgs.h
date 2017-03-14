#pragma once

#include "EventArgs.h"

using namespace sf;
using namespace ToD;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a grid cursor event.
		///
		////////////////////////////////////////////////////////////
		class GridCursorEventArgs :
			public EventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_position The grid cursor position in world coordinates.
			/// \param l_isVisible Indicates whether the grid cursor is visible or not.
			///
			////////////////////////////////////////////////////////////
			explicit GridCursorEventArgs(const Vector2f l_position, const bool l_isVisible);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GridCursorEventArgs() IsDefault__;

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
			/// \brief Gets the grid cursor position in world coordinates.
			///
			/// \return The grid cursor position in world coordinates.
			///
			////////////////////////////////////////////////////////////
			Vector2f GetPosition() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets a value indicating whether the grid cursor is visible or not.
			///
			/// \return A value indicating whether the grid cursor is visible or not.
			///
			////////////////////////////////////////////////////////////
			bool GetIsVisible() const;

			/// Members
		private:
			Vector2f														m_position; ///< The grid cursor position in world coordinates.
			bool															m_isVisible; ///< Indicates whether the grid cursor is visible or not.
		};
	}
}
