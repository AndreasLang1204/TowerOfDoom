#pragma once

#include "AGameState.h"

namespace ToD
{
	namespace Events
	{
		class EventArgs;
	}
}

using namespace ToD::Events;

namespace ToD
{
	namespace States
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to update and render the credit screen.
		///
		////////////////////////////////////////////////////////////
		class CreditScreen :
			public AGameState
		{
			/// Constants
		public:
			////////////////////////////////////////////////////////////
			/// \brief Name that represents the credit screen type.
			///
			////////////////////////////////////////////////////////////
			static const string												Name;

			////////////////////////////////////////////////////////////
			/// \brief Name that represents the credit screen camera.
			///
			////////////////////////////////////////////////////////////
			static const string												CameraName;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			CreditScreen();

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~CreditScreen();

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
			/// \brief Updates the gameplay screen.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			/// \param l_nextState The next state to use if UpdateResult::NextState is returned.
			///
			/// \return Result that indicates what should happen with this state.
			///
			////////////////////////////////////////////////////////////
			virtual GameStateUpdateResult::EntryPtr Update(const Time l_gameTime, AGameState*& l_nextState) override;

		private:
			/// Members
		private:
			bool															m_isExitingOnNextUpdate; ///< Indicates whether the state is exiting during the next update.
		};
	}
}