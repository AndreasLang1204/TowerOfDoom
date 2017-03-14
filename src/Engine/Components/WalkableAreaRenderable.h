#pragma once

#include "AGameComponent.h"
#include "MapLayerCellInfo.h"
#include "Renderable.h"
#include "../Events/WalkableAreaEventArgs.h"

namespace ToD
{
	namespace Events
	{
		class GameMapEventArgs;
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
		/// \brief Used to render the walkable area of a character.
		///
		////////////////////////////////////////////////////////////
		class WalkableAreaRenderable :
			public Renderable
		{
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			///
			////////////////////////////////////////////////////////////
			explicit WalkableAreaRenderable(GameObject* l_owner);

			////////////////////////////////////////////////////////////
			/// \brief The destructor,
			///
			////////////////////////////////////////////////////////////
			~WalkableAreaRenderable() IsDefault__;

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
			/// \brief Processes the map loaded event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGameMapLoaded(GameMapEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system response walkable area event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterResponseWalkableArea(WalkableAreaEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character starts moving event event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterStartsMoving(GameObjectEventArgs* l_args);

		private:
			RectangleShape														m_shape; ///< The sprite rendered by the component.
			WalkableAreaEventArgs::WalkableArea									m_walkableArea; ///< The walkable area to render.
		};
	}
}
