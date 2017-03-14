#include "stdafx.h"

#include "CreditScreen.h"

#include "../Events/EventInvoker.h"
#include "../Factories/ObjectFactory.h"

#include "../Managers/EventBus.h"
#include "../Managers/InputManager.h"
#include "../Managers/ResourceManager.h"
#include "../Managers/GameObjectManager.h"

#include "../Components/GUI/GUICreditScreen.h"

using namespace ToD::Factories;
using namespace ToD::Managers;
using namespace ToD::Components::GUI;

const string CreditScreen::Name = "CreditScreen";
const string CreditScreen::CameraName = "CreditScreen::Camera";

CreditScreen::CreditScreen()
: AGameState()
, m_isExitingOnNextUpdate(false)
{
	LOG(INFO) << "CreditScreen screen was created";

	auto objects = Get<ObjectFactory>().CreateFromTmxFile("../assets/CreditRoom.tmx");

	for (auto object : objects)
	{
		AddObject(object);
	}

	AddObject(Get<ObjectFactory>().Create(Name));
	AddObject(Get<ObjectFactory>().Create(CameraName));
}

CreditScreen::~CreditScreen()
{
	LOG(INFO) << "CreditScreen screen was destroyed";
}

ReferenceType::RuntimeType CreditScreen::GetRuntimeType() const
{
	return "ToD::States::CreditScreen";
}

GameStateUpdateResult::EntryPtr CreditScreen::Update(const Time l_gameTime, AGameState*& l_nextState)
{
	l_nextState = nullptr;

	GUICreditScreen* gui = nullptr;
	auto guiObjects = Get<GameObjectManager>().GetGameObjects({ GameObjectTag::GUI });
	for (auto object : guiObjects)
	{
		if (object->GetComponent<GUICreditScreen>() != nullptr)
		{
			gui = object->GetComponent<GUICreditScreen>();
			break;
		}
	}

	if (gui->GetIsExitScreenClicked())
	{
		gui->SetIsExitScreenClicked(false);

		return GameStateUpdateResult::CloseState;
	}

	/*if (Get<InputManager>().GetBindingKeyState(KeyBindingName::Abort) == KeyBindingState::IsPressed)
	{
		Get<EventBus>().Raise(EventType::GuiReturnToMainMenuButtonClicked, new EventArgs());
	}*/

	return GameStateUpdateResult::KeepState;
}
