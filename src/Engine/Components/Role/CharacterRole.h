#pragma once

#include "../AGameComponent.h"
#include "CreatureTypeTag.h"
#include "CalculatedRoleAttribute.h"
#include "DicedRoleAttribute.h"

using namespace std;
using namespace ToD::Components::Role;

namespace ToD
{
	namespace Components
	{
		namespace Role
		{
			////////////////////////////////////////////////////////////
			/// \brief A character role 
			///
			////////////////////////////////////////////////////////////
			class CharacterRole :
				public AGameComponent
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief Default constructor
				///
				/// \param l_owner Owner of the game component.
				/// \param l_name The role name.
				/// \param l_level The role level.
				/// \param l_types The creature types to set.
				///
				////////////////////////////////////////////////////////////
				explicit CharacterRole(GameObject* l_owner, const string l_name, const int l_level, initializer_list<CreatureTypeTag::EntryPtr> l_types = {});

				////////////////////////////////////////////////////////////
				/// \brief Default destructor
				///
				////////////////////////////////////////////////////////////
				~CharacterRole();

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
				/// \brief Gets the role name.
				///
				/// \return The role name.
				///
				////////////////////////////////////////////////////////////
				string GetName() const;

				////////////////////////////////////////////////////////////
				/// \brief Gets the role level.
				///
				/// \return The role level.
				///
				////////////////////////////////////////////////////////////
				int GetLevel() const;

				////////////////////////////////////////////////////////////
				/// \brief 
				///
				/// \return 
				///
				////////////////////////////////////////////////////////////
				void AddMainAttribute(CalculatedRoleAttribute* l_attribute);

				////////////////////////////////////////////////////////////
				/// \brief 
				///
				/// \return 
				///
				////////////////////////////////////////////////////////////
				void AddHelpAttribute(DicedRoleAttribute* l_attribute);

				////////////////////////////////////////////////////////////
				/// \brief 
				///
				/// \return 
				///
				////////////////////////////////////////////////////////////
				CalculatedRoleAttribute* GetMainAttribute(const string l_attributeName);

				////////////////////////////////////////////////////////////
				/// \brief 
				///
				/// \return 
				///
				////////////////////////////////////////////////////////////
				DicedRoleAttribute* GetHelpAttribute(const string l_attributeName);

				////////////////////////////////////////////////////////////
				/// \brief Checks if the role has the specified CreatureType.
				///
				/// \return True the role has the CreatureType in question; otherwise false.
				///
				////////////////////////////////////////////////////////////
				bool HasCreatureType(CreatureTypeTag::EntryPtr l_creatureType) const;

				////////////////////////////////////////////////////////////
				/// \brief Checks if the role has any specified CreatureType.
				///
				/// \return True if the role has any CreatureType in question; otherwise false.
				///
				////////////////////////////////////////////////////////////
				bool HasAnyCreatureType(initializer_list<CreatureTypeTag::EntryPtr> l_creatureTypes) const;

				////////////////////////////////////////////////////////////
				/// \brief Adds a CreatureType to the role.
				///
				/// \param l_creatureType The CreatureType to add.
				///
				////////////////////////////////////////////////////////////
				void AddCreatureType(CreatureTypeTag::EntryPtr l_creatureType);

				////////////////////////////////////////////////////////////
				/// \brief Removes a CreatureType from the role.
				///
				/// \param l_creatureType The CreatureType to remove.
				///
				////////////////////////////////////////////////////////////
				void RemoveCreatureType(CreatureTypeTag::EntryPtr l_creatureType);

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

				/// Members
			private:
				string												m_name;		///< The role name.
				int													m_level;	///< The role level.
				unordered_map<string, CalculatedRoleAttribute*>		m_mainAttributes;
				unordered_map<string, DicedRoleAttribute*>			m_helpAttributes;
				vector<CreatureTypeTag::EntryPtr>					m_creatureTypes;
			};
		}
	}
}