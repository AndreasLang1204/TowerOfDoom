#include "stdafx.h"

#include "File.h"

using namespace ToD;
using namespace ToD::Serialization::Utility;

ReferenceType::RuntimeType File::GetRuntimeType() const
{
	return "ToD::Serialization::FileUtility";
}

void File::EnsureFileExtension(const string l_filePath, const string l_extension)
{
	if (l_filePath.find(l_extension) == string::npos)
	{
		throw exception(string("The file \"" + l_filePath + "\" is no " + l_extension + " file.").c_str());
	}
}
