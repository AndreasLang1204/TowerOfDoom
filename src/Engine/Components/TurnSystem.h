#pragma once

#include "AGameComponent.h"
#include "TurnSystemRoundState.h"
#include "../Calc/Value.h"
#include "../Game/GameObject.h"

namespace ToD
{
	namespace Events
	{
		class EventArgs;
		class GameObjectEventArgs;
	}
}

using namespace sf;
using namespace ToD::Calc;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Updates the turn based combat system.
		///
		////////////////////////////////////////////////////////////
		class TurnSystem
			: public AGameComponent
		{
			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Definition of the object dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<RuntimeID, GameObject*>					ObjectDictionary;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the weighted combatants type.
			///
			////////////////////////////////////////////////////////////
			typedef map<Value::Unit, GameObject*, greater<int>>				WeightedObjects;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the turn order type.
			///
			////////////////////////////////////////////////////////////
			typedef map<Value::Unit, WeightedObjects, greater<Value::Unit>>	TurnOrder;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			///
			////////////////////////////////////////////////////////////
			explicit TurnSystem(GameObject* l_owner);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~TurnSystem() IsDefault__;

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
			/// \brief Starts the next round.
			///
			////////////////////////////////////////////////////////////
			void StartNextRound();

			////////////////////////////////////////////////////////////
			/// \brief Changes the active character.
			///
			////////////////////////////////////////////////////////////
			void ChangeCharacter();

			////////////////////////////////////////////////////////////
			/// \brief Ends the current round.
			///
			////////////////////////////////////////////////////////////
			void EndCurrentRound();

			////////////////////////////////////////////////////////////
			/// \brief Processes the playable character activated event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnPlayableCharacterActivated(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the playable character deactivated event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character ends turn event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterEndsTurn(EventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system shutting down event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemShuttingDown(EventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Remvoes a character by its game object identifier from the turn order and erases them from the stored combatants if needed.
			///
			/// \param l_identifier The game object identifier.
			/// \param l_eraseCombatant True if the character should be erased from the stored combatants; false if character should be removed from turn order only.
			///
			////////////////////////////////////////////////////////////
			void RemoveCharacter(const RuntimeID l_identifier, const bool l_eraseCombatant);

			/// Members
		private:
			ObjectDictionary											m_combatants; ///< Contains all combatants.
			TurnOrder													m_turnOrder; ///< Contains combatants sorted by their speed.
			TurnSystemRoundState::EntryPtr								m_currentRoundState; ///< The current round state.
			unsigned int												m_currentRound; ///< The current round.
		};
	}
}