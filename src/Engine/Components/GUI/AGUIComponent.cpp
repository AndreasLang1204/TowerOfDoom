#include "stdafx.h"

#include "AGUIComponent.h"

#include "../Game/Game.h"
#include "../Game/GameObject.h"
#include "../Events/EventInvoker.h"
#include "../Events/SfmlEventEventArgs.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace tgui;
using namespace ToD::Components::GUI;
using namespace ToD::Managers;
using namespace ToD::Events;

AGUIComponent::AGUIComponent(GameObject* l_owner)
: Renderable(l_owner, RenderablePriority::GUI)
{
	m_gui = new Gui(Get<Game::Shared>()->GetRenderWindow());

	Get<EventBus>().Get(EventType::SfmlEvent) += new EventInvoker<AGUIComponent, SfmlEventEventArgs>(this, &AGUIComponent::OnSfmlEventRaised);
}

AGUIComponent::~AGUIComponent()
{
	Get<EventBus>().Get(EventType::SfmlEvent) -= new EventInvoker<AGUIComponent, SfmlEventEventArgs>(this, &AGUIComponent::OnSfmlEventRaised);

	delete m_gui;
}

void AGUIComponent::SetIsActive(const bool l_value)
{
	m_isActive = l_value;
}

void AGUIComponent::Process(const Time l_gameTime)
{
	m_gui->draw();
}

void AGUIComponent::OnSfmlEventRaised(SfmlEventEventArgs* l_args)
{
	if (m_isActive)
	{
		m_gui->handleEvent(l_args->GetEvent());
	}
}
