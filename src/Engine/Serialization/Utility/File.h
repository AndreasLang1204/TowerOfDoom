#pragma once

#include "../Game/ReferenceType.h"

using namespace std;

namespace ToD
{
	namespace Serialization
	{
		namespace Utility
		{
			////////////////////////////////////////////////////////////
			/// \brief Provides functionality to easily deal with files and file paths.
			///
			////////////////////////////////////////////////////////////
			class File :
				public ReferenceType
			{
				/// Constructors, destructors
			private:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				////////////////////////////////////////////////////////////
				File() IsDefault__;

				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				~File() IsDefault__;

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
				/// \brief Ensures that a file path ends with a specific extension.
				///
				/// \param l_filePath The file path to check.
				/// \param l_extension The extension to ensure.
				///
				/// \exception std::exception: The file path does not end with the specified extension.
				///
				////////////////////////////////////////////////////////////
				static void EnsureFileExtension(const string l_filePath, const string l_extension);
			};
		}
	}
}
