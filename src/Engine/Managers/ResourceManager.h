#pragma once

#include "ObjectContainer.h"

using namespace sf;
using namespace std;

namespace ToD
{
	namespace Managers
	{
		////////////////////////////////////////////////////////////
		/// \brief Contains all used textures and caches them.
		///
		////////////////////////////////////////////////////////////
		class ResourceManager :
			public ObjectContainer::SharedObject
		{
			/// Typedefs
		private:
			////////////////////////////////////////////////////////////
			/// \brief Definition of the texture dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<string, sf::Texture*>						TextureDictionary;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the soundbuffer dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<string, sf::SoundBuffer*>					SoundBufferDictionary;
			
			////////////////////////////////////////////////////////////
			/// \brief Definition of the SFX dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<string, sf::Sound*>						SoundDictionary;

			////////////////////////////////////////////////////////////
			/// \brief Definition of the music dictionary type.
			///
			////////////////////////////////////////////////////////////
			typedef unordered_map<string, sf::Music*>						MusicDictionary;

			/// Constructors, destructors
		public:
			////////////////////////////////////////////////////////////
			/// \brief The constructor (default constructor).
			///
			////////////////////////////////////////////////////////////
			ResourceManager();

			////////////////////////////////////////////////////////////
			/// \brief The destructor.
			///
			////////////////////////////////////////////////////////////
			~ResourceManager();

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
#pragma region Texture Methods
			////////////////////////////////////////////////////////////
			/// \brief Registers a texture.
			///
			/// \param l_textureName Name of the texture to register.
			/// \param l_filePath Path where the texture file is located.
			/// \param l_isRepeated Determines whether the texture should be repeated (true: repeat; false: no repeat).
			///
			////////////////////////////////////////////////////////////
			void RegisterTexture(const string l_textureName, const string l_filePath, const bool l_isRepeated);

			////////////////////////////////////////////////////////////
			/// \brief Removes a texture by its name.
			///
			/// \param l_textureName Name of the texture to remove.
			///
			////////////////////////////////////////////////////////////
			void RemoveTexture(const string l_textureName);

			////////////////////////////////////////////////////////////
			/// \brief Retrieves a texture by its name.
			///
			/// \param l_textureName Name of the texture to retrieve.
			///
			/// \return Pointer to a texture or nullptr if the texture was not found.
			///
			////////////////////////////////////////////////////////////
			sf::Texture* GetTexture(const string l_textureName);
#pragma endregion

#pragma region Sound/SoundBuffer Mehtods
			////////////////////////////////////////////////////////////
			/// \brief Registers a soundbuffer.
			///
			/// \param l_soundName Name of the soundbuffer to register.
			/// \param l_filePath Path where the sound file is located.
			///
			////////////////////////////////////////////////////////////
			void RegisterSoundBuffer(const string l_soundBufferName, const string l_filePath);

			////////////////////////////////////////////////////////////
			/// \brief Removes a soundbuffer by its name.
			///
			/// \param l_soundName Name of the soundbuffer to remove.
			///
			////////////////////////////////////////////////////////////
			void RemoveSoundBuffer(const string l_soundBufferName);

			////////////////////////////////////////////////////////////
			/// \brief Creates and Registers a sound out of the specific soundbuffer.
			///
			/// \param l_soundName Name of the soundbuffer to register.
			/// \param l_soundBufferName Name of the soundbuffer.
			///
			////////////////////////////////////////////////////////////
			void CreateSound(const string l_soundName, const string l_soundBufferName);

			////////////////////////////////////////////////////////////
			/// \brief Removes a sound by its name.
			///
			/// \param l_soundName Name of the sound to remove.
			///
			////////////////////////////////////////////////////////////
			void RemoveSound(const string l_soundName);

			////////////////////////////////////////////////////////////
			/// \brief plays a sound instance of the specified soundbuffer
			///
			/// \param l_soundName Name of the soundbuffer to play.
			///
			////////////////////////////////////////////////////////////
			void PlaySound(const string l_soundName);
#pragma endregion

#pragma region Music Methods
			////////////////////////////////////////////////////////////
			/// \brief Registers music.
			///
			/// \param l_musicName Name of the music to register.
			/// \param l_filePath Path where the music file is located.
			///
			////////////////////////////////////////////////////////////
			void RegisterMusic(const string l_musicName, const string l_filePath);

			////////////////////////////////////////////////////////////
			/// \brief Remove music by its name.
			///
			/// \param l_musicName Name of the music to remove.
			///
			////////////////////////////////////////////////////////////
			void RemoveMusic(const string l_musicName);

			////////////////////////////////////////////////////////////
			/// \brief Retrieve music by its name.
			///
			/// \param l_musicName Name of the music to retrieve.
			///
			/// \return Pointer to a music or nullptr if the music was not found.
			///
			////////////////////////////////////////////////////////////
			sf::Music* GetMusic(const string l_musicName);
#pragma endregion

		private:
			TextureDictionary												m_textures;		///< Contains cached textures.
			SoundBufferDictionary											m_soundBuffers;	///< Contains cached soundBuffers
			SoundDictionary													m_sounds;		///< Contains cached sounds.
			MusicDictionary													m_music;		///< Contains cached music
		};
	}
}