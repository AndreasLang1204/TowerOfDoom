#pragma once

#include "ARoleAttribute.h"

using namespace std;

namespace ToD
{
	namespace Components
	{
		namespace Role
		{
			////////////////////////////////////////////////////////////
			/// \brief A calculated role attribute
			///
			////////////////////////////////////////////////////////////
			class CalculatedRoleAttribute :
				public ARoleAttribute
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				/// \param l_owner The owner (Role) of the attribute
				/// \param l_attributeName The attribute name
				/// \param l_levelModifiere A value modifier (used for maxValue calculation)
				/// \param l_baseValue The base value of the attribute
				/// \param l_canBeBelowBase Indicates if the current value can fall below m_baseValue
				///
				////////////////////////////////////////////////////////////
				CalculatedRoleAttribute(CharacterRole* l_owner, const string l_attributeName, const int l_levelModifiere, const int l_baseValue, const bool l_canBeBelowBase);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~CalculatedRoleAttribute();

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
				/// \brief Gets max. value of the attribute
				///
				/// \return the max. attribute value
				///
				////////////////////////////////////////////////////////////
				int GetMaxValue() const;

				////////////////////////////////////////////////////////////
				/// \brief Get the current value of the attribute
				///
				/// \return the current attribute value
				///
				////////////////////////////////////////////////////////////
				virtual int GetCurrentValue() override;

				/// Methods
			public:
				////////////////////////////////////////////////////////////
				/// \brief Changes the current value
				///
				/// \param l_modValue The modifiying value
				///
				////////////////////////////////////////////////////////////
				void ModCurrentValue(const int l_modValue);

			private:
				////////////////////////////////////////////////////////////
				/// \brief Updates the max. value of the attribute
				///
				///
				////////////////////////////////////////////////////////////
				void UpdateMaxValue();

				////////////////////////////////////////////////////////////
				/// \brief Processes the role level up event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				/*void OnRoleLevelUp(GameObjectEventArgs* l_args);*/

				/// Members
			private:
				int										m_maxValue;		 ///< the max. value of the attribute (claculated)
				int										m_baseValue;	 ///< the base value of the attribute (used for maxValue calculation)
				int										m_modValue;		 ///< value modifier (used for maxValue calculation)
				bool									m_canBeBelowBase;///< indicates if the current value can fall below the m_baseValue
			};
		}
	}
}
