#pragma once

#include <TGUI/TGUI.hpp>

#include "../AGameComponent.h"
#include "../Renderable.h"

namespace ToD
{
	namespace Events
	{
		class SfmlEventEventArgs;
	}
}

using namespace sf;
using namespace tgui;
using namespace ToD::Events;

namespace ToD
{
	namespace Components
	{
		namespace GUI
		{
			////////////////////////////////////////////////////////////
			/// \brief Used to render a GUI.
			///
			////////////////////////////////////////////////////////////
			class AGUIComponent :
				public Renderable
			{
			public:
				////////////////////////////////////////////////////////////
				/// \brief The constructor.
				///
				/// \param l_owner Owner of the game component.
				///
				////////////////////////////////////////////////////////////
				explicit AGUIComponent(GameObject* l_owner);

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~AGUIComponent();

				/// Properties
			public:
				////////////////////////////////////////////////////////////
				/// \brief Sets a value indicating whether the GUI is active or not.
				///
				/// \param l_value The value to set.
				///
				////////////////////////////////////////////////////////////
				void SetIsActive(const bool l_value);

				/// Methods
			public:
				////////////////////////////////////////////////////////////
				/// \brief Processes pending work.
				///
				/// \param l_gameTime Provides a snapshot of timing values.
				///
				////////////////////////////////////////////////////////////
				virtual void Process(const Time l_gameTime) override;

				////////////////////////////////////////////////////////////
				/// \brief Loads all used widgets.
				///
				////////////////////////////////////////////////////////////
				virtual void LoadWidgets() IsAbstract__;
				
			private:
				////////////////////////////////////////////////////////////
				/// \brief Processes the sfml event raised event.
				///
				/// \param l_args Event arguments.
				///
				////////////////////////////////////////////////////////////
				void OnSfmlEventRaised(SfmlEventEventArgs* l_args);

			protected:
				Gui*														m_gui; ///< The TGUI gui object.
				bool														m_isActive; ///< Indicates whether the GUI is active or not.
			};
		}
	}
}
