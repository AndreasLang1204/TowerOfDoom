#include "stdafx.h"

#include "SfmlEventEventArgs.h"

using namespace ToD;
using namespace ToD::Events;

SfmlEventEventArgs::SfmlEventEventArgs(Event l_event)
: EventArgs()
, m_event(l_event)
{
}

ReferenceType::RuntimeType SfmlEventEventArgs::GetRuntimeType() const
{
	return "ToD::Events::SfmlEventEventArgs";
}

Event SfmlEventEventArgs::GetEvent() const
{
	return m_event;
}
