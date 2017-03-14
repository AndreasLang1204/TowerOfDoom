#include "stdafx.h"

#include "GameLogic.h"

using namespace sf;
using namespace std;
using namespace ToD;
using namespace ToD::Managers;

GameLogic::GameLogic()
: m_updateOrder()
, m_logicLayers()
{
}

GameLogic::~GameLogic()
{
	m_updateOrder.clear();
	m_logicLayers.clear();
}

ReferenceType::RuntimeType GameLogic::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType GameLogic::RuntimeType()
{
	return "ToD::Managers::GameLogic";
}

void GameLogic::RegisterComponent(const RuntimeID l_objectIentifier, AGameComponent* l_component)
{
	LOG(INFO) << "registered component for Object with ID: " << l_objectIentifier;

	auto componentType = l_component->GetType();

	if (m_logicLayers.find(componentType) == m_logicLayers.end())
	{
		LOG(INFO) << "Component type is not in update order";
	}
	else
	{
		m_logicLayers[componentType][l_objectIentifier].push_back(l_component);
	}
}

void GameLogic::RemoveComponent(const RuntimeID l_objectIentifier)
{
	for (auto& layer : m_logicLayers)
	{
		if (layer.second.find(l_objectIentifier) != layer.second.end())
		{
			layer.second.erase(l_objectIentifier);
		}
	}
}

void GameLogic::SetUpdateOrder(const ComponentTypeArray l_updateOrder)
{
	m_updateOrder = l_updateOrder;

	for (auto type : l_updateOrder)
	{
		m_logicLayers[type] = ComponentDictionary();
	}
}

void GameLogic::Update(const Time l_gameTime)
{
	for (auto layer : m_updateOrder)
	{
		for (auto pair : m_logicLayers[layer])
		{
			auto& components = pair.second;
			for (auto component : components)
			{
				if (component->GetIsActivated())
				{
					component->Process(l_gameTime);
				}
			}
		}
	}
}
