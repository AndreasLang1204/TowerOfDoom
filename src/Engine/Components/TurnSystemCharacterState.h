#pragma once

#include "../Game/Enumeration.h"

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Defines possible character states.
		///
		////////////////////////////////////////////////////////////
		class TurnSystemCharacterState :
			public Enumeration<TurnSystemCharacterState>
		{
			/// Enumeation values
		public:
			////////////////////////////////////////////////////////////
			/// \brief The character is inactive.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Inactive, -1)

			////////////////////////////////////////////////////////////
			/// \brief The character turn is starting.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Starting, 0)

			////////////////////////////////////////////////////////////
			/// \brief The character requests the walkable area.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(RequestWalkableArea, 1)

			////////////////////////////////////////////////////////////
			/// \brief The character is idle and waits for commands.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Idle, 2)

			////////////////////////////////////////////////////////////
			/// \brief The character is moving.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(ActionMove, 3)

			////////////////////////////////////////////////////////////
			/// \brief The character uses a role action.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(ActionRole, 4)

			////////////////////////////////////////////////////////////
			/// \brief The character turn is ending.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(Ending, 5)

			/// Constructors, destructors
		private:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			TurnSystemCharacterState() IsDefault__;

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~TurnSystemCharacterState() IsDefault__;

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
