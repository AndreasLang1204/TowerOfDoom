#include "stdafx.h"

#include "ResourceManager.h"

using namespace ToD;
using namespace ToD::Managers;

ResourceManager::ResourceManager()
: m_textures()
, m_sounds()
, m_music()
{
}

ResourceManager::~ResourceManager()
{
	// Clean up
	for (auto pair : m_textures)
	{
		delete m_textures[pair.first];
	}

	m_textures.clear();

	for (auto pair : m_sounds)
	{
		delete m_sounds[pair.first];
	}

	m_sounds.clear();

	for (auto pair : m_soundBuffers)
	{
		delete m_soundBuffers[pair.first];
	}

	m_soundBuffers.clear();

	for (auto pair : m_music)
	{
		delete m_music[pair.first];
	}

	m_music.clear();
}

ReferenceType::RuntimeType ResourceManager::GetRuntimeType() const
{
	return RuntimeType();
}

ReferenceType::RuntimeType ResourceManager::RuntimeType()
{
	return "ToD::Managers::ResourceManager";
}

#pragma region Texture Methods
void ResourceManager::RegisterTexture(const string l_textureName, const string l_filePath, const bool l_isRepeated)
{
	if (m_textures.find(l_textureName) != m_textures.end())
	{
		LOG(INFO) << "Texture " << l_textureName << " from file " << l_filePath << " has already been loaded";
		return;
	}

	auto texture = new Texture();
	if (texture->loadFromFile(l_filePath))
	{
		texture->setRepeated(l_isRepeated);
		m_textures.insert({ l_textureName, texture });
	}
	else
	{
		LOG(INFO) << "Texture file not Found";	
		delete texture;
	}
}

void ResourceManager::RemoveTexture(string l_textureName)
{
	delete m_textures[l_textureName];
	m_textures.erase(l_textureName);
}

Texture* ResourceManager::GetTexture(const string l_textureName)
{
	if (m_textures.find(l_textureName) != m_textures.end())
	{
		return m_textures[l_textureName];
	}
	
	return nullptr;
}
#pragma endregion 

#pragma region Sound/SoundBuffer Methods
void ResourceManager::RegisterSoundBuffer(const string l_soundBufferName, const string l_filePath)
{
	if (m_soundBuffers.find(l_soundBufferName) != m_soundBuffers.end())
	{
		LOG(INFO) << "SoundBuffer " << l_soundBufferName << " from file " << l_filePath << " has already been loaded";
		return;
	}

	auto soundBuffer = new SoundBuffer();
	if (soundBuffer->loadFromFile(l_filePath))
	{
		m_soundBuffers.insert({ l_soundBufferName, soundBuffer });
	}
	else
	{
		LOG(INFO) << "SoundBuffer file not Found";
		delete soundBuffer;
	}
}

void ResourceManager::RemoveSoundBuffer(const string l_soundBufferName)
{
	// only remove SoundBuffer if it's not used in any Sound
	int usedCnt = 0;
	auto itr = m_soundBuffers.find(l_soundBufferName);

	if (itr != m_soundBuffers.end())
	{
		for (auto pair : m_sounds)
		{
			if (pair.second->getBuffer() == itr->second)
			{
				usedCnt++;
			}
		}
	}

	if (usedCnt == 0)
	{
		delete m_soundBuffers[l_soundBufferName];
		m_soundBuffers.erase(l_soundBufferName);
	}
	else
	{
		LOG(INFO) << "Can not delete SoundBuffer " << l_soundBufferName << " because it's used in one or more Sounds";
	}
}

void ResourceManager::CreateSound(const string l_soundName, const string l_soundBufferName)
{
	if (m_sounds.find(l_soundName) != m_sounds.end())
	{
		LOG(INFO) << "Sound " << l_soundName << " has already been registered";
		return;
	}

	auto itr = m_soundBuffers.find(l_soundBufferName);
	if (itr == m_soundBuffers.end())
	{
		LOG(INFO) << "SoundBuffer " << l_soundBufferName << " does not exist";
		return;
	}

	auto sound = new Sound(*itr->second);
	m_sounds.insert({ l_soundName, sound });
}

void ResourceManager::RemoveSound(const string l_soundName)
{
	delete m_sounds[l_soundName];
	m_sounds.erase(l_soundName);
}

void ResourceManager::PlaySound(const string l_soundName)
{
	if (m_sounds.find(l_soundName) != m_sounds.end())
	{
		m_sounds[l_soundName]->play();
	}
}
#pragma endregion

#pragma region Music Mehtods
void ResourceManager::RegisterMusic(const string l_musicName, const string l_filePath)
{
	if (m_music.find(l_musicName) != m_music.end())
	{
		LOG(INFO) << "Music " << l_musicName << " from file " << l_filePath << " has already been loaded";
		return;
	}

	auto music = new Music();
	if (music->openFromFile(l_filePath))
	{
		m_music.insert({ l_musicName, music });
	}
	else
	{
		LOG(INFO) << "Music file not Found";
		delete music;
	}
}

void ResourceManager::RemoveMusic(const string l_musicName)
{
	delete m_music[l_musicName];
	m_music.erase(l_musicName);
}

sf::Music* ResourceManager::GetMusic(const string l_musicName)
{
	if (m_music.find(l_musicName) != m_music.end())
	{
		return m_music[l_musicName];
	}

	return nullptr;
}
#pragma endregion
