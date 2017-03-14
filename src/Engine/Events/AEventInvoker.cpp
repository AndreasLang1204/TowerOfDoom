#include "stdafx.h"

#include "AEventInvoker.h"

using namespace ToD;
using namespace ToD::Events;

AEventInvoker::AEventInvoker(void* l_target)
: ReferenceType()
, m_target(l_target)
{
}

void* AEventInvoker::GetTarget() const
{
	return m_target;
}

void AEventInvoker::Invoke(const AEventInvoker* l_invoker, EventArgs* l_args)
{
	l_invoker->InvokeInner(l_args);
}
