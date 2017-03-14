#pragma once

#include "ACharacterControllerInstance.h"

namespace ToD
{
	namespace Components
	{
		namespace CharacterControllers
		{
			////////////////////////////////////////////////////////////
			/// \brief Represents the artifical playable character controller instance.
			///
			////////////////////////////////////////////////////////////
			class ArtificialCharacterControllerInstance :
				public ACharacterControllerInstance
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor.
				///
				/// \param l_owner Owner of the game component.
				///
				////////////////////////////////////////////////////////////
				explicit ArtificialCharacterControllerInstance(GameObject* l_owner);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				virtual ~ArtificialCharacterControllerInstance() IsDefault__;

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
			};
		}
	}
}
