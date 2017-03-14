#pragma once

#include "GameComponentType.h"
#include "../Game/Activateable.h"

namespace ToD
{
	class GameObject;
}

using namespace sf;
using namespace std;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Represents a single functionality of a game object.
		///
		////////////////////////////////////////////////////////////
		class AGameComponent :
			public Activateable
		{
			/// Typedefs
			/// Constructors, destructors
		protected:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_type The component type.
			///
			////////////////////////////////////////////////////////////
			AGameComponent(GameObject* l_owner, const GameComponentType::EntryPtr l_type);

		public:
			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~AGameComponent() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the component owner.
			///
			/// \return The component owner.
			///
			////////////////////////////////////////////////////////////
			GameObject* GetOwner() const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the component type.
			///
			/// \return The component type.
			///
			////////////////////////////////////////////////////////////
			GameComponentType::EntryPtr GetType() const;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Processes pending work.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Process(const Time l_gameTime) IsAbstract__;

			/// Members
		private:
			GameObject*														m_owner; ///< The component owner.
			GameComponentType::EntryPtr										m_type; ///< The component type.
		};
	}
}
