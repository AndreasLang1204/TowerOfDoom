#pragma once

#include "AEventInvoker.h"
#include "EventType.h"
#include "../Game/ReferenceType.h"

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Represents a single event handled by the event bus.
		///
		////////////////////////////////////////////////////////////
		class EventDelegate :
			public ReferenceType
		{
			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Type definition of the event invoker function type.
			///
			////////////////////////////////////////////////////////////
			typedef function<void(const AEventInvoker*, EventArgs*)>		EventInvokerFunction;

			////////////////////////////////////////////////////////////
			/// \brief Type definition of the invoker function pair type.
			///
			////////////////////////////////////////////////////////////
			typedef pair<AEventInvoker*, EventInvokerFunction>				InvokerFunctionPair;

			////////////////////////////////////////////////////////////
			/// \brief Type definition of the function dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<void*, InvokerFunctionPair>				FunctionDictionary;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_eventType The event type handled by the delegate.
			///
			////////////////////////////////////////////////////////////
			explicit EventDelegate(const EventType::EntryPtr l_eventType);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~EventDelegate();

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			virtual RuntimeType GetRuntimeType() const override;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Raises an event and notifies all listeners.
			///
			/// \param l_args Event arguments.
			///
			////////////////////////////////////////////////////////////
			void Raise(EventArgs* l_args) const;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Deletes an event invoker in the function dictionary that has the same specification than the specified one.
			///
			////////////////////////////////////////////////////////////
			void DeleteInvoker(const AEventInvoker* l_invoker);

			/// Operators
		public:
			////////////////////////////////////////////////////////////
			/// \brief Adds a new event invoker to the delegate.
			///
			/// \param l_invoker The invoker to add.
			///
			/// \return When this method returns if the added invoker has replaced another invoker, the other invoker was deleted.
			///
			////////////////////////////////////////////////////////////
			void operator+= (AEventInvoker* l_invoker);

			////////////////////////////////////////////////////////////
			/// \brief Removes an event invoker from the delegate.
			///
			/// \param l_invoker The invoker to remove.
			///
			/// \return When this method returns the removed invoker has been deleted.
			///
			////////////////////////////////////////////////////////////
			void operator-= (AEventInvoker* l_invoker);

			/// Members
		private:
			EventType::EntryPtr												m_eventType; ///< The event type handled by the delegate.
			FunctionDictionary												m_functions; ///< Functions handled by the delegate.
		};
	}
}
