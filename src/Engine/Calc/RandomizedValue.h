#pragma once

#include "Value.h"

namespace ToD
{
	namespace Calc
	{
		////////////////////////////////////////////////////////////
		/// \brief A calculatable value.
		///
		////////////////////////////////////////////////////////////
		class RandomizedValue :
			public Value
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			/// \param l_min The minimal allowed value (is included in value range).
			/// \param l_max The maximal allowed value (is included in value range).
			///
			////////////////////////////////////////////////////////////
			RandomizedValue(const Unit l_min, const Unit l_max);

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~RandomizedValue() IsDefault__;

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
			/// \brief Evaluates the value.
			///
			////////////////////////////////////////////////////////////
			virtual void Evaluate() override;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Evaluates the value.
			///
			////////////////////////////////////////////////////////////
			void EvaluateInner();

			/// Members
		private:
			Unit															m_min; ///< The minimal allowed value (is included in value range).
			Unit															m_max; ///< The maximal allowed value (is included in value range).
		};
	}
}