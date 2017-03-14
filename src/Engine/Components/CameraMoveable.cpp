#include "stdafx.h"

#include "CameraMoveable.h"

#include "../Game/Constants.h"
#include "../Game/Functions.h"
#include "../Game/GameObject.h"
#include "../Managers/InputManager.h"
#include "CameraFocusable.h"

using namespace sf;
using namespace ToD;
using namespace ToD::Components;
using namespace ToD::Managers;

CameraMoveable::CameraMoveable(GameObject* owner)
: AGameComponent(owner, GameComponentType::Transition)
, m_speed(Constants::Physics::ObjectSpeed)
{
}

ReferenceType::RuntimeType CameraMoveable::GetRuntimeType() const
{
	return "ToD::Components::CameraMoveable";
}

void CameraMoveable::Process(const Time l_gameTime)
{
	auto& iM = Get<InputManager>();
	auto focusComponent = GetOwner()->GetComponent<CameraFocusable>();

	auto move = Vector2f();

	if (iM.GetBindingKeyState(KeyBindingName::MoveRight) == KeyBindingState::WasPressed &&
		!focusComponent->IsMovementDirectionLocked(KeyBindingName::MoveRight))
	{
		move += Vector2f(1.f, 0);
	}

	if (iM.GetBindingKeyState(KeyBindingName::MoveLeft) == KeyBindingState::WasPressed &&
		!focusComponent->IsMovementDirectionLocked(KeyBindingName::MoveLeft))
	{
		move += Vector2f(-1.f, 0);
	}

	if (iM.GetBindingKeyState(KeyBindingName::MoveUp) == KeyBindingState::WasPressed &&
		!focusComponent->IsMovementDirectionLocked(KeyBindingName::MoveUp))
	{
		move += Vector2f(0, -1.f);
	}

	if (iM.GetBindingKeyState(KeyBindingName::MoveDown) == KeyBindingState::WasPressed &&
		!focusComponent->IsMovementDirectionLocked(KeyBindingName::MoveDown))
	{
		move += Vector2f(0, 1.f);
	}

	move = Functions::Normalize(move);
	move *= m_speed * l_gameTime.asSeconds();

	GetOwner()->Move(move);
}
