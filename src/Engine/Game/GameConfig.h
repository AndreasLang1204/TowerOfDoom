#pragma once

#include "ReferenceType.h"
#include "KeyBinding.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace sf;
using namespace std;

namespace ToD
{
	////////////////////////////////////////////////////////////
	/// \brief Used to load game settings from a configuration file.
	///
	////////////////////////////////////////////////////////////
	class GameConfig :
		public ReferenceType
	{
		/// Typedefs
	public:
		////////////////////////////////////////////////////////////
		/// \brief Definition of the binding array type.
		///
		////////////////////////////////////////////////////////////
		typedef vector<pair<KeyBindingName::EntryPtr, Keyboard::Key>>		BindingArray;

		////////////////////////////////////////////////////////////
		/// \brief Definition of the texture info dictionary type.
		///
		////////////////////////////////////////////////////////////
		typedef unordered_map<string, string>								TextureInfoDictionary;

		/// Constructors, desctructors
	public:
		////////////////////////////////////////////////////////////
		/// \brief The constructor (default constructor).
		///
		////////////////////////////////////////////////////////////
		GameConfig();

		////////////////////////////////////////////////////////////
		/// \brief The destructor.
		///
		////////////////////////////////////////////////////////////
		~GameConfig() IsDefault__;

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
		/// \brief Gets the declared bindings.
		///
		/// \return The declared bindings.
		///
		////////////////////////////////////////////////////////////
		const BindingArray& GetBindings() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the window title.
		///
		/// \return The window title.
		///
		////////////////////////////////////////////////////////////
		string GetWindowTitle() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the window refresh rate.
		///
		/// \return The window refresh rate.
		///
		////////////////////////////////////////////////////////////
		unsigned int GetRefreshRate() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets a value which determines whether the window is full screen or not.
		///
		/// \return A value which determines whether the window is full screen or not.
		///
		////////////////////////////////////////////////////////////
		bool GetIsFullScreen() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the window resolution width.
		///
		/// \return The window resolution width.
		///
		////////////////////////////////////////////////////////////
		unsigned int GetResolutionWidth() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets the window resolution height.
		///
		/// \return The window resolution height.
		///
		////////////////////////////////////////////////////////////
		unsigned int GetResolutionHeight() const;

		////////////////////////////////////////////////////////////
		/// \brief Gets all declared texture infos.
		///
		/// \return All declared texture infos.
		///
		////////////////////////////////////////////////////////////
		const TextureInfoDictionary& GetTextureDictionary() const;

		/// Methods
	public:
		////////////////////////////////////////////////////////////
		/// \brief Loads a config file.
		///
		/// \param l_filePath Path where the config file is found.
		///
		/// \exception std::exception: The file is no valid config file.
		/// \exception std::exception: The file could not be loaded.
		/// \exception std::exception: The XML content is incomplete.
		///
		////////////////////////////////////////////////////////////
		void Load(const string l_filePath);

		/// Members
	private:
		BindingArray														m_bindings; ///< Contains all declared bindings.
		string																m_windowTitle; ///< The window title.
		unsigned int														m_refreshRate; ///< The refresh rate in frames per second.
		bool																m_isFullScreen; ///< Determines whether or not the window is fullscreen or not.
		unsigned int														m_resolutionWidth; ///< The horizontal resolution in pixel.
		unsigned int														m_resoltionHeight; ///< The vertical resolution in pixel.
		TextureInfoDictionary												m_textureInfos; /// Contains all declared texture infos.
	};
}
