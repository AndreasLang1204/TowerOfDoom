#include "stdafx.h"

#include "Engine.h"

#include "../Components/GameComponentType.h"
#include "../Components/RenderablePriority.h"
#include "../Components/TurnSystemCharacterState.h"
#include "../Components/TurnSystemRoundState.h"
#include "../Components/CharacterControllers/CharacterControllerAction.h"
#include "../Events/EventType.h"
#include "../Factories/ObjectFactoryPrefabCategory.h"
#include "../Game/Game.h"
#include "../Game/GameObjectTag.h"
#include "../Game/KeyBindingName.h"
#include "../Game/KeyBindingState.h"
#include "../States/GameStateUpdateResult.h"

INITIALIZE_EASYLOGGINGPP

using namespace ToD::States;
using namespace ToD::Components::CharacterControllers;

void ToD::Main()
{
	LOG(INFO) << "Hello from DLL :)";

	GameObjectTag::Initialize();
	GameComponentType::Initialize();
	EventType::Initialize();
	KeyBindingName::Initialize();
	KeyBindingState::Initialize();
	GameStateUpdateResult::Initialize();
	RenderablePriority::Initialize();
	TurnSystemCharacterState::Initialize();
	TurnSystemRoundState::Initialize();
	ObjectFactoryPrefabCategory::Initialize();
	CharacterControllerAction::Initialize();

#ifdef NDEBUG
	try
	{
#endif
		Game game;
		game.Run();
#ifdef NDEBUG
	}
	catch (exception ex)
	{
		auto windowHandle = HWND(nullptr);
		auto caption = string("Unexpected error");
		auto message = string("An unexpected error occured. ") + string(ex.what()) + string(" The application is closing now.");
		auto mode = MB_OK;

		MessageBox(windowHandle, message.c_str(), caption.c_str(), mode);
	}
#endif

	GameObjectTag::Cleanup();
	GameComponentType::Cleanup();
	EventType::Cleanup();
	KeyBindingName::Cleanup();
	KeyBindingState::Cleanup();
	GameStateUpdateResult::Cleanup();
	RenderablePriority::Cleanup();
	TurnSystemCharacterState::Cleanup();
	TurnSystemRoundState::Cleanup();
	ObjectFactoryPrefabCategory::Cleanup();
	CharacterControllerAction::Cleanup();
}
