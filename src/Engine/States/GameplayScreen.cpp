#include "stdafx.h"

#include "GameplayScreen.h"

#include "../Events/EventInvoker.h"
#include "../Factories/ObjectFactory.h"
#include "../Managers/EventBus.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"

using namespace ToD::Factories;
using namespace ToD::Managers;

const string GameplayScreen::Name = "GameplayScreen";
const string GameplayScreen::CameraName = "GameplayScreen::Camera";

GameplayScreen::GameplayScreen()
: AGameState()
, m_isExitingOnNextUpdate(false)
{
	LOG(INFO) << "Gameplay screen was created";

	auto objects = Get<ObjectFactory>().CreateFromTmxFile("../assets/TestArena.tmx");

	for (auto object : objects)
	{
		AddObject(object);
	}

	AddObject(Get<ObjectFactory>().Create(Name));
	AddObject(Get<ObjectFactory>().Create(CameraName));

	Get<ResourceManager>().GetMusic("BGM_StartScreen")->stop();
	auto bgm = Get<ResourceManager>().GetMusic("BGM_GameplayScreen");
	bgm->setLoop(true);
	bgm->setVolume(10);
	bgm->play();

	Get<EventBus>().Get(EventType::TurnSystemShuttingDown) += new EventInvoker<GameplayScreen, EventArgs>(this, &GameplayScreen::OnTurnSystemShuttingDown);
}

GameplayScreen::~GameplayScreen()
{
	Get<EventBus>().Get(EventType::TurnSystemShuttingDown) -= new EventInvoker<GameplayScreen, EventArgs>(this, &GameplayScreen::OnTurnSystemShuttingDown);
	
	Get<ResourceManager>().GetMusic("BGM_GameplayScreen")->stop();
	Get<ResourceManager>().GetMusic("BGM_StartScreen")->play();
	
	LOG(INFO) << "Gameplay screen was destroyed";
}

ReferenceType::RuntimeType GameplayScreen::GetRuntimeType() const
{
	return "ToD::States::GameplayScreen";
}

GameStateUpdateResult::EntryPtr GameplayScreen::Update(const Time l_gameTime, AGameState*& l_nextState)
{
	l_nextState = nullptr;

	if (m_isExitingOnNextUpdate)
	{
		return GameStateUpdateResult::CloseState;
	}

	if (Get<InputManager>().GetBindingKeyState(KeyBindingName::Abort) == KeyBindingState::IsPressed)
	{
		Get<EventBus>().Raise(EventType::GuiReturnToMainMenuButtonClicked, new EventArgs());
	}

	return GameStateUpdateResult::KeepState;
}

void GameplayScreen::OnTurnSystemShuttingDown(EventArgs* l_args)
{
	m_isExitingOnNextUpdate = true;
}
