#pragma once

#include "AGUIComponent.h"

namespace ToD
{
	namespace Events
	{
		class GameObjectEventArgs;
		class GridCellClickedEventArgs;
	}
}

using namespace std;
using namespace ToD::Components::GUI;
using namespace ToD::Events;

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
			class GUIGameplayScreen :
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
				explicit GUIGameplayScreen(GameObject* l_owner);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~GUIGameplayScreen();

				/// Properties
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
				/// \brief Loads all used widgets.
				///
				////////////////////////////////////////////////////////////
				virtual void LoadWidgets() override;

			private:
				////////////////////////////////////////////////////////////
				/// \brief Processes the turn system next character event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnTurnSystemNextCharacter(GameObjectEventArgs* l_args);

				////////////////////////////////////////////////////////////
				/// \brief Processes the grid cell clicked event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnGridCellClicked(GridCellClickedEventArgs* l_args);
			};
		}
	}
}
