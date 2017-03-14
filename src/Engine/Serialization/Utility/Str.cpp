#include "stdafx.h"

#include "Str.h"

using namespace ToD;
using namespace ToD::Serialization::Utility;

ReferenceType::RuntimeType Str::GetRuntimeType() const
{
	return "ToD::Serialization::Utility::Str";
}

bool Str::ToBool(const char* l_value)
{
	/// http://stackoverflow.com/questions/31965097/convert-char-to-bool-passing-bool-to-main
	auto stringStream = stringstream();
	stringStream << l_value;

	auto value = false;
	if (stringStream >> boolalpha >> value)
	{
		return value;
	}

	throw exception("Can not parse string to boolean.");
}
