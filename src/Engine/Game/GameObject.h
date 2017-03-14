#pragma once

#include "Activateable.h"
#include "IEnumerable.h"
#include "GameObjectTag.h"
#include "../Components/AGameComponent.h"

using namespace std;
using namespace ToD::Components;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Provides functionality to update and render a single object of a game.
	///
	////////////////////////////////////////////////////////////
	class GameObject :
		public Activateable,
		public IEnumerable<vector<AGameComponent*>>
	{
		/// Typedefs
	public:
		////////////////////////////////////////////////////////////
		/// \brief Definition of the game object array type.
		///
		////////////////////////////////////////////////////////////
		typedef vector<GameObject*>											Array;

	private:
		////////////////////////////////////////////////////////////
		/// \brief Definition of the game component pointer array type.
		///
		////////////////////////////////////////////////////////////
		typedef vector<AGameComponent*>										ComponentArray;

		////////////////////////////////////////////////////////////
		/// \brief Definition of the game component dictionary type.
		///
		////////////////////////////////////////////////////////////
		typedef unordered_map<RuntimeType, ComponentArray>					ComponentDictionary;

		/// Constructors, destructors
	public:
		////////////////////////////////////////////////////////////
		/// \brief The constructor.
		///
		/// \param l_name The object name.
		/// \param l_tags The tags to set.
		///
		////////////////////////////////////////////////////////////
		explicit GameObject(const string l_name, initializer_list<GameObjectTag::EntryPtr> l_tags = {});

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		~GameObject();

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
		/// \brief Gets the name of the game object.
		///
		/// \return The name of the game object.
		///
		////////////////////////////////////////////////////////////
		string GetName() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the position vector.
		///
		/// \return The position vector.
		///
		////////////////////////////////////////////////////////////
		Vector2f GetPosition() const;

		/// Methods
	public:
		////////////////////////////////////////////////////////////
		/// \brief Avtivates the game object (first step).
		///
		/// \override Always call base class method.
		///
		////////////////////////////////////////////////////////////
		virtual void Activate1() override;

		////////////////////////////////////////////////////////////
		/// \brief Avtivates the game object (second step).
		///
		/// \override Always call base class method.
		///
		////////////////////////////////////////////////////////////
		virtual void Activate2() override;

		////////////////////////////////////////////////////////////
		/// \brief Deactivates the game object (first step).
		///
		/// \override Always call base class method.
		///
		////////////////////////////////////////////////////////////
		virtual void Deactivate1() override;

		////////////////////////////////////////////////////////////
		/// \brief Deactivates the game object (second step).
		///
		/// \override Always call base class method.
		///
		////////////////////////////////////////////////////////////
		virtual void Deactivate2() override;

		////////////////////////////////////////////////////////////
		/// \brief Checks if the game object has the specified tag.
		///
		/// \return True is the game object has the tag in question; otherwise false.
		///
		////////////////////////////////////////////////////////////
		bool HasTag(GameObjectTag::EntryPtr l_tag) const;

		////////////////////////////////////////////////////////////
		/// \brief Checks if the game object has any specified tag.
		///
		/// \return True is the game object has any tag in question; otherwise false.
		///
		////////////////////////////////////////////////////////////
		bool HasAnyTag(initializer_list<GameObjectTag::EntryPtr> l_tags) const;

		////////////////////////////////////////////////////////////
		/// \brief Adds a tag to the game object.
		///
		/// \param l_tag The tag to add.
		///
		////////////////////////////////////////////////////////////
		void AddTag(GameObjectTag::EntryPtr l_tag);

		////////////////////////////////////////////////////////////
		/// \brief Removes a tag from the game object.
		///
		/// \param l_tag The tag to remove.
		///
		////////////////////////////////////////////////////////////
		void RemoveTag(GameObjectTag::EntryPtr l_tag);

		////////////////////////////////////////////////////////////
		/// \brief Moves the object.
		///
		/// \param l_offset The movement offset.
		///
		////////////////////////////////////////////////////////////
		void Move(Vector2f l_offset);

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the iterator where the sequence begins.
		///
		/// \return An iterator of the specified type.
		///
		////////////////////////////////////////////////////////////
		virtual Iterator begin() override;

		////////////////////////////////////////////////////////////
		/// \brief Retrieves the iterator where the sequence ends.
		///
		/// \return An iterator of the specified type.
		///
		////////////////////////////////////////////////////////////
		virtual Iterator end() override;

		////////////////////////////////////////////////////////////
		/// \brief Adds a component to the game object.
		///
		/// \param l_component The component to add.
		///
		////////////////////////////////////////////////////////////
		void AddComponent(AGameComponent* l_component);

		////////////////////////////////////////////////////////////
		/// \brief Gets a component of a specific type.
		///
		/// \param l_considerInheritance Indicates whether inherited types should be checked too or not.
		///
		/// \return The first component of the specified type; nullptr is returned if no matching game component was found.
		///
		////////////////////////////////////////////////////////////
		template<typename T>
		T* GetComponent(bool l_considerInheritance = false)
		{
			auto result = GetComponents<T>(l_considerInheritance);
			if (result.size() > 0)
			{
				return result[0];
			}

			return nullptr;
		}

		////////////////////////////////////////////////////////////
		/// \brief Gets components of a specific type.
		///
		/// \param l_considerInheritance Indicates whether inherited types should be checked too or not.
		///
		/// \return Components of the specified type.
		///
		////////////////////////////////////////////////////////////
		template<typename T>
		vector<T*> GetComponents(bool l_considerInheritance = false)
		{
			auto result = vector<T*>();
		
			if (l_considerInheritance)
			{
				for (auto& component : m_componentPtrs)
				{
					auto target = dynamic_cast<T*>(component);
					if (target != nullptr)
					{
						result.push_back(target);
					}
				}
			}
			else
			{
				auto runtimeType = T::RuntimeType();

				if (m_components.find(runtimeType) != m_components.end())
				{
					for (auto& component : m_components[runtimeType])
					{
						result.push_back(dynamic_cast<T*>(component));
					}
				}
			}
			
			return result;
		}

		/// Members
	private:
		ComponentDictionary													m_components; ///< Contains all components of the game object.
		ComponentArray														m_componentPtrs; ///< Contains all components as raw pointers.
		Vector2f															m_position; ///< The object's world position.
		vector<GameObjectTag::EntryPtr>										m_tags; ///< Contains all tags.
		string																m_name; ///< The game object name.
	};
}
