#pragma once

#include "ObjectFactoryPrefabCategory.h"
#include "../Game/GameObject.h"
#include "../Managers/ObjectContainer.h"

class NLTmxMapObject;
class NLTmxMapLayer;
class NLTmxMap;

using namespace ToD::Components;
using namespace ToD::Managers;

namespace ToD
{
	namespace Factories
	{
		////////////////////////////////////////////////////////////
		/// \brief Used to create game objects.
		///
		////////////////////////////////////////////////////////////
		class ObjectFactory :
			public ObjectContainer::SharedObject
		{
			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief Default constructor
			///
			////////////////////////////////////////////////////////////
			ObjectFactory() IsDefault__;

			////////////////////////////////////////////////////////////
			/// \brief Default destructor
			///
			////////////////////////////////////////////////////////////
			~ObjectFactory() IsDefault__;

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
			/// \brief Loads prefabs for a specific category from an XML file.
			///
			/// \param l_prefabCategory The prefab category to load.
			/// \param l_filePath Path where the prefab file is found.
			///
			/// \exception std::exception: The file is no valid XML file.
			/// \exception std::exception: The file could not be loaded.
			///
			////////////////////////////////////////////////////////////
			void LoadPrefabs(ObjectFactoryPrefabCategory::EntryPtr l_prefabCategory, const string l_filePath);

			////////////////////////////////////////////////////////////
			/// \brief Creates a new game object.
			/// 
			/// \param l_name The name of the game object to create.
			///
			/// \return The created game object.
			///
			/// \exception std::exception: name is invalid.
			///
			////////////////////////////////////////////////////////////
			GameObject* Create(const string l_name) const;

			////////////////////////////////////////////////////////////
			/// \brief Creates a new game object from a tmx file.
			///
			/// \param l_filePath Path where the tmx file is found.
			///
			/// \return The created game object.
			///
			/// \exception std::exception: The file is no valid tmx file.
			/// \exception std::exception: The file could not be loaded.
			///
			////////////////////////////////////////////////////////////
			vector<GameObject*> CreateFromTmxFile(const string l_filePath) const;

		private:
			////////////////////////////////////////////////////////////
			/// \brief Creates a new game object.
			/// 
			/// \param l_object The tmx map game object.
			///
			/// \return The created game object.
			///
			/// \exception std::exception: name is invalid.
			///
			////////////////////////////////////////////////////////////
			GameObject* Create(NLTmxMapObject* l_object) const;

			////////////////////////////////////////////////////////////
			/// \brief Creates a new map layer.
			/// 
			/// \param l_object The object this component belongs to.
			/// \param l_layer The layer the component belongs to.
			/// \param l_layerDepth The layer depth.
			/// \param l_tilemap The tilemap to use.
			///
			/// \return The created map layer.
			///
			////////////////////////////////////////////////////////////
			AGameComponent* CreateMapLayer(GameObject* l_object, const NLTmxMapLayer* l_layer, const int l_layerDepth, NLTmxMap* l_tilemap) const;

			////////////////////////////////////////////////////////////
			/// \brief Creates a new map tile.
			/// 
			/// \param l_tilemap The tilemap to use.
			/// \param l_layer The layer the tile belongs to.
			/// \param l_idx The tile index.
			///
			/// \return The created map tile.
			///
			////////////////////////////////////////////////////////////
			Sprite* CreateMapTile(NLTmxMap* l_tilemap, const NLTmxMapLayer * l_layer, const int l_idx) const;
		};
	}
}
