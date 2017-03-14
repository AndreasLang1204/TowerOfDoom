#pragma once

#include "stdafx.h"

using namespace std;

namespace ToD
{
	namespace Constants
	{
		namespace Texture
		{
			const string StartScreenBackground = "Game.Screen.StartScreen.Background";
			const string GameplayScreenBorder = "Game.Screen.GameplayScreen.GUIBorder";
			const string GameplayScreenGUIUnitFrame = "Game.Screen.GameplayScreen.GUIUnitFrame";
			const string CreditScreenBackground = "Game.Screen.CreditScreen.Background";
			const string GameplayScreenGridCursor = "Game.Screen.GameplayScreen.Cursors";
			const string CharacterSelector = "Game.Character.Selector";
		}

		namespace Attribute
		{
			const string ActionPoints = "ActionPoints";
			const string HitPoints = "HitPoints";
			const string Dexterity = "Dexterity";
			const string Will = "Will";
			const string Constitution = "Constitution";
			const string Initiative = "Initiative";
		}
		
		namespace Physics
		{
			constexpr float ObjectSpeed = 100.f;
			constexpr float WalkSpeed = 200.f; ///< The character walk speed in milliseconds per tile.
		}

		namespace Visual
		{
			const sf::Color WalkableArea = sf::Color(0, 255, 0, 63); ///< Color of the walkable area.
		}
	}
}
