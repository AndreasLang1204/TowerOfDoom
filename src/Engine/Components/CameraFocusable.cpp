#include "stdafx.h"

#include "CameraFocusable.h"

#include "../Events/EventInvoker.h"
#include "../Events/GameMapEventArgs.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Game/GameObject.h"
#include "../Game/Game.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Events;
using namespace ToD::Managers;

CameraFocusable::CameraFocusable(GameObject* l_owner, View l_view, const float l_zoom)
: AGameComponent(l_owner, GameComponentType::Camera)
, m_view(l_view)
, m_mapSize(0, 0, 0, 0)
, m_isDownLocked(false)
, m_isLeftLocked(false)
, m_isRightLocked(false)
, m_isUpLocked(false)
{
	m_view.zoom(l_zoom);

	auto viewSize = m_view.getSize();
}

ReferenceType::RuntimeType CameraFocusable::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType ToD::Components::CameraFocusable::RuntimeType()
{
	return "ToD::Components::CameraFocusable";
}

void CameraFocusable::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::GameMapLoaded) += new EventInvoker<CameraFocusable, GameMapEventArgs>(this, &CameraFocusable::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) += new EventInvoker<CameraFocusable, GameObjectEventArgs>(this, &CameraFocusable::OnTurnSystemNextCharacter);
}

void CameraFocusable::Activate2()
{
	Activateable::Activate2();
}

void CameraFocusable::Deactivate1()
{
	Activateable::Deactivate1();
}

void CameraFocusable::Deactivate2()
{
	Activateable::Deactivate2();

	Get<EventBus>().Get(EventType::GameMapLoaded) -= new EventInvoker<CameraFocusable, GameMapEventArgs>(this, &CameraFocusable::OnGameMapLoaded);
	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) -= new EventInvoker<CameraFocusable, GameObjectEventArgs>(this, &CameraFocusable::OnTurnSystemNextCharacter);
}

void CameraFocusable::Process(const Time l_gameTime)
{
	auto& renderTarget = Get<Game::Shared>()->GetRenderWindow();

	auto moveVectorF = this->GetOwner()->GetPosition();//renderTarget.mapPixelToCoords(moveVectorI);

	m_isLeftLocked = false;
	m_isRightLocked = false;
	m_isUpLocked = false;
	m_isDownLocked = false;

	// check if viewport is inside the map boundaries
	if (moveVectorF.x - m_view.getSize().x / 2 < 0)
	{
		moveVectorF.x = m_view.getSize().x / 2;
		m_isLeftLocked = true;
	}
	else if (moveVectorF.x + m_view.getSize().x / 2 > m_mapSize.left + m_mapSize.width)
	{
		moveVectorF.x = (m_mapSize.left + m_mapSize.width) - m_view.getSize().x / 2;
		m_isRightLocked = true;
	}

	if (moveVectorF.y - m_view.getSize().y / 2 < 0)
	{
		moveVectorF.y = m_view.getSize().y / 2;
		m_isUpLocked = true;
	}
	else if (moveVectorF.y + m_view.getSize().y / 2 > m_mapSize.top + m_mapSize.height)
	{
		moveVectorF.y = (m_mapSize.top + m_mapSize.height) - m_view.getSize().y / 2;
		m_isDownLocked = true;
	}

	m_view.setCenter(moveVectorF);
	renderTarget.setView(m_view);
}

bool CameraFocusable::IsMovementDirectionLocked(KeyBindingName::EntryPtr l_name) const
{
	switch (l_name->GetValue())
	{
	case KeyBindingName::ValueMoveLeft:
		return m_isLeftLocked;
		break;

	case KeyBindingName::ValueMoveRight:
		return m_isRightLocked;
		break;
	
	case KeyBindingName::ValueMoveUp:
		return m_isUpLocked;
		break;
	
	case KeyBindingName::ValueMoveDown:
		return m_isDownLocked;
		break;

	default:
		return false;
		break;
	}
}

void CameraFocusable::OnGameMapLoaded(GameMapEventArgs* l_args)
{
	m_mapSize = IntRect(Vector2i(0, 0), l_args->GetMapSize());
}

void CameraFocusable::OnTurnSystemNextCharacter(GameObjectEventArgs* l_args)
{
	GetOwner()->Move(l_args->GetGameObject()->GetPosition() - GetOwner()->GetPosition());
}
