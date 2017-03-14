#pragma once

#include "AGameComponent.h"

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to move a game object.
		///
		////////////////////////////////////////////////////////////
		class CameraMoveable :
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
			explicit CameraMoveable(GameObject* l_owner);

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
			/// \brief Processes pending work.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Process(const Time l_gameTime) override;

			/// Members
		private:
			float															m_speed; ///< The movement speed.
		};
	}
}
