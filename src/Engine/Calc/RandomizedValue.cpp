#include "stdafx.h"

#include "RandomizedValue.h"
#include "../Game/Randomizer.h"

using namespace ToD;
using namespace ToD::Calc;
using namespace ToD::Managers;

RandomizedValue::RandomizedValue(const Unit l_min, const Unit l_max)
: Value()
, m_min(l_min)
, m_max(l_max)
{
	EvaluateInner();
}

ReferenceType::RuntimeType RandomizedValue::GetRuntimeType() const
{
	return "ToD::Calc::RandomizedValue";
}

void RandomizedValue::Evaluate()
{
	EvaluateInner();
}

void RandomizedValue::EvaluateInner()
{
	SetValue(Get<Randomizer>().Random(m_min, m_max));
}
