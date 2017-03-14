#pragma once

#include "AGameComponent.h"
#include "Renderable.h"

using namespace sf;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to render a Sprite object.
		///
		////////////////////////////////////////////////////////////
		class SpriteRenderable :
			public Renderable
		{
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// sets the TextureRect of m_sprite to the size of texture
			///
			/// \param l_owner Owner of the game component.
			/// \param l_renderPriority The render priority.
			/// \param l_texture The sprite sheet to use.
			///
			////////////////////////////////////////////////////////////
			SpriteRenderable(GameObject* l_owner, RenderablePriority::EntryPtr l_renderPriority, sf::Texture* l_texture);

			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// sets the TextureRect of m_sprite to the size srcRect
			///
			/// \param l_owner Owner of the game component.
			/// \param l_renderPriority The render priority.
			/// \param l_texture The sprite sheet to use.
			/// \param l_srcRect Specifies the frame to select from the sprite sheet.
			///
			////////////////////////////////////////////////////////////
			SpriteRenderable(GameObject* l_owner, RenderablePriority::EntryPtr l_renderPriority, sf::Texture* l_texture, const IntRect l_srcRect);

			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// sets the TextureRect of m_sprite to the size srcRect and the scale to scale
			///
			/// \param l_owner Owner of the game component.
			/// \param l_renderPriority The render priority.
			/// \param l_texture The sprite sheet to use.
			/// \param l_srcRect Specifies the frame to select from the sprite sheet.
			/// \param l_scale Scales the rendered sprite.
			///
			////////////////////////////////////////////////////////////
			SpriteRenderable(GameObject* l_owner, RenderablePriority::EntryPtr l_renderPriority, sf::Texture* l_texture, const IntRect l_srcRect, const Vector2f l_scale);

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

			////////////////////////////////////////////////////////////
			/// \brief Gets the sprite rendered by the component.
			///
			/// \return The sprite rendered by the component.
			///
			////////////////////////////////////////////////////////////
			Sprite GetSprite() const;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Processes pending work.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Process(const Time l_gameTime) override;

			/// Members
		private:
			Sprite															m_sprite; ///< The sprite rendered by the component.
		};

	}
}
