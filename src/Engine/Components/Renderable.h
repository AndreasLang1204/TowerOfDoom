#pragma once

#include "AGameComponent.h"
#include "RenderablePriority.h"

namespace ToD
{
	namespace Components
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to render a game object.
		///
		////////////////////////////////////////////////////////////
		class Renderable :
			public AGameComponent
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// Initializes a new instance of the ToD::Renderable class.
			///
			/// \param l_owner Owner of the game component.
			/// \param l_renderPriority The render priority.
			///
			////////////////////////////////////////////////////////////
			Renderable(GameObject* l_owner, const RenderablePriority::EntryPtr l_renderPriority);

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the render priority.
			///
			/// \return The render priority.
			///
			////////////////////////////////////////////////////////////
			RenderablePriority::EntryPtr GetPriority() const;

			/// Members
		private:
			RenderablePriority::EntryPtr									m_priority; ///< The render priority.
		};
	}
}
