#include "stdafx.h"

#include "GameConfig.h"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "KeyboardKey.h"

#include "../Serialization/Utility/File.h"
#include "../Serialization/Utility/Str.h"
#include "../Serialization/Utility/Xml.h"

using namespace rapidxml;
using namespace sf;
using namespace ToD;
using namespace ToD::Serialization::Utility;

GameConfig::GameConfig()
: ReferenceType()
, m_bindings()
, m_windowTitle("")
, m_refreshRate(0u)
, m_isFullScreen(false)
, m_resolutionWidth(0u)
, m_resoltionHeight(0u)
, m_textureInfos()
{
}

ReferenceType::RuntimeType GameConfig::GetRuntimeType() const
{
	return "ToD::GameConfig";
}

const GameConfig::BindingArray& GameConfig::GetBindings() const
{
	return m_bindings;
}

string GameConfig::GetWindowTitle() const
{
	return m_windowTitle;
}

unsigned int GameConfig::GetRefreshRate() const
{
	return m_refreshRate;
}

bool GameConfig::GetIsFullScreen() const
{
	return m_isFullScreen;
}

unsigned int GameConfig::GetResolutionWidth() const
{
	return m_resolutionWidth;
}

unsigned int GameConfig::GetResolutionHeight() const
{
	return m_resoltionHeight;
}

const GameConfig::TextureInfoDictionary& GameConfig::GetTextureDictionary() const
{
	return m_textureInfos;
}

void GameConfig::Load(const string l_filePath)
{
	File::EnsureFileExtension(l_filePath, ".config");

	auto xmlFile = new file<>(l_filePath.c_str());
	auto doc = new xml_document<>();

	doc->parse<0>(xmlFile->data());

	auto settingsNode = Xml::GetNode(doc, "Settings");
	auto bindingsNode = Xml::GetNodes(Xml::GetNode(settingsNode, "Bindings"), "KeyBinding");
	auto windowNode = Xml::GetNode(settingsNode, "Window");
	auto resolutionNode = Xml::GetNode(windowNode, "Resolution");

	for (auto bindingNode : bindingsNode)
	{
		m_bindings.push_back({ KeyBindingName::FromString(Xml::GetAttribute(bindingNode, "Name")->value()), KeyboardKey::FromString(Xml::GetAttribute(bindingNode, "Key")->value()) });
	}

	m_windowTitle = Xml::GetAttribute(windowNode, "Title")->value();
	m_refreshRate = Str::To<unsigned int>(Xml::GetAttribute(windowNode, "RefreshRate")->value());
	m_isFullScreen = Str::ToBool(Xml::GetAttribute(windowNode, "IsFullScreen")->value());
	m_resolutionWidth = Str::To<unsigned int>(Xml::GetAttribute(resolutionNode, "Width")->value());
	m_resoltionHeight = Str::To<unsigned int>(Xml::GetAttribute(resolutionNode, "Height")->value());

	auto texturesNode = Xml::GetNode(settingsNode, "Textures");
	auto textureNodes = Xml::GetNodes(texturesNode, "Texture");

	for (auto textureNode : textureNodes)
	{
		m_textureInfos[Xml::GetAttribute(textureNode, "Name")->value()] = Xml::GetAttribute(textureNode, "Location")->value();
	}

	delete doc;
	delete xmlFile;
}

