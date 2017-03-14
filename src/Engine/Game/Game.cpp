#include "stdafx.h"

#include "Game.h"

#include "rapidxml.hpp"
#include "GameConfig.h"
#include "GameComponentRegistration.h"
#include "Randomizer.h"
#include "../Events/EventInvoker.h"
#include "../Events/MouseEventArgs.h"
#include "../Events/SfmlEventEventArgs.h"
#include "../Factories/ObjectFactory.h"
#include "../Factories/StateFactory.h"
#include "../Managers/ObjectContainer.h"
#include "../Managers/EventBus.h"
#include "../Managers/GameLogic.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameStateManager.h"
#include "../Managers/RenderManager.h"
#include "../Managers/GameObjectManager.h"
#include "../Managers/ResourceManager.h"
#include "../States/StartScreen.h"

using namespace rapidxml;
using namespace sf;
using namespace std;
using namespace ToD::Components;
using namespace ToD::Factories;
using namespace ToD::Managers;
using namespace ToD::States;

Clock Game::s_clock = Clock();

Game::Shared::Shared(Game* l_game)
: SharedObject()
, m_game(l_game)
{
}

Game* Game::Shared::operator->() const
{
	return m_game;
}

ReferenceType::RuntimeType Game::Shared::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType Game::Shared::RuntimeType()
{
	return "ToD::Game::Shared";
}

Game::Game()
: m_gameObject("GameHelper")
{
}

ReferenceType::RuntimeType Game::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType Game::RuntimeType()
{
	return "ToD::Game";
}

RenderWindow& Game::GetRenderWindow()
{
	return m_window;
}

void Game::Run()
{
	if (ObjectContainer::Has<Game>())
	{
		throw exception("Another game instance is already running.");
	}

	ObjectContainer::AddObject(Shared::RuntimeType(), new Shared(this));

	if (Init())
	{
		while (m_window.isOpen())
		{
			Update();
			Render();
		}

		ShutDown();
	}

	ObjectContainer::RemoveObject(Shared::RuntimeType());
}

void Game::Exit()
{
	m_window.close();
}

void Game::UseDefaultView()
{
	GetRenderWindow().setView(GetRenderWindow().getDefaultView());
}

