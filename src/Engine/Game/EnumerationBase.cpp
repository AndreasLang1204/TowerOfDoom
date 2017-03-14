#include "stdafx.h"

#include "EnumerationBase.h"

using namespace ToD;

EnumerationBase::EnumerationDictionary EnumerationBase::s_values;

EnumerationBase::Entry::Entry(const string l_key, const int l_value)
	: m_key(l_key)
	, m_value(l_value)
{
}

int EnumerationBase::Entry::GetValue() const
{
	return m_value;
}

string EnumerationBase::Entry::ToString() const
{
	return m_key;
}

const char* EnumerationBase::Entry::ToCharacters() const
{
	return m_key.c_str();
}

bool EnumerationBase::EntryComparer::operator()(const Entry* lhs, const Entry* rhs) const
{
	return lhs->GetValue() < rhs->GetValue();
}

const EnumerationBase::EntryDictionary& EnumerationBase::GetValues(const string l_namespace)
{
	if (s_values.find(l_namespace) == s_values.end())
	{
		throw exception(string("The enumeration " + l_namespace + " does not exist.").c_str());
	}

	return s_values[l_namespace];
}

void EnumerationBase::Create(const string l_namespace)
{
	if (s_values.find(l_namespace) != s_values.end())
	{
		throw exception(string("The enumeration " + l_namespace + " already exists.").c_str());
	}

	s_values[l_namespace];
}

void EnumerationBase::Add(const string l_namespace, EntryPtr l_entryPtr)
{
	if (s_values.find(l_namespace) == s_values.end())
	{
		throw exception(string("The enumeration " + l_namespace + " does not exist.").c_str());
	}

	s_values[l_namespace][l_entryPtr->ToString()] = l_entryPtr;
}

void EnumerationBase::Remove(const string l_namespace)
{
	if (s_values.find(l_namespace) == s_values.end())
	{
		throw exception(string("The enumeration " + l_namespace + " does not exist.").c_str());
	}

	s_values.erase(l_namespace);
}

EnumerationBase::EntryPtr EnumerationBase::FromString(const string l_namespace, const string l_key)
{
	if (s_values.find(l_namespace) == s_values.end())
	{
		throw exception(string("The enumeration " + l_namespace + " does not exist.").c_str());
	}

	auto enumeration = s_values[l_namespace];

	if (enumeration.find(l_key) == enumeration.end())
	{
		throw exception(string("The enumeration " + l_namespace + " has no entry " + l_key + ".").c_str());
	}

	return enumeration[l_key];
}

EnumerationBase::EntryPtr EnumerationBase::FromValue(const string l_namespace, const int l_value)
{
	if (s_values.find(l_namespace) == s_values.end())
	{
		throw exception(string("The enumeration " + l_namespace + " does not exist.").c_str());
	}

	auto enumeration = s_values[l_namespace];
	
	for (auto& pair : enumeration)
	{
		auto entry = pair.second;
		if (entry->GetValue() == l_value)
		{
			return entry;
		}
	}

	throw exception(string("The enumeration " + l_namespace + " has no entry with value " + to_string(l_value) + ".").c_str());
}
