#pragma once

#include "ObjectContainer.h"
#include "../Events/EventArgs.h"
#include "../Events/EventType.h"
#include "../Events/EventDelegate.h"

using namespace std;
using namespace ToD::Events;

namespace ToD
{
	namespace Managers
	{
		////////////////////////////////////////////////////////////
		/// \brief Notifies listeners about events.
		///
		////////////////////////////////////////////////////////////
		class EventBus :
			public ObjectContainer::SharedObject
		{
			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Type definition of the event delegate dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<EventType::EntryPtr, EventDelegate*>		DelegateDictionary;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			EventBus();

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~EventBus();

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

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the delegate for a specific event type.
			///
			/// \param l_eventType The event type.
			///
			////////////////////////////////////////////////////////////
			EventDelegate& Get(const EventType::EntryPtr l_eventType);

			////////////////////////////////////////////////////////////
			/// \brief Raises an event and notifies all listeners.
			///
			/// \param l_eventType The event type.
			/// \param l_args Event arguments.
			///
			/// \return l_args is deleted when the method returns.
			///
			////////////////////////////////////////////////////////////
			void Raise(const EventType::EntryPtr l_eventType, EventArgs* l_args);

			/// Members
		private:
			DelegateDictionary												m_delegates; ///< Contains used delegates.
		};
	}
}