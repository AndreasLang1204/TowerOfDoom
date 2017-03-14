#pragma once

#include "CharacterControllerAction.h"
#include "../AGameComponent.h"

using namespace sf;

namespace ToD
{
	namespace Components
	{
		namespace CharacterControllers
		{
			////////////////////////////////////////////////////////////
			/// \brief Represents a playable character controller instance.
			///
			////////////////////////////////////////////////////////////
			class ACharacterControllerInstance :
				public AGameComponent
			{
				/// Constructors, destructors
			protected:
				////////////////////////////////////////////////////////////
				/// \brief The constructor.
				///
				/// \param l_owner Owner of the game component.
				///
				////////////////////////////////////////////////////////////
				explicit ACharacterControllerInstance(GameObject* l_owner);

			public:
				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				virtual ~ACharacterControllerInstance() IsDefault__;

				/// Properties
			public:
				////////////////////////////////////////////////////////////
				/// \brief Gets the action to execute.
				///
				/// \return The action to execute.
				///
				////////////////////////////////////////////////////////////
				CharacterControllerAction::EntryPtr GetAction() const;

			protected:
				////////////////////////////////////////////////////////////
				/// \brief Sets the action to execute.
				///
				/// \param l_value The value to set.
				///
				////////////////////////////////////////////////////////////
				void SetAction(CharacterControllerAction::EntryPtr l_value);

				/// Members
			private:
				CharacterControllerAction::EntryPtr							m_action; ///< The action to execute.
			};
		}
	}
}
