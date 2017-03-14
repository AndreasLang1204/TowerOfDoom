#pragma once

#include "Renderable.h"

namespace ToD
{
	namespace Events
	{
		class EventArgs;
		class GameMapEventArgs;
		class MouseEventArgs;
	}
}

using namespace sf;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to update a grid cursor.
		///
		////////////////////////////////////////////////////////////
		class GridCursorLogic :
			public AGameComponent
		{
			/// Constructors & destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			///
			////////////////////////////////////////////////////////////
			explicit GridCursorLogic(GameObject* l_owner);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GridCursorLogic() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Sets a value indicating whether the grid cursor is visible or not.
			///
			/// \param l_value The value to set.
			///
			////////////////////////////////////////////////////////////
			void SetIsVisible(const bool l_value);

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
			/// \brief Processes the map loaded event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGameMapLoaded(GameMapEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the mouse cursor moved event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnMouseMoved(MouseEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the gui element entering event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGuiElementEntering(EventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the gui element leaving event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGuiElementLeaving(EventArgs* l_args);

			/// Members
		private:
			Vector2f														m_position; ///< The cursor position in world coordinates.
			int																m_gridX; ///< The cursor grid x position.
			int																m_gridY; ///< The cursor grid y position.
			bool															m_isVisible; ///< Indicates whether the grid cursor is visible or not.
			Vector2i														m_tileSize; ///< The tile size in pixel.
		};
	}
}
