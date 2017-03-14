#pragma once

#include "GameObjectEventArgs.h"
#include "../Calc/Value.h"

using namespace ToD::Calc;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a game object.
		///
		////////////////////////////////////////////////////////////
		class RequestWalkableAreaEventArgs :
			public GameObjectEventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_object The game object realting with the event.
			/// \param l_movementRange The movement range.
			/// 
			////////////////////////////////////////////////////////////
			RequestWalkableAreaEventArgs(GameObject* l_object, const int l_movementRange);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~RequestWalkableAreaEventArgs() IsDefault__;

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
			/// \brief Gets the movement range.
			///
			/// \return The movement range.
			///
			////////////////////////////////////////////////////////////
			Value::Unit GetMovementRange() const;

			/// Members
		private:
			int														m_movementRange; ///< The movement range.
		};
	}
}
