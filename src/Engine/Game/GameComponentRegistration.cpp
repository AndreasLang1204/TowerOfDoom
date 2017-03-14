#include "stdafx.h"

#include "GameComponentRegistration.h"

#include "../Managers/EventBus.h"
#include "../Managers/GameLogic.h"
#include "../Managers/RenderManager.h"

using namespace ToD;
using namespace Events;
using namespace Managers;

ReferenceType::RuntimeType GameComponentRegistration::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GameComponentRegistration::RuntimeType()
{
	return "ToD::GameComponentRegistration";
}

void GameComponentRegistration::Register(const GameObject::Array l_objects) const
{
	auto& gameLogic = Get<GameLogic>();
	auto& renderManager = Get<RenderManager>();

	for (auto object : l_objects)
	{
		auto identifier = object->GetRuntimeID();

		for (auto component : *object)
		{
			switch (component->GetType()->GetValue())
			{
			case GameComponentType::ValueNone:
				break;

			case GameComponentType::ValueRender:
				renderManager.RegisterComponent(identifier, dynamic_cast<Renderable*>(component));
				break;

			default:
				gameLogic.RegisterComponent(identifier, component);
				break;
			}
		}
	}

	for (auto object : l_objects)
	{
		object->Activate1();
	}

	for (auto object : l_objects)
	{
		object->Activate2();
	}
}

void GameComponentRegistration::Deregister(const GameObject::Array l_objects) const
{
	auto& gameLogic = Get<GameLogic>();
	auto& renderManager = Get<RenderManager>();

	for (auto object : l_objects)
	{
		auto identifier = object->GetRuntimeID();

		for (auto component : *object)
		{
			switch (component->GetType()->GetValue())
			{
			case GameComponentType::ValueNone:
				break;

			case GameComponentType::ValueRender:
				renderManager.RemoveComponent(identifier);
				break;

			default:
				gameLogic.RemoveComponent(identifier);
				break;
			}
		}

	}

	for (auto object : l_objects)
	{
		object->Deactivate1();
	}

	for (auto object : l_objects)
	{
		object->Deactivate2();
	}
}
