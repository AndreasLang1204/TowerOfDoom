#pragma once

#include "AGameState.h"

namespace ToD
{
	namespace States
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to update and render the start screen.
		///
		////////////////////////////////////////////////////////////
		class StartScreen :
			public AGameState
		{
			/// Constants
		public:
			////////////////////////////////////////////////////////////
			/// \brief Name that represents the start screen type.
			///
			////////////////////////////////////////////////////////////
			static const string												Name;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			StartScreen();

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~StartScreen();

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
			/// \brief Updates the start screen.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			/// \param l_nextState The next state to use if UpdateResult::NextState is returned.
			///
			/// \return Result that indicates what should happen with this state.
			///
			////////////////////////////////////////////////////////////
			virtual GameStateUpdateResult::EntryPtr Update(const Time l_gameTime, AGameState*& l_nextState) override;
		};
	}
}