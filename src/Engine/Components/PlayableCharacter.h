#pragma once

#include "AGameComponent.h"
#include "TurnSystemCharacterState.h"
#include "../Calc/Value.h"
#include "../Calc/RandomizedValue.h"
#include "../Events/WalkableAreaEventArgs.h"
#include "Role/CharacterRole.h"

namespace ToD
{
	namespace Components
	{
		namespace CharacterControllers
		{
			class ACharacterControllerInstance;
		}
	}

	namespace Events
	{
		class GameObjectEventArgs;
		class GridCellClickedEventArgs;
	}
}

using namespace ToD::Calc;
using namespace ToD::Components::CharacterControllers;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Represents a playable character.
		///
		////////////////////////////////////////////////////////////
		class PlayableCharacter :
			public AGameComponent
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_role The role of the PlayableCharacter.
			///
			////////////////////////////////////////////////////////////
			explicit PlayableCharacter(GameObject* l_owner, CharacterRole* l_role);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~PlayableCharacter() IsDefault__;

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
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			static RuntimeType RuntimeType();

			//////////////////////////////////////////////////////////////
			///// \brief Gets the value of a character attribute.
			/////
			///// \param l_name The attribute name.
			/////
			///// \return The attribute value.
			/////
			///// \exception std::exception: No matching attribute was found.
			/////
			//////////////////////////////////////////////////////////////
			//Value::Unit GetAttribute(const string l_name) const;

			////////////////////////////////////////////////////////////
			/// \brief Gets the character role.
			///
			/// \return The character role.
			///
			////////////////////////////////////////////////////////////
			CharacterRole* GetRole() const;

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
			/// \brief Starts the characters turn.
			///
			////////////////////////////////////////////////////////////
			void StartCharacterTurn();

			////////////////////////////////////////////////////////////
			/// \brief Send a request for the character's walkable area.
			///
			////////////////////////////////////////////////////////////
			void RequestWalkableArea();

			//// ToDo
			//////////////////////////////////////////////////////////////
			///// \brief Send a request for the character's that can be affected by the chossen ability.
			/////
			//////////////////////////////////////////////////////////////
			//void RequestInteractableCharacters();

			////////////////////////////////////////////////////////////
			/// \brief Enters the characters idle state.
			///
			////////////////////////////////////////////////////////////
			void EnterIdleState();

			////////////////////////////////////////////////////////////
			/// \brief Polls the character controller and waits for an action to execute.
			///
			////////////////////////////////////////////////////////////
			void PollControllerAction();

			////////////////////////////////////////////////////////////
			/// \brief Leaves the characters idle state.
			///
			/// \param l_nextState The next state to enter.
			///
			////////////////////////////////////////////////////////////
			void LeaveIdleState(TurnSystemCharacterState::EntryPtr l_nextState);

			////////////////////////////////////////////////////////////
			/// \brief Ends the characters turn.
			///
			////////////////////////////////////////////////////////////
			void EndCharacterTurn();

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system next character event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemNextCharacter(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system response walkable area event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterResponseWalkableArea(WalkableAreaEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character starts moving event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterStartsMoving(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character ends moving event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterEndsMoving(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the grid cell clicked event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGridCellClicked(GridCellClickedEventArgs* l_args);

			/// Members
		private:
			/*RandomizedValue												m_initiative; ///< Todo. remove after implementing role
			RandomizedValue													m_actionPoints; ///< Todo. remove after implementing role
			Value															m_hitPoints; ///< Todo. remove after implementing role*/
			CharacterRole*													m_role; ///< The role instance.
			ACharacterControllerInstance*									m_controller; ///< The controller instance.
			TurnSystemCharacterState::EntryPtr								m_currentCharacterState; ///< The current character state.
			WalkableAreaEventArgs::WalkableArea								m_walkableArea; ///< The currently walkable area.
		};
	}
}
