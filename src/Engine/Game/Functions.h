#pragma once

#include "stdafx.h"

using namespace sf;
using namespace std;

namespace ToD
{
	namespace Functions
	{
		////////////////////////////////////////////////////////////
		/// \brief Normalizes a vector.
		///
		/// \param l_vector The vector to normalize.
		///
		/// \return The normalized vector.
		///
		////////////////////////////////////////////////////////////
		inline Vector2f Normalize(const Vector2f l_vector)
		{
			auto tmp = sqrtf(powf(l_vector.x, 2.f) + powf(l_vector.y, 2.f));
			if (tmp >= numeric_limits<float>::epsilon())
			{
				return 1.f / tmp * l_vector;
			}

			return Vector2f();
		}

		////////////////////////////////////////////////////////////
		/// \brief Converts an integer vector to a float vector.
		///
		/// \param l_vector The integer vector to convert.
		///
		/// \return The resulting float vector.
		///
		////////////////////////////////////////////////////////////
		inline Vector2f ToVector2f(const Vector2i& l_vector)
		{
			auto x = static_cast<float>(l_vector.x);
			auto y = static_cast<float>(l_vector.y);

			return Vector2f(x, y);
		}
	}
}
