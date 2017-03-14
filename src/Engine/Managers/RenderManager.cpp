#include "stdafx.h"

#include "RenderManager.h"

using namespace sf;
using namespace std;
using namespace ToD;
using namespace ToD::Managers;

RenderManager::RenderManager()
: m_layers()
{
}

RenderManager::~RenderManager()
{
	m_layers.clear();
}

ReferenceType::RuntimeType RenderManager::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType RenderManager::RuntimeType()
{
	return "ToD::Managers::RenderManager";
}

void RenderManager::RegisterComponent(const RuntimeID l_objectID, Renderable* l_component)
{
	m_layers[l_component->GetPriority()][l_objectID].push_back(l_component);
}

void RenderManager::RemoveComponent(const RuntimeID l_objectID)
{
	// erase all entries for Object with UID: l_objectID in all layers
	for (auto& pair : m_layers)
	{
		auto& layer = pair.second;

		layer.erase(l_objectID);
	}
}

void RenderManager::Render() const
{
	for (auto& pair1 : m_layers)
	{
		auto& layer = pair1.second;

		for (auto& pair2 : layer)
		{
			auto& components = pair2.second;
			for (auto component : components)
			{
				if (component->GetIsActivated())
				{
					component->Process(Time());
				}
			}
		}
	}
}
