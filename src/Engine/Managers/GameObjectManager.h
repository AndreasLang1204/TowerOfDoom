#pragma once

#include "AManager.h"
#include "../Game/GameObject.h"

using namespace sf;
using namespace std;

namespace ToD
{
	namespace Managers
	{
		////////////////////////////////////////////////////////////
		/// \brief Holds and shares all created game objects.
		///
		////////////////////////////////////////////////////////////
		class GameObjectManager :
			public AManager<GameObjectManager>
		{
			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Definition of the game object dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<string, GameObject*>						GameObjectDictionary;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			GameObjectManager();

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~GameObjectManager();

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
			/// \brief Gets the static runtime type.
			///
			/// \return The static runtime type.
			///
			////////////////////////////////////////////////////////////
			static RuntimeType RuntimeType();

			/// Methods
		public:
			////////////////////////////////////////////////////////////
			/// \brief Updates the currently active game state.
			///
			/// \param l_gameTime Provides a snapshot of timing values.
			///
			////////////////////////////////////////////////////////////
			virtual void Update(const Time l_gameTime) override;

			////////////////////////////////////////////////////////////
			/// \brief Registers a game object.
			///
			/// \param l_gameObject The game object to register.
			///
			////////////////////////////////////////////////////////////
			void RegisterGameObject(GameObject* l_gameObject);

			////////////////////////////////////////////////////////////
			/// \brief Removes a game object.
			///
			/// \param l_gameObject The game object to remove.
			///
			////////////////////////////////////////////////////////////
			void RemoveGameObject(GameObject* l_gameObject);

			////////////////////////////////////////////////////////////
			/// \brief Retrieves the first game object that has a specific tag.
			///
			/// \param l_tag A game object tag.
			///
			/// \return The first game object that has a specific tag.
			///
			////////////////////////////////////////////////////////////
			GameObject& GetGameObject(GameObjectTag::EntryPtr l_tag);

			////////////////////////////////////////////////////////////
			/// \brief Retrieves the game objects that have specific tags.
			///
			/// \param l_tags Game object tags.
			///
			/// \return All game objects with the specified tags.
			///
			////////////////////////////////////////////////////////////
			GameObject::Array GetGameObjects(vector<GameObjectTag::EntryPtr> l_tags);

		private:
			////////////////////////////////////////////////////////////
			/// \brief Removes a game object.
			///
			/// \param l_gameObject The game object to remove.
			/// \param l_isErased Indicates whether objects is erased from the dictionaries or not.
			///
			////////////////////////////////////////////////////////////
			void RemoveGameObject(GameObject* l_gameObject, bool l_isErased);

			/// Members
		private:
			GameObjectDictionary											m_playerObjects; ///< Contains the gameObjects controlled by the player. (lifetime = game || death)
			GameObjectDictionary											m_aiObjects;  ///< Contains the gameObjects controlled by the AI. (liftetime = screen || death)
			GameObjectDictionary											m_otherObjects; ///< Contains the gameObjects which are neither controlled by the player or the AI (lifetime = screen)
		};
	}
}
