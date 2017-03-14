#include "stdafx.h"

#include "PathMoveable.h"

#include "MapLayerCellInfo.h"
#include "../Game/Constants.h"
#include "../Events/EventInvoker.h"
#include "../Events/GameObjectEventArgs.h"
#include "../Events/WalkablePathEventArgs.h"
#include "../Managers/EventBus.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Events;
using namespace ToD::Managers;

PathMoveable::PathMoveable(GameObject* owner)
: AGameComponent(owner, GameComponentType::Transition)
, m_path()
, m_target(nullptr)
, m_walkSpeed(Constants::Physics::WalkSpeed)
, m_delay()
{
}

ReferenceType::RuntimeType PathMoveable::GetRuntimeType() const
{
	return "ToD::Components::PathMoveable";
}

void PathMoveable::Activate1()
{
	Activateable::Activate1();

	Get<EventBus>().Get(EventType::TurnSystemNextCharacter) += new EventInvoker<PathMoveable, GameObjectEventArgs>(this, &PathMoveable::OnTurnSystemNextCharacter);
	Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) += new EventInvoker<PathMoveable, GameObjectEventArgs>(this, &PathMoveable::OnPlayableCharacterDeactivated);
}

void PathMoveable::Activate2()
{
	Activateable::Activate2();
}

void PathMoveable::Deactivate1()
{
	Activateable::Deactivate1();
}

void PathMoveable::Deactivate2()
{
	Activateable::Deactivate2();
}

void PathMoveable::Process(const Time l_gameTime)
{
	if(m_path.size() > 0)
	{
		m_delay += l_gameTime.asMilliseconds();
		
		if (m_delay < m_walkSpeed)
		{
			return;
		}

		m_delay -= m_walkSpeed;

		auto position = (*m_path.begin())->GetWorldPosition();

		GetOwner()->Move(position - GetOwner()->GetPosition());

		m_path.pop_front();

		Get<EventBus>().Raise(EventType::TurnSystemCharacterWalkablePathUpdated, new WalkablePathEventArgs(m_path, m_target));
	}
	else if (m_target != nullptr)
	{
		Get<EventBus>().Raise(EventType::TurnSystemCharacterEndsMoving, new GameObjectEventArgs(GetOwner()));

		m_target = nullptr;
	}
}

void PathMoveable::OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args)
{
	if (l_args->GetGameObject() == GetOwner())
	{
		Get<EventBus>().Get(EventType::TurnSystemNextCharacter) -= new EventInvoker<PathMoveable, GameObjectEventArgs>(this, &PathMoveable::OnTurnSystemNextCharacter);
		Get<EventBus>().Get(EventType::PlayableCharacterDeactivated) -= new EventInvoker<PathMoveable, GameObjectEventArgs>(this, &PathMoveable::OnPlayableCharacterDeactivated);
		Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkablePath) -= new EventInvoker<PathMoveable, WalkablePathEventArgs>(this, &PathMoveable::OnTurnSystemCharacterResponseWalkablePath);
	}
}

void PathMoveable::OnTurnSystemNextCharacter(GameObjectEventArgs* l_args)
{
	if (l_args->GetGameObject() == GetOwner())
	{
		Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkablePath) += new EventInvoker<PathMoveable, WalkablePathEventArgs>(this, &PathMoveable::OnTurnSystemCharacterResponseWalkablePath);
	}
	else
	{
		Get<EventBus>().Get(EventType::TurnSystemCharacterResponseWalkablePath) -= new EventInvoker<PathMoveable, WalkablePathEventArgs>(this, &PathMoveable::OnTurnSystemCharacterResponseWalkablePath);
	}
}

void PathMoveable::OnTurnSystemCharacterResponseWalkablePath(WalkablePathEventArgs* l_args)
{
	m_path = l_args->GetPath();
	m_target = l_args->GetTarget();

	Get<EventBus>().Raise(EventType::TurnSystemCharacterStartsMoving, new GameObjectEventArgs(GetOwner()));
	Get<EventBus>().Raise(EventType::TurnSystemCharacterWalkablePathUpdated, new WalkablePathEventArgs(m_path, m_target));
}
