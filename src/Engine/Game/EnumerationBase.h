#pragma once

using namespace std;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Base declaration of an enumeration with additional functionality.
	///
	////////////////////////////////////////////////////////////
	class EnumerationBase
	{
		/// Nested classes & structs
	public:
		////////////////////////////////////////////////////////////
		/// \brief Represents a single value of an enumeration.
		///
		////////////////////////////////////////////////////////////
		class Entry
		{
			/// Constructors, desctructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor.
			///
			/// \param l_key The entry key.
			/// \param l_value The entry value.
			///
			////////////////////////////////////////////////////////////
			Entry(const string l_key, const int l_value);

			////////////////////////////////////////////////////////////
			/// \brief The constructor (copy constructor).
			///
			/// \param l_other The Entry to copy.
			///
			////////////////////////////////////////////////////////////
			Entry(const Entry& l_other) IsDeleted__;

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~Entry() IsDefault__;

			/// Properties
		public:
			////////////////////////////////////////////////////////////
			/// \brief Gets the entry value.
			///
			/// \return The entry value.
			///
			////////////////////////////////////////////////////////////
			int GetValue() const;

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Retrieves a string that represents the entry.
			///
			/// \return The representation as string.
			///
			////////////////////////////////////////////////////////////
			string ToString() const;

			////////////////////////////////////////////////////////////
			/// \brief Retrieves a string that represents the entry.
			///
			/// \return The representation as const char*.
			///
			////////////////////////////////////////////////////////////
			const char* ToCharacters() const;

			/// Operators
		public:
			////////////////////////////////////////////////////////////
			/// \brief Prevents copying a Entry via the copy operator.
			///
			/// \param l_other The Entry to copy.
			///
			/// \return The copied Entry object.
			///
			////////////////////////////////////////////////////////////
			Entry& operator=(const Entry& l_other) IsDeleted__;

			/// Members
		private:
			string															m_key; ///< The entry key.
			int																m_value; ///< The entry value.
		};

		////////////////////////////////////////////////////////////
		/// \brief Compares entries by their value.
		///
		////////////////////////////////////////////////////////////
		struct EntryComparer
		{
			////////////////////////////////////////////////////////////
			/// \brief Compares sprites by their x position.
			///
			/// \param lhs The first entry.
			/// \param rhs The first entry.
			///
			/// \return true when lhs x is less than rhs x.
			///
			////////////////////////////////////////////////////////////
			bool operator() (const Entry* lhs, const Entry* rhs) const;
		};

		/// Typedefs
	public:
		////////////////////////////////////////////////////////////
		/// \brief Definition of the enumeration entry pointer type.
		///
		////////////////////////////////////////////////////////////
		typedef const Entry*												EntryPtr;

		////////////////////////////////////////////////////////////
		/// \brief Definition of the enumeration entry dictionary type.
		///
		////////////////////////////////////////////////////////////
		typedef unordered_map<string, EntryPtr>								EntryDictionary;

	private:
		////////////////////////////////////////////////////////////
		/// \brief Definition of the enumeration dictionary type.
		///
		////////////////////////////////////////////////////////////
		typedef unordered_map<string, EntryDictionary>						EnumerationDictionary;

		/// Constructors, desctructors
	protected:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		EnumerationBase() IsDefault__;

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		virtual ~EnumerationBase() IsDefault__;

		/// Properties
	public:
		////////////////////////////////////////////////////////////
		/// \brief Retrieves all entries of an enumeration.
		///
		/// \param l_namespace The runtime type of the target enumeration.
		///
		/// \exception std::exception: l_namespace references an enumeration that was never created.
		///
		////////////////////////////////////////////////////////////
		static const EntryDictionary& GetValues(const string l_namespace);

		/// Methods
	protected:
		////////////////////////////////////////////////////////////
		/// \brief Creates an enumeration.
		///
		/// \param l_namespace The runtime type of the target enumeration.
		///
		/// \exception std::exception: l_namespace references an enumeration that was already created.
		///
		////////////////////////////////////////////////////////////
		static void Create(const string l_namespace);

		////////////////////////////////////////////////////////////
		/// \brief Adds an entry to an enumeration.
		///
		/// \param l_namespace The runtime type of the target enumeration.
		/// \param l_entryPtr The entry to add.
		///
		/// \exception std::exception: l_namespace references an enumeration that was never created.
		///
		////////////////////////////////////////////////////////////
		static void Add(const string l_namespace, EntryPtr l_entryPtr);

		////////////////////////////////////////////////////////////
		/// \brief Removes all entries of an enumeration.
		///
		/// \param l_namespace The runtime type of the target enumeration.
		///
		/// \exception std::exception: l_namespace references an enumeration that was never created.
		///
		////////////////////////////////////////////////////////////
		static void Remove(const string l_namespace);

		////////////////////////////////////////////////////////////
		/// \brief Parses a string to an entry of an enumeration.
		///
		/// \param l_namespace The runtime type of the target enumeration.
		/// \param l_key The string to parse.
		///
		/// \exception std::exception: l_namespace references an enumeration that was never created.
		/// \exception std::exception: l_key references an invalid enumeration entry.
		///
		////////////////////////////////////////////////////////////
		static EntryPtr FromString(const string l_namespace, const string l_key);

		////////////////////////////////////////////////////////////
		/// \brief Parses an integer to an entry of an enumeration.
		///
		/// \param l_namespace The runtime type of the target enumeration.
		/// \param l_value The integer to parse.
		///
		/// \exception std::exception: l_namespace references an enumeration that was never created.
		/// \exception std::exception: l_value does not exist as enumeration entry.
		///
		////////////////////////////////////////////////////////////
		static EntryPtr FromValue(const string l_namespace, const int l_value);

		/// Members
	private:
		static EnumerationDictionary										s_values; ///< Contains all enumeration entries of all enumerations.
	};
}

#ifndef EnumerationDeclaration__
#define EnumerationDeclaration__(name, value)								static EnumerationBase::EntryPtr name; static constexpr int Value##name = value;
#endif

#ifndef EnumerationDefinition__
#define EnumerationDefinition__(enumeration, name)							EnumerationBase::EntryPtr enumeration::name = new Entry(#name, Value##name);
#endif
