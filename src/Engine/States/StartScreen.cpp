#include "stdafx.h"

#include "StartScreen.h"

#include "AGameState.h"
#include "GameplayScreen.h"
#include "CreditScreen.h"

#include "../Components/GUI/GUIStartScreen.h"
#include "../Game/Game.h"

#include "../Factories/ObjectFactory.h"
#include "../Factories/StateFactory.h"

#include "../Managers/InputManager.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/ResourceManager.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components::GUI;
using namespace ToD::Factories;
using namespace ToD::Managers;
using namespace ToD::States;

const string StartScreen::Name = "StartScreen";

StartScreen::StartScreen()
: AGameState()
{
	LOG(INFO) << "Start screen was created";

	auto gfrast = Get<ObjectFactory>().Create(Name);

	AddObject(gfrast);

	auto bgm = Get<ResourceManager>().GetMusic("BGM_StartScreen");
	bgm->setLoop(true);
	bgm->setVolume(50);
	bgm->play();
}

StartScreen::~StartScreen()
{
	LOG(INFO) << "Start screen was destroyed";
	Get<ResourceManager>().GetMusic("BGM_StartScreen")->stop();
}

ReferenceType::RuntimeType StartScreen::GetRuntimeType() const
{
	return "ToD::States::StartScreen";
}

GameStateUpdateResult::EntryPtr StartScreen::Update(const Time l_gameTime, AGameState*& l_nextState)
{
	l_nextState = nullptr;

	auto gui = Get<GameObjectManager>().GetGameObject(GameObjectTag::GUI).GetComponent<GUIStartScreen>();

	if (gui->GetIsStartGameClicked())
	{
		gui->SetIsStartGameClicked(false);

		l_nextState = Get<StateFactory>().Create(GameplayScreen::Name);

		return GameStateUpdateResult::NextState;
	}

	if (gui->GetIsCredistClicked())
	{
		gui->SetIsCredistClicked(false);

		l_nextState = Get<StateFactory>().Create(CreditScreen::Name);

		return GameStateUpdateResult::NextState;
	}

	if (gui->GetIsExitGameClicked())
	{
		gui->SetIsExitGameClicked(false);

		return GameStateUpdateResult::CloseState;
	}

	
	if (Get<InputManager>().GetBindingKeyState(KeyBindingName::Abort) == KeyBindingState::IsPressed)
	{
		return GameStateUpdateResult::CloseState;
	}

	return GameStateUpdateResult::KeepState;
}
