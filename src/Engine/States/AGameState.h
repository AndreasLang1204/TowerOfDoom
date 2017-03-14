#pragma once

#include "GameStateUpdateResult.h"
#include "../Game/GameObject.h"

namespace ToD
{
	namespace Events
	{
		class GameObjectEventArgs;
	}
}

using namespace std;
using namespace ToD::Events;
using namespace ToD::States;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Defines how a game state is created and updated.
	///
	////////////////////////////////////////////////////////////
	class AGameState :
		public ReferenceType
	{
		/// Typedefs
	private:
		////////////////////////////////////////////////////////////
		/// \brief An array of game objects.
		///
		////////////////////////////////////////////////////////////
		typedef unordered_map<RuntimeID, GameObject*>						ObjectDictionary;

		/// Constructors, destructors
	protected:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		AGameState();

	public:
		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		virtual ~AGameState();

		/// Properties
	protected:
		////////////////////////////////////////////////////////////
		/// \brief Gets the objects used by the game state.
		///
		/// \return The object array as vector.
		///
		////////////////////////////////////////////////////////////
		const ObjectDictionary& GetObjects() const;

		/// Methods
	public:
		////////////////////////////////////////////////////////////
		/// \brief Enters the state before the first update occurs.
		///
		/// All components are registered to relevant namagers.
		///
		////////////////////////////////////////////////////////////
		void Enter();

		////////////////////////////////////////////////////////////
		/// \brief Updates the game state.
		///
		/// \param l_gameTime Provides a snapshot of timing values.
		/// \param l_nextState The next state to use if UpdateResult::NextState is returned.
		///
		/// \return Result that indicates what should happen with this state.
		///
		////////////////////////////////////////////////////////////
		virtual GameStateUpdateResult::EntryPtr Update(const Time l_gameTime, AGameState*& l_nextState) IsAbstract__;

		////////////////////////////////////////////////////////////
		/// \brief Exits the state after is has closed.
		///
		/// All components are removed from relevant namagers.
		///
		////////////////////////////////////////////////////////////
		void Exit();

	protected:
		////////////////////////////////////////////////////////////
		/// \brief Adds an object to the game state.
		///
		/// \param l_object The object to add.
		///
		////////////////////////////////////////////////////////////
		void AddObject(GameObject* l_object);

	private:
		////////////////////////////////////////////////////////////
		/// \brief Handles a game object deleting event.
		///
		/// \param l_args Event arguments.
		///
		////////////////////////////////////////////////////////////
		void OnGameObjectDeleting(GameObjectEventArgs* l_args);

		/// Members
	private:
		ObjectDictionary													m_objects; ///< Contains all game objects in this game state uses.
		bool																m_isEntered; ///< Indicates whether the game state is entered or not.
	};
}