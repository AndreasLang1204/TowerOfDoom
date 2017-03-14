#include "stdafx.h"

#include "StateFactory.h"

#include "../States/StartScreen.h"
#include "../States/GameplayScreen.h"
#include "../States/CreditScreen.h"

using namespace ToD;
using namespace ToD::Factories;
using namespace ToD::States;

ReferenceType::RuntimeType StateFactory::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType StateFactory::RuntimeType()
{
	return "ToD::Factories::StateFactory";
}

AGameState* StateFactory::Create(const string l_name) const
{
	if (l_name == StartScreen::Name)
	{
		return new StartScreen();
	}

	if (l_name == GameplayScreen::Name)
	{
		return new GameplayScreen();
	}

	if (l_name == CreditScreen::Name)
	{
		return new CreditScreen();
	}
	
	throw exception(("Can not create screen " + l_name + ". There is no such screen").c_str());
}
