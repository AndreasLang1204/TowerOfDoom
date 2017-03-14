#pragma once

#include "EnumerationBase.h"

using namespace ToD;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Base declaration of an enumeration with additional functionality.
	///
	/// \typename T The enumeration tye.
	///
	////////////////////////////////////////////////////////////
	template<typename T>
	class Enumeration :
		public EnumerationBase
	{
		/// Constructors, desctructors
	protected:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		Enumeration() IsDefault__;

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		virtual ~Enumeration() IsDefault__;

		/// Properties
	public:
		////////////////////////////////////////////////////////////
		/// \brief Retrieves all entries of the enumeration.
		///
		////////////////////////////////////////////////////////////
		static const EntryDictionary& GetValues()
		{
			return EnumerationBase::GetValues(T::RuntimeType());
		}

		/// Methods
	public:
		////////////////////////////////////////////////////////////
		/// \brief Initializes the enumeration.
		///
		////////////////////////////////////////////////////////////
		static void Initialize();

		////////////////////////////////////////////////////////////
		/// \brief Cleanup the enumeration.
		///
		////////////////////////////////////////////////////////////
		static void Cleanup()
		{
			EnumerationBase::Remove(T::RuntimeType());
		}

	private:
		////////////////////////////////////////////////////////////
		/// \brief Creates the enumeration.
		///
		/// \exception std::exception: l_namespace references an enumeration that was already created.
		///
		////////////////////////////////////////////////////////////
		static void Create()
		{
			EnumerationBase::Create(T::RuntimeType());
		}

		////////////////////////////////////////////////////////////
		/// \brief Adds an entry to the enumeration.
		///
		/// \param l_entryPtr The entry to add.
		///
		////////////////////////////////////////////////////////////
		static void Add(EntryPtr l_entryPtr)
		{
			EnumerationBase::Add(T::RuntimeType(), l_entryPtr);
		}

	public:
		////////////////////////////////////////////////////////////
		/// \brief Parses a string to an entry of the enumeration.
		///
		/// \param l_key The string to parse.
		///
		/// \exception std::exception: l_key references an invalid enumeration entry.
		///
		////////////////////////////////////////////////////////////
		static EntryPtr FromString(const string l_key)
		{
			return EnumerationBase::FromString(T::RuntimeType(), l_key);
		}

		////////////////////////////////////////////////////////////
		/// \brief Parses an integer to an entry of an enumeration.
		///
		/// \param l_value The integer to parse.
		///
		/// \exception std::exception: l_value does not exist as enumeration entry.
		///
		////////////////////////////////////////////////////////////
		static EntryPtr FromValue(const int l_value)
		{
			return EnumerationBase::FromValue(T::RuntimeType(), l_value);
		}

		/// Members
	protected:
		static int															s_nextIndex; ///< The next entry index.
	};
}
