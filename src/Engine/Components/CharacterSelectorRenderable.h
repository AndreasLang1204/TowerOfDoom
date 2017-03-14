#pragma once

#include "Renderable.h"

namespace ToD
{
	namespace Events
	{
		class GameObjectEventArgs;
	}
}

using namespace sf;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to render a character selector.
		///
		////////////////////////////////////////////////////////////
		class CharacterSelectorRenderable :
			public Renderable
		{
			/// Constructors & destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_texture The sprite sheet to use.
			/// \param l_player determines which selector will be used
			///
			////////////////////////////////////////////////////////////
			CharacterSelectorRenderable(GameObject* l_owner, Texture* l_texture, const bool l_player);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~CharacterSelectorRenderable() IsDefault__;

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
			/// \brief Avtivates the component (first step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Activate1() override;

			////////////////////////////////////////////////////////////
			/// \brief Avtivates the component (second step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Activate2() override;

			////////////////////////////////////////////////////////////
			/// \brief Deactivates the component (first step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Deactivate1() override;

			////////////////////////////////////////////////////////////
			/// \brief Deactivates the component (second step).
			///
			/// \override Always call base class method.
			///
			////////////////////////////////////////////////////////////
			virtual void Deactivate2() override;

			////////////////////////////////////////////////////////////
			/// \brief Processes pending work.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Process(const Time l_gameTime) override;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system next character event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemNextCharacter(GameObjectEventArgs* l_args);

			/// Members
		private:
			Sprite															m_selector; ///< The cursor sprite.
			bool															m_isVisible; ///< Indicates whether the grid cursor is visible or not.
		};
	}
}
