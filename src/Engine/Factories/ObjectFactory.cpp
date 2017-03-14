#include "stdafx.h"

#include "ObjectFactory.h"

#include "rapidxml_utils.hpp"
#include "../Components/CameraFocusable.h"
#include "../Components/CameraMoveable.h"
#include "../Components/GridCursorLogic.h"
#include "../Components/GridCursorRenderable.h"
#include "../Components/MapLayerCollision.h"
#include "../Components/MapLayerRenderable.h"
#include "../Components/PathMoveable.h"
#include "../Components/PathRenderable.h"
#include "../Components/PlayableCharacter.h"
#include "../Components/SpriteRenderable.h"
#include "../Components/TurnSystem.h"
#include "../Components/WalkableAreaRenderable.h"
#include "../Components/CharacterControllers/PlayerCharacterControllerInstance.h"
#include "../Components/CharacterControllers/ArtificialCharacterControllerInstance.h"

#include "../Components/CharacterSelectorRenderable.h"
#include "../Components/Role/CharacterRole.h"

#include "../Components/GUI/GUIGameplayScreen.h"
#include "../Components/GUI/GUIStartScreen.h"
#include "../Components/GUI/GUICreditScreen.h"
#include "../Game/Constants.h"
#include "../Game/Game.h"
#include "../General/NLTmxMap.h"
#include "../Managers/ResourceManager.h"
#include "../Serialization/Utility/File.h"
#include "../States/GameplayScreen.h"
#include "../States/StartScreen.h"
#include "../States/CreditScreen.h"

using namespace rapidxml;
using namespace ToD;
using namespace ToD::Components::GUI;
using namespace ToD::Components::Role;
using namespace ToD::Factories;
using namespace ToD::Managers;
using namespace ToD::Serialization::Utility;

const auto EmptyGrid = 0;

ReferenceType::RuntimeType ObjectFactory::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType ObjectFactory::RuntimeType()
{
	return "ToD::Factories::ObjectFactory";
}

void ObjectFactory::LoadPrefabs(ObjectFactoryPrefabCategory::EntryPtr l_prefabCategory, const string l_filePath)
{
	switch(l_prefabCategory->GetValue())
	{
	case ObjectFactoryPrefabCategory::ValueAbilityDeclaration:
		return;

	case ObjectFactoryPrefabCategory::ValueRoleDeclaration:
		return;

	default: 
		throw exception(string("Prefab category " + l_prefabCategory->ToString() + " is not supported.").c_str());
	}
}

GameObject* ObjectFactory::Create(const string l_name) const
{
	if (l_name == StartScreen::Name)
	{
		auto object = new GameObject(StartScreen::Name, { GameObjectTag::GUI });

		auto gui = new GUIStartScreen(object);
		
		gui->LoadWidgets();
		gui->SetIsActive(true);

		object->AddComponent(move(gui));

		return object;
	}

	if (l_name == GameplayScreen::Name)
	{
		auto object = new GameObject(GameplayScreen::Name, { GameObjectTag::GUI });

		auto gui = new GUIGameplayScreen(object);

		gui->LoadWidgets();
		gui->SetIsActive(true);

		object->AddComponent(move(gui));

		return object;
	}

	if (l_name == CreditScreen::Name)
	{
		auto object = new GameObject(CreditScreen::Name, { GameObjectTag::GUI });

		auto gui = new GUICreditScreen(object);

		gui->LoadWidgets();
		gui->SetIsActive(true);

		object->AddComponent(move(gui));

		return object;
	}

	if (l_name == GameplayScreen::CameraName)
	{
		auto object = new GameObject(GameplayScreen::CameraName, { GameObjectTag::Unspecified });

		object->AddComponent(new CameraMoveable(object));
		object->AddComponent(new CameraFocusable(object, Get<Game::Shared>()->GetRenderWindow().getView(), 0.4f));
		object->AddComponent(new GridCursorLogic(object));
		object->AddComponent(new GridCursorRenderable(object, RenderablePriority::HUD, Get<ResourceManager>().GetTexture(Constants::Texture::GameplayScreenGridCursor)));

		return object;
	}

	if (l_name == CreditScreen::CameraName)
	{
		auto object = new GameObject(CreditScreen::CameraName, { GameObjectTag::Unspecified });

		object->AddComponent(new CameraMoveable(object));
		object->AddComponent(new CameraFocusable(object, Get<Game::Shared>()->GetRenderWindow().getView(), 0.4f));
		
		return object;
	}

	throw exception(string("Can not create object " + l_name + ". There is no such object.").c_str());
}

