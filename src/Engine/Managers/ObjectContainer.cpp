#include "stdafx.h"

#include "ObjectContainer.h"

using namespace ToD;
using namespace ToD::Managers;

ObjectContainer::ObjectDictionary ObjectContainer::s_objects = ObjectDictionary();

ReferenceType::RuntimeType ObjectContainer::GetRuntimeType() const
{
	return "ToD::Managers::ObjectContainer";
}

void ObjectContainer::Clear()
{
	for (auto pair : s_objects)
	{
		auto object = pair.second;

		delete object;
	}

	s_objects.clear();
}

void ObjectContainer::AddObject(const string l_type, SharedObject* l_object)
{
	s_objects[l_type] = l_object;
}

void ObjectContainer::RemoveObject(const string l_type)
{
	if (!Has(l_type))
	{
		throw exception(string("The requested object " + l_type + " does not exist.").c_str());
	}

	delete s_objects[l_type];
	s_objects.erase(l_type);
}

bool ObjectContainer::Has(const string l_type)
{
	return s_objects.find(l_type) != s_objects.end();
}
