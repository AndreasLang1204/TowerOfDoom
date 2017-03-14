#pragma once

#include "EventArgs.h"

// !! not implemented !!

namespace ToD
{
	class GameObject;
}

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a game object.
		///
		////////////////////////////////////////////////////////////
		class KeyInputEventArgs :
			public EventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_object The game object realting with the event.
			/// 
			////////////////////////////////////////////////////////////
			explicit KeyInputEventArgs(GameObject* l_object);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~KeyInputEventArgs() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

			/// Members
		private:

		};
	}
}