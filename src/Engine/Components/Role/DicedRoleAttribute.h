#pragma once

#include "ARoleAttribute.h"
#include "CalculatedRoleAttribute.h"

using namespace std;

namespace ToD
{
	namespace Components
	{
		namespace Role
		{
			////////////////////////////////////////////////////////////
			/// \brief A role attribute
			///
			////////////////////////////////////////////////////////////
			class DicedRoleAttribute :
				public ARoleAttribute
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				/// \param l_owner The owner (Role) of the attribute
				/// \param l_attributeName The attribute name
				/// \param l_modifyingAttributeName 
				/// \param l_attributeModifier 
				///
				////////////////////////////////////////////////////////////
				DicedRoleAttribute(CharacterRole* l_owner, const string l_attributeName, const string l_modifyingAttributeName, const float l_attributeModifier);

				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				/// \param l_owner The owner (Role) of the attribute
				/// \param l_attributeName The attribute name
				/// \param l_modifyingAttribute
				/// \param l_attributeModifier 
				///
				////////////////////////////////////////////////////////////
				DicedRoleAttribute(CharacterRole* l_owner, const string l_attributeName, CalculatedRoleAttribute* l_modifyingAttribute, const float l_attributeModifier);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~DicedRoleAttribute();

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

				////////////////////////////////////////////////////////////
				/// \brief Get the current value of the attribute
				///
				/// \return the current attribute value
				///
				////////////////////////////////////////////////////////////
				virtual int GetCurrentValue() override;

				int GetLastValidValue() const;
				
				/// Methods
				
				/// Members
			private:
				CalculatedRoleAttribute*					m_modifyingAttribute;	///<
				float										m_attributeModifier;	///<
				int											m_lastValidValue;
			};
		}
	}
}
