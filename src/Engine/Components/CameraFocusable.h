#pragma once

#include "AGameComponent.h"
#include "../Game/KeyBindingName.h"

namespace ToD
{
	namespace Events
	{
		class GameMapEventArgs;
		class GameObjectEventArgs;
		class TurnSystemCharacterChangedEventArgs;
	}
}

using namespace sf;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to attach a view.
		///
		////////////////////////////////////////////////////////////
		class CameraFocusable :
			public AGameComponent
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_view The used view.
			/// \param l_zoom The zoom (default = 1.0)
			///
			////////////////////////////////////////////////////////////
			CameraFocusable(GameObject* l_owner, View l_view, const float l_zoom = 1.0f);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~CameraFocusable() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

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

			bool IsMovementDirectionLocked(KeyBindingName::EntryPtr l_name) const;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Processes the map loaded event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnGameMapLoaded(GameMapEventArgs* l_args);

			////////////////////////////////////////////////////////////
			/// \brief Processes the turn system next character event.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void OnTurnSystemNextCharacter(GameObjectEventArgs* l_args);

			/// Members
		private:
			View															m_view; ///< The attached view.
			IntRect															m_mapSize; ///< The map size in pixel.
			bool															m_isLeftLocked;
			bool														    m_isRightLocked;
			bool															m_isUpLocked;
			bool															m_isDownLocked;
		};
	}
}