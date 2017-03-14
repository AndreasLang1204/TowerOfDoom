#pragma once

#include "../Game/ReferenceType.h"

using namespace std;

namespace ToD
{
	namespace Serialization
	{
		namespace Utility
		{
			class Str :
				public ReferenceType
			{
				/// Constructors, destructors
			private:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				////////////////////////////////////////////////////////////
				Str() IsDefault__;

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~Str() IsDefault__;

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
				/// \brief Converts a string to the specified type.
				///
				/// \param l_value The value to convert.
				///
				/// \exception std::exception: The conversion failed.
				///
				////////////////////////////////////////////////////////////
				template<typename T>
				static T To(const char* l_value)
				{
					/// http://stackoverflow.com/questions/4024806/how-to-convert-from-const-char-to-unsigned-int-c
					auto stringStream = stringstream();
					stringStream << l_value;

					T value;
					if (stringStream >> value)
					{
						return value;
					}

					throw exception("Can not parse string to specified type.");
				}

				////////////////////////////////////////////////////////////
				/// \brief Converts a string to a bool.
				///
				/// \param l_value The value to convert.
				///
				/// \exception std::exception: The conversion failed.
				///
				////////////////////////////////////////////////////////////
				static bool ToBool(const char* l_value);
			};
		}
	}
}
