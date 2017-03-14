#pragma once

#include "ACharacterControllerInstance.h"

namespace ToD
{
	namespace Events
	{
		class EventArgs;
		class GameObjectEventArgs;
	}
}

using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		namespace CharacterControllers
		{
			////////////////////////////////////////////////////////////
			/// \brief Represents the player playable character controller instance.
			///
			////////////////////////////////////////////////////////////
			class PlayerCharacterControllerInstance :
				public ACharacterControllerInstance
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor.
				///
				/// \param l_owner Owner of the game component.
				///
				////////////////////////////////////////////////////////////
				explicit PlayerCharacterControllerInstance(GameObject* l_owner);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~PlayerCharacterControllerInstance() IsDefault__;

				/// Properties
			public:
				////////////////////////////////////////////////////////////
				/// \brief Gets the static runtime type.
				///
				/// \return The static runtime type.
				///
				////////////////////////////////////////////////////////////
				virtual RuntimeType GetRuntimeType() const override;

				/// Methods
			public:
				////////////////////////////////////////////////////////////
				/// \brief Avtivates the component (first step).
				///
				/// \override Always call base class method.
				///
				////////////////////////////////////////////////////////////
				virtual void Activate1() override;

				////////////////////////////////////////////////////////////
				/// \brief Avtivates the component (second step).
				///
				/// \override Always call base class method.
				///
				////////////////////////////////////////////////////////////
				virtual void Activate2() override;

				////////////////////////////////////////////////////////////
				/// \brief Deactivates the component (first step).
				///
				/// \override Always call base class method.
				///
				////////////////////////////////////////////////////////////
				virtual void Deactivate1() override;

				////////////////////////////////////////////////////////////
				/// \brief Deactivates the component (second step).
				///
				/// \override Always call base class method.
				///
				////////////////////////////////////////////////////////////
				virtual void Deactivate2() override;

				////////////////////////////////////////////////////////////
				/// \brief Processes pending work.
				///
				/// \param l_gameTime Provides a snapshot of timing values.
				///
				////////////////////////////////////////////////////////////
				virtual void Process(const Time l_gameTime) override;

			private:
				////////////////////////////////////////////////////////////
				/// \brief Processes the gui end turn button clicked event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnGuiEndTurnButtonClicked(EventArgs* l_args);

				////////////////////////////////////////////////////////////
				/// \brief Processes the gui return to main menu button clicked event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnGuiReturnToMainMenuButtonClicked(EventArgs* l_args);

				////////////////////////////////////////////////////////////
				/// \brief Processes the playable character deactivated event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args);

				////////////////////////////////////////////////////////////
				/// \brief Processes the turn system next character event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnTurnSystemNextCharacter(GameObjectEventArgs* l_args);
			};
		}
	}
}
