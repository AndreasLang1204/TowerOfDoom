#include "stdafx.h"

#include "ReferenceType.h"

using namespace ToD;

ReferenceType::RuntimeID ReferenceType::GetRuntimeID() const
{
	return reinterpret_cast<RuntimeID>(this);
}
