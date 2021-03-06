#pragma once

using namespace std;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Prevents from getting copied.
	///
	////////////////////////////////////////////////////////////
	class ReferenceType
	{
		/// Typedefs
	public:
		////////////////////////////////////////////////////////////
		/// \brief Definition of the reference type runtime type.
		///
		////////////////////////////////////////////////////////////
		typedef string														RuntimeType;

		////////////////////////////////////////////////////////////
		/// \brief Definition of the reference type runtime identifier type.
		///
		////////////////////////////////////////////////////////////
		typedef unsigned int												RuntimeID;

		/// Constructors, destructors
	public:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		ReferenceType() IsDefault__;

		////////////////////////////////////////////////////////////
		/// \brief The constructor (copy constructor).
		///
		/// \param l_other The ReferenceType to copy.
		///
		////////////////////////////////////////////////////////////
		ReferenceType(const ReferenceType& l_other) IsDeleted__;

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		virtual ~ReferenceType() IsDefault__;

		/// Properties
	public:
		////////////////////////////////////////////////////////////
		/// \brief Gets the static runtime type.
		///
		/// \return The static runtime type.
		///
		////////////////////////////////////////////////////////////
		virtual RuntimeType GetRuntimeType() const IsAbstract__;

		////////////////////////////////////////////////////////////
		/// \brief Gets the runtime identifier based on the object pointer.
		///
		/// \return The runtime identifier based on the object pointer.
		///
		////////////////////////////////////////////////////////////
		RuntimeID GetRuntimeID() const;

		/// Operators
	public:
		////////////////////////////////////////////////////////////
		/// \brief Prevents copying a ReferenceType via the copy operator.
		///
		/// \param l_other The ReferenceType to copy.
		///
		/// \return The copied ReferenceType object.
		///
		////////////////////////////////////////////////////////////
		ReferenceType& operator=(const ReferenceType& l_other) IsDeleted__;
	};
}
