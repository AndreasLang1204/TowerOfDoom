#include "stdafx.h"

#include "Value.h"

using namespace ToD;
using namespace ToD::Calc;

Value::Value(const Unit l_value)
: ReferenceType()
, m_value(l_value)
{
}

ReferenceType::RuntimeType Value::GetRuntimeType() const
{
	return "ToD::Calc::Value";
}

Value::Unit Value::GetValue() const
{
	return m_value;
}

void Value::SetValue(const Unit l_value)
{
	m_value = l_value;
}

void Value::Evaluate()
{
}
