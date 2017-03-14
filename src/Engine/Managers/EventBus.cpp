#include "stdafx.h"

#include "EventBus.h"

using namespace ToD;
using namespace ToD::Managers;

EventBus::EventBus()
: SharedObject()
, m_delegates()
{
}

EventBus::~EventBus()
{
	for (auto pair : m_delegates)
	{
		auto delegate = pair.second;

		delete delegate;
	}

	m_delegates.clear();
}

ReferenceType::RuntimeType EventBus::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType EventBus::RuntimeType()
{
	return "ToD::Managers::EventBus";
}

EventDelegate& EventBus::Get(const EventType::EntryPtr l_eventType)
{
	if (m_delegates.find(l_eventType) == m_delegates.end())
	{
		m_delegates[l_eventType] = new EventDelegate(l_eventType);
	}

	return *m_delegates[l_eventType];
}

void EventBus::Raise(const EventType::EntryPtr l_eventType, EventArgs* l_args)
{
	if (m_delegates.find(l_eventType) != m_delegates.end())
	{
		m_delegates[l_eventType]->Raise(l_args);
	}

	delete l_args;
}
