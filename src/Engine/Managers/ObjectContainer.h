#pragma once

#include "../Game/ReferenceType.h"

using namespace std;

namespace ToD
{
	namespace Managers
	{
		////////////////////////////////////////////////////////////
		/// \brief Shares common used objects among application components.
		///
		////////////////////////////////////////////////////////////
		class ObjectContainer :
			public ReferenceType
		{
			/// Nested classes & structs
		public:
			class SharedObject :
				public ReferenceType
			{
				/// Constructors & destructors
			protected:
				////////////////////////////////////////////////////////////
				/// \brief The constructor (default constructor).
				///
				////////////////////////////////////////////////////////////
				SharedObject() IsDefault__;

			public:
				////////////////////////////////////////////////////////////
				/// \brief The destructor.
				///
				////////////////////////////////////////////////////////////
				virtual ~SharedObject() IsDefault__;
			};

			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Type definition of the object dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<string, SharedObject*>					ObjectDictionary;

			/// Constructors & destructors
		private:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			ObjectContainer() IsDefault__;

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~ObjectContainer() IsDefault__;

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
			/// \brief Clears the object container and removes all objects.
			///
			////////////////////////////////////////////////////////////
			static void Clear();

			////////////////////////////////////////////////////////////
			/// \brief Adds an object to the container.
			///
			/// \param l_type The object type.
			/// \param l_object The object instance.
			///
			////////////////////////////////////////////////////////////
			static void AddObject(const string l_type, SharedObject* l_object);

			////////////////////////////////////////////////////////////
			/// \brief Removes an object to the container.
			///
			/// \param l_type The object type.
			///
			////////////////////////////////////////////////////////////
			static void RemoveObject(const string l_type);

			////////////////////////////////////////////////////////////
			/// \brief Checks whether an object is registered  or not.
			///
			/// \return True if an object of the specified type is registered; otherwise false.
			///
			////////////////////////////////////////////////////////////
			template<typename T>
			static bool Has()
			{
				return Has(T::RuntimeType());
			}

			////////////////////////////////////////////////////////////
			/// \brief Gets an object.
			///
			/// \return The requested object.
			///
			/// \exception std::exception: No shared object of the specified type was registered before.
			///
			////////////////////////////////////////////////////////////
			template<typename T>
			static T& Get()
			{
				if (Has<T>())
				{
					return *dynamic_cast<T*>(s_objects[T::RuntimeType()]);
				}

				throw exception(string("The requested object " + T::RuntimeType() + " does not exist.").c_str());
			}

		private:
			////////////////////////////////////////////////////////////
			/// \brief Checks whether an object is registered  or not.
			///
			/// \param l_type The object type.
			///
			/// \return True if an object of the specified type is registered; otherwise false.
			///
			////////////////////////////////////////////////////////////
			static bool Has(const string l_type);

			/// Members
		private:
			static ObjectDictionary											s_objects; ///< Contains all objects.
		};

		////////////////////////////////////////////////////////////
		/// \brief Gets a shared object.
		///
		/// \return The requested shared object.
		///
		/// \exception std::exception: No shared object of the specified type was registered before.
		///
		////////////////////////////////////////////////////////////
		template<typename T>
		static T& Get()
		{
			return ObjectContainer::Get<T>();
		}
	}
}
