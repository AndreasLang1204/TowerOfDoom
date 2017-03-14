#pragma once

#include "Enumeration.h"

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Defines supported binding names.
	///
	////////////////////////////////////////////////////////////
	class KeyBindingName :
		public Enumeration<KeyBindingName>
	{
		/// Enumeation values
	public:
		////////////////////////////////////////////////////////////
		/// \brief Name of the unused binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(None, 0)

		////////////////////////////////////////////////////////////
		/// \brief Name of the accept binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(Accept, 0)

		////////////////////////////////////////////////////////////
		/// \brief Name of the abort binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(Abort, 1)

		////////////////////////////////////////////////////////////
		/// \brief Name of the scroll-down binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(ScrollDown, 2)

		////////////////////////////////////////////////////////////
		/// \brief Name of the scroll-up binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(ScrollUp, 3)

		////////////////////////////////////////////////////////////
		/// \brief Name of the hotkey for ability 1 binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(HotkeyAbility1, 4)

		////////////////////////////////////////////////////////////
		/// \brief Name of the hotkey for ability 2 binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(HotkeyAbility2, 5)

		////////////////////////////////////////////////////////////
		/// \brief Name of the hotkey for ability 3 binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(HotkeyAbility3, 6)

		////////////////////////////////////////////////////////////
		/// \brief Name of the move-up binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(MoveUp, 7)

		////////////////////////////////////////////////////////////
		/// \brief Name of the move-down binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(MoveDown, 8)

		////////////////////////////////////////////////////////////
		/// \brief Name of the move-left binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(MoveLeft, 9)

		////////////////////////////////////////////////////////////
		/// \brief Name of the move-right binding.
		///
		////////////////////////////////////////////////////////////
		EnumerationDeclaration__(MoveRight, 10)

		/// Constructors, destructors
	private:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		KeyBindingName() IsDefault__;

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		~KeyBindingName() IsDefault__;

		/// Properties
	public:
		////////////////////////////////////////////////////////////
		/// \brief Gets the static runtime type.
		///
		/// \return The static runtime type.
		///
		////////////////////////////////////////////////////////////
		static string RuntimeType();
	};
}