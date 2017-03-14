#pragma once

#include "../Game/ReferenceType.h"

namespace ToD
{
	namespace Components
	{
		namespace Role
		{
			class CharacterRole;
		}
	}
}

using namespace std;
using namespace ToD::Components::Role;

namespace ToD
{
	namespace Components
	{
		namespace Role
		{
			////////////////////////////////////////////////////////////
			/// \brief base class for role attributes
			///
			////////////////////////////////////////////////////////////
			class ARoleAttribute :
				public ReferenceType
			{
				/// Constructors, destructors
			protected:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				/// \param l_owner The owner (Role) of the attribute
				/// \param l_attributeName The attribute name
				///
				////////////////////////////////////////////////////////////
				ARoleAttribute(CharacterRole* l_owner, const string l_attributeName);

			public:
				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				virtual ~ARoleAttribute() IsDefault__;

				/// Properties
			public:
				////////////////////////////////////////////////////////////
				/// \brief Gets name of the attribute
				///
				/// \return the attribute name
				///
				////////////////////////////////////////////////////////////
				string GetName() const;

				////////////////////////////////////////////////////////////
				/// \brief Get the current value of the attribute
				///
				/// \return the current attribute value
				///
				////////////////////////////////////////////////////////////
				virtual int GetCurrentValue() IsAbstract__;

				////////////////////////////////////////////////////////////
				/// \brief Gets the role the attribute belongs to
				///
				/// \return the owner (Role) of the attribute
				///
				////////////////////////////////////////////////////////////
				CharacterRole* GetRole();

				/// Methods
			public:

				/// Members
			protected:
				string									m_name;			///< the name of the attribute
				int										m_currentValue; ///< the current value of the attribute
				CharacterRole*							m_owner;		///< the role component the attribute belongs to
			};
		}
	}
}
