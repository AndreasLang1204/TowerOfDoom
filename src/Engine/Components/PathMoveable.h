#pragma once

#include "AGameComponent.h"
#include "MapLayerCellInfo.h"
#include "../Events/WalkablePathEventArgs.h"

namespace ToD
{
	namespace Events
	{
		class GameObjectEventArgs;
		class WalkablePathEventArgs;
	}
}

using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to move a playable character on the map.
		///
		////////////////////////////////////////////////////////////
		class PathMoveable :
			public AGameComponent
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			///
			////////////////////////////////////////////////////////////
			explicit PathMoveable(GameObject* l_owner);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~PathMoveable() IsDefault__;

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
			/// \brief Processes the playable character deactivated event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnPlayableCharacterDeactivated(GameObjectEventArgs* l_args);

				////////////////////////////////////////////////////////////
			/// \brief Processes the turn system next character event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemNextCharacter(GameObjectEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system character response walkable path event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemCharacterResponseWalkablePath(WalkablePathEventArgs* l_args);

			/// Members
		private:
			WalkablePathEventArgs::WalkablePath								m_path; ///< The path to walk.
			MapLayerCellInfo*												m_target; ///< The target cell.
			float															m_walkSpeed; ///< The walkspeed in milliseconds per tile.
			float															m_delay; ///< The current walk delay time in milliseconds.
		};
	}
}