bool Game::Init()
{
	ObjectContainer::AddObject(EventBus::RuntimeType(), new EventBus());
	ObjectContainer::AddObject(Randomizer::RuntimeType(), new Randomizer());

	ObjectContainer::AddObject(GameComponentRegistration::RuntimeType(), new GameComponentRegistration());

	ObjectContainer::AddObject(InputManager::RuntimeType(), new InputManager());
	ObjectContainer::AddObject(GameLogic::RuntimeType(), new GameLogic());
	ObjectContainer::AddObject(RenderManager::RuntimeType(), new RenderManager());

	ObjectContainer::AddObject(GameObjectManager::RuntimeType(), new GameObjectManager());
	ObjectContainer::AddObject(GameStateManager::RuntimeType(), new GameStateManager());
	
	ObjectContainer::AddObject(ResourceManager::RuntimeType(), new ResourceManager());

	ObjectContainer::AddObject(ObjectFactory::RuntimeType(), new ObjectFactory());
	ObjectContainer::AddObject(StateFactory::RuntimeType(), new StateFactory());

	auto config = new GameConfig();
	config->Load("../assets/Engine.config");

	VideoMode vm(config->GetResolutionWidth(), config->GetResolutionHeight());
	m_window.create(vm, config->GetWindowTitle(), Style::Titlebar);
	m_window.setFramerateLimit(config->GetRefreshRate());

	for (auto textureInfo : config->GetTextureDictionary())
	{
		Get<ResourceManager>().RegisterTexture(textureInfo.first, textureInfo.second, false);
	}

#pragma region Sound Effects
	#pragma region GUI
		Get<ResourceManager>().RegisterSoundBuffer("BtnPress", "../assets/Audio/Button_Push.wav");
		Get<ResourceManager>().CreateSound("BtnPress", "BtnPress");
	#pragma endregion

	#pragma region Combat
		Get<ResourceManager>().RegisterSoundBuffer("FireSpell", "../assets/Audio/fire_spell_01.wav");
		Get<ResourceManager>().CreateSound("FireSpell", "FireSpell");

		Get<ResourceManager>().RegisterSoundBuffer("Magic", "../assets/Audio/magic.wav");
		Get<ResourceManager>().CreateSound("Magic", "Magic");

		Get<ResourceManager>().RegisterSoundBuffer("Spell", "../assets/Audio/spell.wav");
		Get<ResourceManager>().CreateSound("Spell", "Spell");

		Get<ResourceManager>().RegisterSoundBuffer("SwordSwing", "../assets/Audio/swing.wav");
		Get<ResourceManager>().CreateSound("SwordSwing", "SwordSwing");
	#pragma endregion

	#pragma region Characters
		#pragma region Player
			Get<ResourceManager>().RegisterSoundBuffer("IWILLFIGHT_YELL", "../assets/Audio/I_WILLFIGHTYELL.flac");
			Get<ResourceManager>().CreateSound("IWILLFIGHT_YELL", "IWILLFIGHT_YELL");

			Get<ResourceManager>().RegisterSoundBuffer("IWILLFIGHT_CALM", "../assets/Audio/i_will_fightcalm.flac");
			Get<ResourceManager>().CreateSound("IWILLFIGHT_CALM", "IWILLFIGHT_CALM");

			Get<ResourceManager>().RegisterSoundBuffer("PrepareToDie", "../assets/Audio/preparetodie.flac");
			Get<ResourceManager>().CreateSound("PrepareToDie", "PrepareToDie");

			Get<ResourceManager>().RegisterSoundBuffer("TheseEnemies", "../assets/Audio/theseenemies.flac");
			Get<ResourceManager>().CreateSound("TheseEnemies", "TheseEnemies");
		#pragma endregion

		#pragma region Enemies
			Get<ResourceManager>().RegisterSoundBuffer("GrowlingZombie", "../assets/Audio/growling_zombie.wav");
			Get<ResourceManager>().CreateSound("GrowlingZombie", "GrowlingZombie");

			Get<ResourceManager>().RegisterSoundBuffer("ShortRoar", "../assets/Audio/short_roar.wav");
			Get<ResourceManager>().CreateSound("ShortRoar", "ShortRoar");

			Get<ResourceManager>().RegisterSoundBuffer("Laughter", "../assets/Audio/laughter.wav");
			Get<ResourceManager>().CreateSound("Laughter", "Laughter");

			Get<ResourceManager>().RegisterSoundBuffer("Orc", "../assets/Audio/orc_16.wav");
			Get<ResourceManager>().CreateSound("Orc", "Orc");
		#pragma endregion
	#pragma endregion
#pragma endregion

#pragma region Music
	// StartScreen
	Get<ResourceManager>().RegisterMusic("BGM_StartScreen", "../assets/Audio/33_Dead_End.ogg");
	// GameplayScreen
	Get<ResourceManager>().RegisterMusic("BGM_GameplayScreen", "../assets/Audio/06_Under_Siege.ogg");
#pragma endregion

	for (auto binding : config->GetBindings())
	{
		auto bindingName = binding.first;
		auto bindingKey = binding.second;

		Get<InputManager>().Bind(bindingName, bindingKey);
	}

	delete config;

	Get<ObjectFactory>().LoadPrefabs(ObjectFactoryPrefabCategory::AbilityDeclaration, "../assets/data/abilities.xml");
	Get<ObjectFactory>().LoadPrefabs(ObjectFactoryPrefabCategory::RoleDeclaration, "../assets/data/roles.xml");

	Get<Randomizer>().SetSeed(static_cast<unsigned int>(time(nullptr)));

	auto updateOrder =
	{
		GameComponentType::GameStateManagerIntegration,
		GameComponentType::TurnSystemRoundState,
		GameComponentType::TurnSystemCharacterController,
		GameComponentType::TurnSystemCharacterState,
		GameComponentType::Transition,
		GameComponentType::Camera,
		GameComponentType::GameObjectManagerIntegration,
		GameComponentType::InputManagerIntegration,
	};

	Get<GameLogic>().SetUpdateOrder(updateOrder);

	// Create & register manager helper components
	m_gameObject.AddComponent(new InputManager::Component(&m_gameObject, &Get<InputManager>()));
	m_gameObject.AddComponent(new GameStateManager::Component(&m_gameObject, &Get<GameStateManager>()));
	m_gameObject.AddComponent(new GameObjectManager::Component(&m_gameObject, &Get<GameObjectManager>()));

	Get<GameComponentRegistration>().Register({ &m_gameObject });

	Get<GameStateManager>().SetInitialState(Get<StateFactory>().Create(StartScreen::Name));

	Get<EventBus>().Get(EventType::SfmlEvent) += new EventInvoker<Game, SfmlEventEventArgs>(this, &Game::OnSfmlEventRaised);

	return true;
}

void Game::Update()
{
	Event event;

	if (m_window.hasFocus())
	{
		while (m_window.pollEvent(event))
		{
			Get<EventBus>().Raise(EventType::SfmlEvent, new SfmlEventEventArgs(event));
		}
	}

	auto delta = s_clock.restart();

	Get<GameLogic>().Update(delta);

	if (Get<GameStateManager>().IsEmpty())
	{
		Exit();
	}
}

void Game::Render()
{
	m_window.clear(Color(0, 0, 0, 255));

	Get<RenderManager>().Render();
	
	m_window.display();
}

void Game::ShutDown()
{
	Get<EventBus>().Get(EventType::SfmlEvent) -= new EventInvoker<Game, SfmlEventEventArgs>(this, &Game::OnSfmlEventRaised);

	Get<GameComponentRegistration>().Deregister({ &m_gameObject });

	ObjectContainer::RemoveObject(GameStateManager::RuntimeType());
	ObjectContainer::RemoveObject(GameObjectManager::RuntimeType());

	ObjectContainer::RemoveObject(StateFactory::RuntimeType());
	ObjectContainer::RemoveObject(ObjectFactory::RuntimeType());

	ObjectContainer::RemoveObject(ResourceManager::RuntimeType());

	ObjectContainer::RemoveObject(RenderManager::RuntimeType());
	ObjectContainer::RemoveObject(GameLogic::RuntimeType());
	ObjectContainer::RemoveObject(InputManager::RuntimeType());

	ObjectContainer::RemoveObject(GameComponentRegistration::RuntimeType());

	ObjectContainer::RemoveObject(Randomizer::RuntimeType());
	ObjectContainer::RemoveObject(EventBus::RuntimeType());
}

void Game::OnSfmlEventRaised(SfmlEventEventArgs* l_args)
{
	auto event = l_args->GetEvent();

	if (event.type == Event::Closed)
	{
		Exit();
	}
	else if (event.type == Event::MouseMoved)
	{
		auto cursorWorldPosition = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y });

		Get<EventBus>().Raise(EventType::MouseMoved, new MouseEventArgs(cursorWorldPosition));
	}
}
