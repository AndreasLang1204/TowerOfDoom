#include "stdafx.h"

#include "KeyboardKey.h"

using namespace ToD;

string KeyboardKey::RuntimeType()
{
	return "ToD::KeyboardKey";
}

Keyboard::Key KeyboardKey::FromString(const string l_value)
{
	if (l_value == "Space")
	{
		return Keyboard::Key::Space;
	}

	if (l_value == "Escape")
	{
		return Keyboard::Key::Escape;
	}

	if (l_value == "Down")
	{
		return Keyboard::Key::Down;
	}

	if (l_value == "Up")
	{
		return Keyboard::Key::Up;
	}

	if (l_value == "Num1")
	{
		return Keyboard::Key::Num1;
	}

	if (l_value == "Num2")
	{
		return Keyboard::Key::Num2;
	}

	if (l_value == "Num3")
	{
		return Keyboard::Key::Num3;
	}

	if (l_value == "W")
	{
		return Keyboard::Key::W;
	}

	if (l_value == "S")
	{
		return Keyboard::Key::S;
	}

	if (l_value == "A")
	{
		return Keyboard::Key::A;
	}

	if (l_value == "D")
	{
		return Keyboard::Key::D;
	}

	throw exception(string("The enumeration keyboard key " + l_value + " is not supported.").c_str());
}
