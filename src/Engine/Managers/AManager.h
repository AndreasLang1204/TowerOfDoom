#pragma once

#include "ObjectContainer.h"
#include "../Components/AGameComponent.h"

using namespace ToD::Components;

namespace ToD
{
	namespace Managers
	{
		////////////////////////////////////////////////////////////
		/// \brief Provides functionality of a generic manager.
		///
		/// \typename TManager The manager type.
		///
		////////////////////////////////////////////////////////////
		template<typename TManager>
		class AManager :
			public ObjectContainer::SharedObject
		{
			/// Nested classes & structs
		public:
			////////////////////////////////////////////////////////////
			/// \brief Used to integrate the game object manager in the game logic.
			///
			////////////////////////////////////////////////////////////
			class Component :
				public AGameComponent
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor.
				///
				/// \param l_owner Owner of the game component.
				/// \param l_manager The manager to integrate in the game logic.
				///
				////////////////////////////////////////////////////////////
				Component(GameObject* l_owner, TManager* l_manager);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~Component() IsDefault__;

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
				virtual void Process(const Time l_gameTime) override
				{
					m_manager->Update(l_gameTime);
				}

				/// Members
			private:
				TManager*													m_manager; ///< The manager to integrate in the game logic.
			};

			/// Constructors, destructors
		protected:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			AManager() IsDefault__;

		public:
			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~AManager() IsDefault__;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Updates the currently active game state.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Update(const Time l_gameTime) IsAbstract__;
		};
	}
}
