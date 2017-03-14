#pragma once

#include "AEventInvoker.h"

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to invoke event handling functions.
		///
		////////////////////////////////////////////////////////////
		template<typename T, typename TArgs>
		class EventInvoker :
			public AEventInvoker
		{
			/// Typedefs
		public:
			////////////////////////////////////////////////////////////
			/// \brief Type definition of the event handling function type.
			///
			////////////////////////////////////////////////////////////
			typedef function<void(T*, TArgs*)>								EventHandlingFunction;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_target The event handling object.
			/// \param l_function The event handling function.
			///
			////////////////////////////////////////////////////////////
			EventInvoker(T* l_target, EventHandlingFunction l_function)
			: AEventInvoker(l_target)
			, m_target(l_target)
			, m_function(l_function)
			{
			}

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~EventInvoker() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override
			{
				return "ToD::Events::EventInvoker";
			}

			/// Methods
		protected:
			////////////////////////////////////////////////////////////
			/// \brief Invokes the event handling function.
			///
			/// \param l_args The event arguments.
			///
			////////////////////////////////////////////////////////////
			virtual void InvokeInner(EventArgs* l_args) const override
			{
				m_function(m_target, dynamic_cast<TArgs*>(l_args));
			}

			/// Members
		private:
			T*																m_target; ///< The event handling object.
			EventHandlingFunction											m_function; ///< The event handling function.
		};
	}
}
