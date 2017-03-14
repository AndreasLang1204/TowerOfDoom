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
			/// \brief Used to update and render the credit screen.
			///
			////////////////////////////////////////////////////////////
			class GUICreditScreen :
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
				explicit GUICreditScreen(GameObject* l_owner);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~GUICreditScreen() IsDefault__;

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
				/// \brief Gets a value indicating whether the exit screen button was clicked or not.
				///
				/// \return A value indicating whether the exit screen button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				bool GetIsExitScreenClicked() const;

				////////////////////////////////////////////////////////////
				/// \brief Sets a value indicating whether the exit screen button was clicked or not.
				///
				/// \param l_value A value indicating whether the exit screen button was clicked or not.
				///
				////////////////////////////////////////////////////////////
				void SetIsExitScreenClicked(const bool l_value);

				/// Methods
			public:
				////////////////////////////////////////////////////////////
				/// \brief Loads all used widgets.
				///
				////////////////////////////////////////////////////////////
				virtual void LoadWidgets() override;

				/// Members
			private:
				bool														m_isExitScreenClicked; ///< Indicates whether the exit screen button was clicked or not.
			};
		}
	}
}