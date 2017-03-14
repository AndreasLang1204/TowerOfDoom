#pragma once

#include "../../../Game/ReferenceType.h"

namespace ToD
{
	namespace Components
	{
		namespace CharacterControllers
		{
			class ACharacterControllerInstance;
		}
	}
}

using namespace ToD::Components::CharacterControllers;

namespace ToD
{
	namespace Components
	{
		namespace CharacterControllers
		{
			namespace ControllerCommands
			{
				////////////////////////////////////////////////////////////
				/// \brief Represents a command executed by a playable character.
				///
				////////////////////////////////////////////////////////////
				class ACharacterControllerCommand :
					public ReferenceType
				{
					/// Constructors, destructors
				public:
					////////////////////////////////////////////////////////////
					/// \brief The constructor.
					///
					/// \param l_owner The command owner.
					///
					////////////////////////////////////////////////////////////
					explicit ACharacterControllerCommand(ACharacterControllerInstance* l_owner);

					////////////////////////////////////////////////////////////
					/// \brief The destructor.
					///
					////////////////////////////////////////////////////////////
					~ACharacterControllerCommand() IsDefault__;

					/// Properties
				public:
					////////////////////////////////////////////////////////////
					/// \brief Gets the command owner.
					///
					/// \return The command owner.
					///
					////////////////////////////////////////////////////////////
					ACharacterControllerInstance* GetOwner() const;

					/// Methods
				public:
					////////////////////////////////////////////////////////////
					/// \brief Executes the command.
					///
					////////////////////////////////////////////////////////////
					virtual void Execute() IsAbstract__;

					/// Members
				private:
					ACharacterControllerInstance*							m_owner; ///< The command owner.
				};
			}
		}
	}
}
