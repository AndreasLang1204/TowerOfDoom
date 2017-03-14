#pragma once

#include "EventArgs.h"

using namespace sf;
using namespace ToD;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a mouse event.
		///
		////////////////////////////////////////////////////////////
		class MouseEventArgs :
			public EventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_position The mouse position in world coordinates.
			///
			////////////////////////////////////////////////////////////
			explicit MouseEventArgs(const Vector2f l_position);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~MouseEventArgs() IsDefault__;

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
			/// \brief Gets the mouse position in world coordinates.
			///
			/// \return The mouse position in world coordinates.
			///
			////////////////////////////////////////////////////////////
			Vector2f GetPosition() const;

			/// Members
		private:
			Vector2f														m_position; ///< The mouse position in world coordinates.
		};
	}
}
