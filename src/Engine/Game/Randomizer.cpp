#include "stdafx.h"

#include "Randomizer.h"

using namespace ToD;

ReferenceType::RuntimeType Randomizer::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType Randomizer::RuntimeType()
{
	return "ToD::Randomizer";
}

void Randomizer::SetSeed(const unsigned l_seed)
{
	srand(l_seed);
}

int Randomizer::Random()
{
	m_value += rand();

	return m_value;
}

int Randomizer::Random(const int l_min, const int l_max)
{
	Random();

	auto range = 1 + l_max - l_min;

	return l_min + m_value % range;
}
