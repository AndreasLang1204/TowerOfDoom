#pragma once

#include "../Game/ReferenceType.h"

namespace ToD
{
	namespace Events
	{
		class EventArgs;
	}
}

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to invoke event handling functions.
		///
		////////////////////////////////////////////////////////////
		class AEventInvoker :
			public ReferenceType
		{
			/// Constructors, destructors
		protected:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_target The invoker target.
			///
			////////////////////////////////////////////////////////////
			explicit AEventInvoker(void* l_target);

		public:
			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~AEventInvoker() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the invoker target.
			///
			/// \return The invoker target.
			///
			////////////////////////////////////////////////////////////
			void* GetTarget() const;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Invokes the event handling function a specific invoker wraps.
			///
			/// \param l_invoker The invoker to use.
			/// \param l_args The event arguments.
			///
			////////////////////////////////////////////////////////////
			static void Invoke(const AEventInvoker* l_invoker, EventArgs* l_args);

		protected:
			////////////////////////////////////////////////////////////
			/// \brief Invokes the event handling function.
			///
			/// \param l_args The event arguments.
			///
			////////////////////////////////////////////////////////////
			virtual void InvokeInner(EventArgs* l_args) const IsAbstract__;

			/// Members
		private:
			void*															m_target; ///< The invoker target.
		};
	}
}