vector<GameObject*> ObjectFactory::CreateFromTmxFile(const string l_filePath) const
{
	vector<GameObject*> gameObjects;

	File::EnsureFileExtension(l_filePath, ".tmx");

	auto xmlFile = new file<>(l_filePath.c_str());
	auto tmxMap = NLLoadTmxMap(xmlFile->data());

	for (auto tileset : tmxMap->tilesets)
	{
		Get<ResourceManager>().RegisterTexture(tileset->name, "../assets/" + tileset->filename, false);
	}

	auto object = new GameObject("Map", { GameObjectTag::Map });

	for (auto layerIdx = 0; layerIdx < static_cast<int>(tmxMap->layers.size()); layerIdx++)
	{
		object->AddComponent(CreateMapLayer(object, tmxMap->layers[layerIdx], layerIdx, tmxMap));
	}

	auto collisionLayer = new MapLayerCollision(object, Vector2i(tmxMap->width, tmxMap->height), Vector2i(tmxMap->tileWidth, tmxMap->tileHeight));

	for (auto group : tmxMap->groups)
	{
		for (auto obj : group->objects)
		{
			if (obj->type == "BlockedTerrain")
			{
				auto  position = Vector2i(obj->x / tmxMap->tileWidth, obj->y / tmxMap->tileHeight);
				collisionLayer->GetCell(position)->SetWalkable(false);
			}
			else
			{
				gameObjects.push_back(Create(obj));
			}
		}
	}

	object->AddComponent(collisionLayer);
	object->AddComponent(new TurnSystem(object));
	object->AddComponent(new WalkableAreaRenderable(object));
	object->AddComponent(new PathRenderable(object));

	gameObjects.push_back(object);

	delete tmxMap;
	delete xmlFile;

	return gameObjects;
}

