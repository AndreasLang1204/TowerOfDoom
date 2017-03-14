#include "stdafx.h"

#include "EventDelegate.h"

using namespace ToD;
using namespace ToD::Events;

EventDelegate::EventDelegate(const EventType::EntryPtr l_eventType)
: ReferenceType()
, m_eventType(l_eventType)
, m_functions()
{
}

EventDelegate::~EventDelegate()
{
	for (auto pair : m_functions)
	{
		delete pair.second.first;
	}

	m_functions.clear();
}

ReferenceType::RuntimeType EventDelegate::GetRuntimeType() const
{
	return "ToD::Events::EventDelegate";
}

void EventDelegate::Raise(EventArgs* l_args) const
{
	auto functions = vector<InvokerFunctionPair>();

	for (auto& pair : m_functions)
	{
		functions.push_back(pair.second);
	}

	for (auto& pair : functions)
	{
		auto invoker = pair.first;
		auto function = pair.second;

		function(invoker, l_args);
	}
}

void EventDelegate::DeleteInvoker(const AEventInvoker* l_invoker)
{
	auto target = l_invoker->GetTarget();

	if (m_functions.find(target) == m_functions.end())
	{
		return;
	}

	delete m_functions[target].first;

	m_functions.erase(target);
}

void EventDelegate::operator+=(AEventInvoker* l_invoker)
{
	DeleteInvoker(l_invoker);

	m_functions[l_invoker->GetTarget()] = pair<AEventInvoker*, EventInvokerFunction>(l_invoker, &AEventInvoker::Invoke);
}

void EventDelegate::operator-=(AEventInvoker* l_invoker)
{
	DeleteInvoker(l_invoker);
	
	delete l_invoker;
}
