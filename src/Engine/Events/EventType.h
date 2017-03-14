#pragma once

#include "../Game/Enumeration.h"

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Declares supported render priorities.
		///
		////////////////////////////////////////////////////////////
		class EventType :
			public Enumeration<EventType>
		{
			/// Enumeation values
		public:
			////////////////////////////////////////////////////////////
			/// \brief No event type is specified.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(None, 0)

			////////////////////////////////////////////////////////////
			/// \brief Raised before a game object is deleted.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GameObjectDeleting, 1)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a SFML event is processed.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(SfmlEvent, 2)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the mouse moved.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(MouseMoved, 3)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the grid cursor was updated.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GridCursorUpdated, 4)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the grid cursor was clicked.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GridCursorClicked, 5)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the game loaded a map.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GameMapLoaded, 6)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the game unloaded a map.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GameMapUnloaded, 7)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a GUI element is entered.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GuiElementEntering, 8)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a GUI element is left.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GuiElementLeaving, 9)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the end turn button was clicked.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GuiEndTurnButtonClicked, 10)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the end turn button was clicked.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GuiReturnToMainMenuButtonClicked, 11)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a playable character is activated.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(PlayableCharacterActivated, 12)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a playable character is deactivated.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(PlayableCharacterDeactivated, 13)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the turn system sets the next character active.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemNextCharacter, 14)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the turn system is shutting down.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemShuttingDown, 15)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a character requests the walkable area.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterRequestsWalkableArea, 16)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the walkable area response is sent.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterResponseWalkableArea, 17)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a character requests a walkable path.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterRequestsWalkablePath, 18)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the walkable path response is sent.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterResponseWalkablePath, 19)

			////////////////////////////////////////////////////////////
			/// \brief Raised when the walkable path was updated due to player movement.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterWalkablePathUpdated, 20)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a character starts moving.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterStartsMoving, 21)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a character ends moving.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterEndsMoving, 22)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a character ends their turn active.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(TurnSystemCharacterEndsTurn, 23)

			////////////////////////////////////////////////////////////
			/// \brief Raised when a grid cell was clicked.
			///
			////////////////////////////////////////////////////////////
			EnumerationDeclaration__(GridCellClicked, 24)

			/// Constructors, destructors
		private:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			EventType() IsDefault__;

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~EventType() IsDefault__;

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
