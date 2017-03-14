#pragma once

#include "AGUIComponent.h"

using namespace std;
using namespace ToD::Components;

namespace ToD
{
	namespace Components
	{
		namespace GUI
		{
			////////////////////////////////////////////////////////////
			/// \brief Used to update and render the start screen.
			///
			////////////////////////////////////////////////////////////
			class GUIStartScreen :
				public AGUIComponent
			{
				/// Constructors, destructors
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor.
				///
				/// \param l_owner Owner of the game component.
				///
				////////////////////////////////////////////////////////////
				explicit GUIStartScreen(GameObject* l_owner);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~GUIStartScreen() IsDefault__;

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
				/// \brief Gets a value indicating whether the start game button was clicked or not.
				///
				/// \return A value indicating whether the start game button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				bool GetIsStartGameClicked() const;

				////////////////////////////////////////////////////////////
				/// \brief Sets a value indicating whether the start game button was clicked or not.
				///
				/// \param l_value A value indicating whether the start game button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				void SetIsStartGameClicked(const bool l_value);

				////////////////////////////////////////////////////////////
				/// \brief Gets a value indicating whether the exit game button was clicked or not.
				///
				/// \return A value indicating whether the exit game button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				bool GetIsExitGameClicked() const;

				////////////////////////////////////////////////////////////
				/// \brief Sets a value indicating whether the exit game button was clicked or not.
				///
				/// \param l_value A value indicating whether the exit game button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				void SetIsExitGameClicked(const bool l_value);

				////////////////////////////////////////////////////////////
				/// \brief Gets a value indicating whether the credits button was clicked or not.
				///
				/// \return A value indicating whether thecredits button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				bool GetIsCredistClicked() const;

				////////////////////////////////////////////////////////////
				/// \brief Sets a value indicating whether the credits button was clicked or not.
				///
				/// \param l_value A value indicating whether the credits button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				void SetIsCredistClicked(const bool l_value);

				/// Methods
			public:
				////////////////////////////////////////////////////////////
				/// \brief Loads all used widgets.
				///
				////////////////////////////////////////////////////////////
				virtual void LoadWidgets() override;

				/// Members
			private:
				bool														m_isStartGameClicked; ///< Indicates whether the start game button was clicked or not.
				bool														m_isExitGameClicked; ///< Indicates whether the exit game button was clicked or not.
				bool														m_isCredistClicked; ///< Indicates whether the credits button was clicked or not.
			};
		}
	}
}