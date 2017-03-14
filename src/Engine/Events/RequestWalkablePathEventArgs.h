#pragma once

#include "RequestWalkableAreaEventArgs.h"
#include "../Calc/Value.h"

using namespace sf;
using namespace ToD::Calc;

namespace ToD
{
	namespace Events
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds information about a game object.
		///
		////////////////////////////////////////////////////////////
		class RequestWalkablePathEventArgs :
			public RequestWalkableAreaEventArgs
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_object The game object realting with the event.
			/// \param l_movementRange The movement range.
			/// \param l_targetCellPosition The target cell's position.
			/// 
			////////////////////////////////////////////////////////////
			RequestWalkablePathEventArgs(GameObject* l_object, const Value::Unit l_movementRange, const Vector2i l_targetCellPosition);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			virtual ~RequestWalkablePathEventArgs() IsDefault__;

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
			/// \brief Gets the target cell's position.
			///
			/// \return The target cell's position.
			///
			////////////////////////////////////////////////////////////
			Vector2i GetTargetCellPosition() const;

			/// Members
		private:
			Vector2i														m_targetCellPosition; ///< The target cell's position.
		};
	}
}
