#pragma once

#include "Renderable.h"

namespace ToD
{
	namespace Events
	{
		class GridCursorEventArgs;
	}
}

using namespace sf;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to render a grid cursor.
		///
		////////////////////////////////////////////////////////////
		class GridCursorRenderable :
			public Renderable
		{
			/// Constructors & destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_renderPriority The render priority.
			/// \param l_texture The sprite sheet to use.
			///
			////////////////////////////////////////////////////////////
			GridCursorRenderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority, Texture* l_texture);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GridCursorRenderable() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

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
			/// \brief Processes the grid cursor updated event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGridCursorUpdated(GridCursorEventArgs* l_args);

			/// Members
		private:
			Sprite															m_cursor; ///< The cursor sprite.
			bool															m_isVisible; ///< Indicates whether the grid cursor is visible or not.
		};
	}
}