GameObject* ObjectFactory::Create(NLTmxMapObject* l_object) const
{
	if (l_object->type == "Trigger")
	{
		auto object = new GameObject("trigger", { GameObjectTag::Trigger, GameObjectTag::MapObject });

		return object;
	}

	if (l_object->type == "Character")
	{
		auto position = Vector2f(static_cast<float>(l_object->x), static_cast<float>(l_object->y));
		auto textureName = l_object->properties[2]->value;
		auto textureOffsetX = std::stoi(l_object->properties[3]->value);
		auto textureOffsetY = std::stoi(l_object->properties[4]->value);
		auto textureWidth = l_object->width;
		auto textureHeight = l_object->height;
		//auto roleName = l_object->name == "Player" ? "role-soldier" : "role-skeleton"; // Todo. determine role via certain criteria
		
		auto object = new GameObject(string(l_object->name), { GameObjectTag::FromString(l_object->name), GameObjectTag::MapObject, GameObjectTag::Blocking });

		object->Move(position);

		bool player = false;
		ACharacterControllerInstance* controllerInstance = nullptr;
		CharacterRole* role = nullptr;
		if (l_object->name == "Player")
		{
			controllerInstance = new PlayerCharacterControllerInstance(object);
			role = new CharacterRole(object, "Soldier", 1);
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::HitPoints, 3, 8, true));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::ActionPoints, 1, 8, true));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::Dexterity, 1, 2, false));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::Will, 1, 1, false));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::Constitution, 2, 3, false));
			role->AddHelpAttribute(new DicedRoleAttribute(role, Constants::Attribute::Initiative, Constants::Attribute::Dexterity, 0.5f));
			player = true;
		}
		else if (l_object->name == "Enemy")
		{
			controllerInstance = new ArtificialCharacterControllerInstance(object);
			role = new CharacterRole(object, "Zombie", 2);
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::HitPoints, 4, 12, true));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::ActionPoints, 1, 5, true));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::Dexterity, 1, 1, false));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::Will, 1, 1, false));
			role->AddMainAttribute(new CalculatedRoleAttribute(role, Constants::Attribute::Constitution, 2, 1, false));
			role->AddHelpAttribute(new DicedRoleAttribute(role, Constants::Attribute::Initiative, Constants::Attribute::Dexterity, 0.5f));
		}

		object->AddComponent(controllerInstance);
		object->AddComponent(role);
		object->AddComponent(new PlayableCharacter(object, role));
		object->AddComponent(new PathMoveable(object));
		object->AddComponent(new SpriteRenderable(object, RenderablePriority::Object, Get<ResourceManager>().GetTexture(textureName), IntRect(textureOffsetX, textureOffsetY, textureWidth, textureHeight)));
		//object->AddComponent(Instantiate(ObjectFactoryPrefabCategory::RoleDeclaration, roleName));
		object->AddComponent(new CharacterSelectorRenderable(object, Get<ResourceManager>().GetTexture(Constants::Texture::CharacterSelector), player));

		return object;
	}

	throw exception(("Can not create object " + l_object->name + ". There is no such object.").c_str());
}

AGameComponent* ObjectFactory::CreateMapLayer(GameObject* l_object, const NLTmxMapLayer* l_layer, const int l_layerDepth, NLTmxMap* l_tilemap) const
{
	auto renderPriority = RenderablePriority::FromValue(l_layerDepth);
	auto layerSize = Vector2i(l_layer->width, l_layer->height);
	auto tileSize = Vector2i(l_tilemap->tileWidth, l_tilemap->tileHeight);

	auto component = new MapLayerRenderable(l_object, renderPriority, layerSize, tileSize);

	// go over all elements in the layer
	auto tileCount = l_layer->width * l_layer->height;
	for (auto i = 0; i < tileCount; i++)
	{
		auto tile = CreateMapTile(l_tilemap, l_layer, i);
		if (tile != nullptr)
		{
			component->AddTile(tile);
		}
	}

	return component;
}

Sprite* ObjectFactory::CreateMapTile(NLTmxMap* l_tilemap, const NLTmxMapLayer* l_layer, const int l_idx) const
{
	auto grid = l_layer->data[l_idx];
	if (grid == EmptyGrid)
	{
		return nullptr;
	}

	// get tileset and tileset texture
	auto tileset = l_tilemap->getTilesetForGrid(grid);
	auto tileSize = Vector2i(l_tilemap->tileWidth, l_tilemap->tileHeight);
	auto texture = Get<ResourceManager>().GetTexture(tileset->name);

	// horizontal tile count in tileset texture
	int tileCountX = texture->getSize().x / tileSize.x;

	// calcualte position of tile
	auto positionX = (l_idx % l_layer->width) * static_cast<float>(tileSize.x);
	auto positionY = (l_idx / l_layer->width) * static_cast<float>(tileSize.y);
	auto position = Vector2f(positionX, positionY);

	// calculate 2d idx of tile in tileset texture
	auto offsetOneDimensional = grid - tileset->firstGid;
	auto offsetX = offsetOneDimensional % tileCountX;
	auto offsetY = offsetOneDimensional / tileCountX;

	// calculate source area of tile in tileset texture
	auto sourceRect = IntRect(offsetX * tileSize.x, offsetY * tileSize.y, tileSize.x, tileSize.y);

	auto tile = new Sprite(*texture, sourceRect);

	tile->setPosition(position);

	return tile;
}
