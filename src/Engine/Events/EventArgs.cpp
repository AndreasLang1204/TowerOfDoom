#include "stdafx.h"

#include "EventArgs.h"

using namespace ToD;
using namespace ToD::Events;

ReferenceType::RuntimeType EventArgs::GetRuntimeType() const
{
	return "ToD::EventArgs";
}
