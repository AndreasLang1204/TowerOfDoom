#pragma once

#include "AManager.h"
#include "../Game/KeyBinding.h"

namespace ToD
{
	namespace Events
	{
		class SfmlEventEventArgs;
	}
}

using namespace sf;
using namespace std;
using namespace ToD::Events;

namespace ToD
{
	namespace Managers
	{
		////////////////////////////////////////////////////////////
		/// \brief Contains all defined key bindings and keeps them up-to-date.
		///
		////////////////////////////////////////////////////////////
		class InputManager :
			public AManager<InputManager>
		{
			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Definition of the mouse state dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<Mouse::Button, KeyBinding*>				MouseStateDictionary;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the binding array type.
			///
			////////////////////////////////////////////////////////////
			typedef vector<KeyBinding*>										BindingArray;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the bindings by key dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<Keyboard::Key, KeyBinding*>				BindingsByKeyDictionary;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the bindings by name dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<KeyBindingName::EntryPtr, KeyBinding*>	BindingsByNameDictionary;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the key binding vector value type.
			///
			////////////////////////////////////////////////////////////
			typedef _Vector_val<_Simple_types<KeyBinding*>>					KeyBindingVectorValue;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the key binding const vector iterator type.
			///
			////////////////////////////////////////////////////////////
			typedef _Vector_const_iterator<KeyBindingVectorValue>			KeyBindingConstVectorIterator;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			InputManager();

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~InputManager();

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			static RuntimeType RuntimeType();

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Updates all bindings.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Update(const Time l_gameTime) override;

			////////////////////////////////////////////////////////////
			/// \brief Creates a binding to a keyboard key.
			///
			/// \param l_bindingName Name of the binding.
			/// \param l_key The bounded key.
			///
			////////////////////////////////////////////////////////////
			void Bind(const KeyBindingName::EntryPtr l_bindingName, const Keyboard::Key l_key);

			////////////////////////////////////////////////////////////
			/// \brief Removes a binding to a keyboard key.
			///
			/// \param l_bindingName Name of the binding.
			///
			////////////////////////////////////////////////////////////
			void Unbind(const KeyBindingName::EntryPtr l_bindingName);

			////////////////////////////////////////////////////////////
			/// \brief Gets the state of a binding.
			///
			/// \param l_bindingName Name of the binding.
			///
			/// \return The binding state.
			///
			////////////////////////////////////////////////////////////
			KeyBindingState::EntryPtr GetBindingKeyState(const KeyBindingName::EntryPtr l_bindingName);

			////////////////////////////////////////////////////////////
			/// \brief Get the current position of the mouse in window coordinates.
			///
			/// \param l_window Relativ window.
			///
			/// \return Current Position of the mouse.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetMousePos(const RenderWindow& l_window) const;

			////////////////////////////////////////////////////////////
			/// \brief Determines whether a mouse button is pressed.
			///
			/// \param l_button A mouse button.
			///
			/// \return true if the mouse button is pressed; otherwise false.
			///
			////////////////////////////////////////////////////////////
			bool IsMouseButtonPressed(const Mouse::Button l_button) const;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Gets a binding by its name.
			///
			/// \param l_bindingName Name of the binding.
			///
			/// \return An iterator that retrieves the binding value if it exists.
			///
			////////////////////////////////////////////////////////////
			KeyBindingConstVectorIterator GetBinding(const KeyBindingName::EntryPtr l_bindingName);

			////////////////////////////////////////////////////////////
			/// \brief Handles the SFML event raised event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnSfmlEventRaised(SfmlEventEventArgs* l_args);

			/// Members
		private:
			BindingArray													m_bindingList; ///< Contains all declared bindings.
			BindingsByKeyDictionary											m_bindingByKey; ///< Bindings grouped by the bounded key.
			BindingsByNameDictionary										m_bindingByName; ///< Bindings grouped by their name.
			MouseStateDictionary											m_mouseStates; ///< Contains all mouse states.
		};
	}
}
