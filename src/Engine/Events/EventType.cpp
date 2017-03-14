#include "stdafx.h"

#include "EventType.h"

using namespace ToD;
using namespace ToD::Events;

int Enumeration<EventType>::s_nextIndex;

EnumerationDefinition__(EventType, None)
EnumerationDefinition__(EventType, GameObjectDeleting)
EnumerationDefinition__(EventType, SfmlEvent)
EnumerationDefinition__(EventType, MouseMoved)
EnumerationDefinition__(EventType, GridCursorUpdated)
EnumerationDefinition__(EventType, GridCursorClicked)
EnumerationDefinition__(EventType, GameMapLoaded)
EnumerationDefinition__(EventType, GameMapUnloaded)
EnumerationDefinition__(EventType, GuiElementEntering)
EnumerationDefinition__(EventType, GuiElementLeaving)
EnumerationDefinition__(EventType, GuiEndTurnButtonClicked)
EnumerationDefinition__(EventType, GuiReturnToMainMenuButtonClicked)
EnumerationDefinition__(EventType, PlayableCharacterActivated)
EnumerationDefinition__(EventType, PlayableCharacterDeactivated)
EnumerationDefinition__(EventType, TurnSystemNextCharacter)
EnumerationDefinition__(EventType, TurnSystemShuttingDown)
EnumerationDefinition__(EventType, TurnSystemCharacterRequestsWalkableArea)
EnumerationDefinition__(EventType, TurnSystemCharacterResponseWalkableArea)
EnumerationDefinition__(EventType, TurnSystemCharacterRequestsWalkablePath)
EnumerationDefinition__(EventType, TurnSystemCharacterResponseWalkablePath)
EnumerationDefinition__(EventType, TurnSystemCharacterWalkablePathUpdated)
EnumerationDefinition__(EventType, TurnSystemCharacterStartsMoving)
EnumerationDefinition__(EventType, TurnSystemCharacterEndsMoving)
EnumerationDefinition__(EventType, TurnSystemCharacterEndsTurn)
EnumerationDefinition__(EventType, GridCellClicked)

void Enumeration<EventType>::Initialize()
{
	Create();

	Add(EventType::None);
	Add(EventType::GameObjectDeleting);
	Add(EventType::SfmlEvent);
	Add(EventType::MouseMoved);
	Add(EventType::GridCursorUpdated);
	Add(EventType::GridCursorClicked);
	Add(EventType::GameMapLoaded);
	Add(EventType::GameMapUnloaded);
	Add(EventType::GuiElementEntering);
	Add(EventType::GuiElementLeaving);
	Add(EventType::GuiEndTurnButtonClicked);
	Add(EventType::GuiReturnToMainMenuButtonClicked);
	Add(EventType::PlayableCharacterActivated);
	Add(EventType::PlayableCharacterDeactivated);
	Add(EventType::TurnSystemNextCharacter);
	Add(EventType::TurnSystemShuttingDown);
	Add(EventType::TurnSystemCharacterRequestsWalkableArea);
	Add(EventType::TurnSystemCharacterResponseWalkableArea);
	Add(EventType::TurnSystemCharacterRequestsWalkablePath);
	Add(EventType::TurnSystemCharacterResponseWalkablePath);
	Add(EventType::TurnSystemCharacterWalkablePathUpdated);
	Add(EventType::TurnSystemCharacterStartsMoving);
	Add(EventType::TurnSystemCharacterEndsMoving);
	Add(EventType::TurnSystemCharacterEndsTurn);
	Add(EventType::GridCellClicked);
}

string EventType::RuntimeType()
{
	return "ToD::Events::EventType";
}
