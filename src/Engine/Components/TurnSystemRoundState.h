#pragma once

#include "../Game/Enumeration.h"

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Defines possible round states.
		///
		////////////////////////////////////////////////////////////
		class TurnSystemRoundState :
			public Enumeration<TurnSystemRoundState>
		{
			/// Enumeation values
		public:
			////////////////////////////////////////////////////////////
			/// \brief The round is starting.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Staring, 0)

			////////////////////////////////////////////////////////////
			/// \brief The round changes the character.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(ChangeCharacter, 1)

			////////////////////////////////////////////////////////////
			/// \brief The round is waiting for the character to finish.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Waiting, 2)

			////////////////////////////////////////////////////////////
			/// \brief The round is ending.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Ending, 3)

			/// Constructors, destructors
		private:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			TurnSystemRoundState() IsDefault__;

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~TurnSystemRoundState() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			static string RuntimeType();
		};
	}
}