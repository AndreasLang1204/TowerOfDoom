#include "stdafx.h"

#include "InputManager.h"

#include "EventBus.h"
#include "../Events/EventInvoker.h"
#include "../Events/SfmlEventEventArgs.h"

using namespace sf;
using namespace std;
using namespace ToD;
using namespace ToD::Managers;

InputManager::Component::Component(GameObject* l_owner, InputManager* l_manager)
: AGameComponent(l_owner, GameComponentType::InputManagerIntegration)
, m_manager(l_manager)
{
}

ReferenceType::RuntimeType InputManager::Component::GetRuntimeType() const
{
	return "ToD::Managers::InputManager::Component";
}

InputManager::InputManager()
: m_bindingList()
, m_bindingByKey()
, m_bindingByName()
, m_mouseStates()
{
	m_mouseStates[Mouse::Button::Left] = new KeyBinding(KeyBindingName::None);
	m_mouseStates[Mouse::Button::Right] = new KeyBinding(KeyBindingName::None);

	Get<EventBus>().Get(EventType::SfmlEvent) += new EventInvoker<InputManager, SfmlEventEventArgs>(this, &InputManager::OnSfmlEventRaised);
}

InputManager::~InputManager()
{
	Get<EventBus>().Get(EventType::SfmlEvent) -= new EventInvoker<InputManager, SfmlEventEventArgs>(this, &InputManager::OnSfmlEventRaised);
	
	for (auto binding : m_bindingList)
	{
		delete binding;
	}

	m_bindingByName.clear();
	m_bindingByKey.clear();
	m_bindingList.clear();

	for (auto state : m_mouseStates)
	{
		delete state.second;
	}

	m_mouseStates.clear();
}

ReferenceType::RuntimeType InputManager::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType InputManager::RuntimeType()
{
	return "ToD::Managers::InputManager";
}

void InputManager::Update(const Time l_gameTime)
{
	for (auto& keyBinding : m_bindingByKey)
	{
		if (keyBinding.second->GetKeyState() == KeyBindingState::IsReleased)
		{
			keyBinding.second->GotReleased();
		}
		else if (keyBinding.second->GetKeyState() == KeyBindingState::IsPressed)
		{
			keyBinding.second->GotPressed();
		}
	}

	for (auto& state : m_mouseStates)
	{
		if (state.second->GetKeyState() == KeyBindingState::IsReleased)
		{
			state.second->GotReleased();
		}
		else if (state.second->GetKeyState() == KeyBindingState::IsPressed)
		{
			state.second->GotPressed();
		}
	}
}

void InputManager::Bind(const KeyBindingName::EntryPtr l_bindingName, const Keyboard::Key l_key)
{
	auto iterator = GetBinding(l_bindingName);

	// handle multi keybinding
	if (iterator != m_bindingList.end())
	{
		// m_bindingList contains newBinding 
		m_bindingByKey.insert({ l_key,  *iterator });
	}
	else
	{
		// m_bindingList not contains newBinding 
		auto newBinding = new KeyBinding(l_bindingName);

		m_bindingByName.insert({ l_bindingName, newBinding });
		m_bindingByKey.insert({ l_key,  newBinding });
		m_bindingList.push_back(newBinding);
	}
}

void InputManager::Unbind(const KeyBindingName::EntryPtr l_bindingName)
{
	auto itrBindingByName = m_bindingByName.find(l_bindingName);

	if (itrBindingByName == m_bindingByName.end())
	{
		throw exception(string("KeyBinding " + l_bindingName->ToString() + " does not exist").c_str());
	}
	
	vector<Keyboard::Key> unbindList;

	// get all keys with the KeyBinding.m_name of l_bindingName
	for (auto& keyPair : m_bindingByKey)
	{
		if (keyPair.second->GetName() == itrBindingByName->second->GetName())
		{
			unbindList.push_back(keyPair.first);
		}
	}

	// erase binding from m_bindingByName
	m_bindingByName.erase(l_bindingName);

	// erase all bindings from m_bindingByKey
	for (auto& key : unbindList)
	{
		m_bindingByKey.erase(key);
	}

	// find & erase binding ptr from m_bindingList
	auto iterator = GetBinding(l_bindingName);
	auto binding = *iterator;

	m_bindingList.erase(iterator);

	delete binding;
}

KeyBindingState::EntryPtr InputManager::GetBindingKeyState(const KeyBindingName::EntryPtr l_bindingName)
{
	if (m_bindingByName.find(l_bindingName) == m_bindingByName.end())
	{
		throw exception(string("KeyBinding " + l_bindingName->ToString() + " does not exist").c_str());
	}

	return m_bindingByName[l_bindingName]->GetKeyState();
}

Vector2i InputManager::GetMousePos(const RenderWindow& window) const
{
	return Mouse::getPosition(window);
}

bool InputManager::IsMouseButtonPressed(const Mouse::Button l_mButton) const
{
	if (m_mouseStates.find(l_mButton) == m_mouseStates.end())
	{
		return false;
	}

	return m_mouseStates.at(l_mButton)->GetKeyState() == KeyBindingState::IsPressed;
}

InputManager::KeyBindingConstVectorIterator InputManager::GetBinding(const KeyBindingName::EntryPtr l_bindingName)
{
	return find_if(m_bindingList.begin(), m_bindingList.end(), [l_bindingName](KeyBinding* binding) -> bool { return binding->GetName() == l_bindingName; });
}

void InputManager::OnSfmlEventRaised(SfmlEventEventArgs* l_args)
{
	auto sfmlEvent = l_args->GetEvent();

	if (sfmlEvent.type == Event::MouseButtonPressed || sfmlEvent.type == Event::MouseButtonReleased)
	{
		if (m_mouseStates.find(sfmlEvent.mouseButton.button) != m_mouseStates.end())
		{
			if (sfmlEvent.type == Event::MouseButtonPressed)
			{
				m_mouseStates[sfmlEvent.mouseButton.button]->GotPressed();
			}

			if (sfmlEvent.type == Event::MouseButtonReleased)
			{
				m_mouseStates[sfmlEvent.mouseButton.button]->GotReleased();
			}
		}
	}
	else if (m_bindingByKey.find(sfmlEvent.key.code) != m_bindingByKey.end())
	{
		if (sfmlEvent.type == Event::KeyPressed)
		{
			m_bindingByKey[sfmlEvent.key.code]->GotPressed();
		}
		else if (sfmlEvent.type == Event::KeyReleased)
		{
			m_bindingByKey[sfmlEvent.key.code]->GotReleased();
		}
	}
}
