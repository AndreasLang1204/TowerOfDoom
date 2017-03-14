#pragma once

#include "EventArgs.h"

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
		class GameObjectEventArgs :
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
			explicit GameObjectEventArgs(GameObject* l_object);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~GameObjectEventArgs() IsDefault__;

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
			/// \brief Gets the game object realting with the event.
			///
			/// \return The game object realting with the event.
			///
			////////////////////////////////////////////////////////////
			GameObject* GetGameObject() const;

			/// Members
		private:
			GameObject*														m_object; ///< The game object realting with the event.
		};
	}
}
