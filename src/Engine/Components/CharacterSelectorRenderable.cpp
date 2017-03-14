#include "stdafx.h"

#include "CharacterSelectorRenderable.h"

#include "../Events/EventArgs.h"
#include "../Game/GameObject.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Game/Game.h"
#include "../Managers/EventBus.h"

using namespace ToD::Components;
using namespace ToD::Managers;

CharacterSelectorRenderable::CharacterSelectorRenderable(GameObject* l_owner, Texture* l_texture, const bool l_player)
: Renderable(l_owner, RenderablePriority::BackgroundDecoration)
, m_selector()
, m_isVisible(false)
{
	m_selector.setTexture(*l_texture);
	
	if (l_player)
	{
		m_selector.setTextureRect(IntRect(0, 0, 16, 16));
	}
	else
	{
		m_selector.setTextureRect(IntRect(16, 0, 16, 16));
	}
	
}

ReferenceType::RuntimeType CharacterSelectorRenderable::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType CharacterSelectorRenderable::RuntimeType()
{
	return "ToD::Components::CharacterSelectorRenderable";
}

void CharacterSelectorRenderable::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) += new EventInvoker<CharacterSelectorRenderable, GameObjectEventArgs>(this, &CharacterSelectorRenderable::OnTurnSystemNextCharacter);
}

void CharacterSelectorRenderable::Activate2()
{
	Activateable::Activate2();
}

void CharacterSelectorRenderable::Deactivate1()
{
	Activateable::Deactivate1();
}

void CharacterSelectorRenderable::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) -= new EventInvoker<CharacterSelectorRenderable, GameObjectEventArgs>(this, &CharacterSelectorRenderable::OnTurnSystemNextCharacter);
}

void CharacterSelectorRenderable::Process(const Time l_gameTime)
{
	if (m_isVisible)
	{
		m_selector.setPosition(GetOwner()->GetPosition());

		Get<Game::Shared>()->GetRenderWindow().draw(m_selector);
	}
}

void CharacterSelectorRenderable::OnTurnSystemNextCharacter(GameObjectEventArgs* l_args)
{
	l_args->GetGameObject() == GetOwner() ? m_isVisible = true : m_isVisible = false;
}

