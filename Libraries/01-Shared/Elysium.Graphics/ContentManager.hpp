/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTMANAGER
#define ELYSIUM_GRAPHICS_CONTENT_CONTENTMANAGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_DICTIONARY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Dictionary.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_FILESTREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/FileStream.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTREADER
#include "ContentReader.hpp"
#endif

namespace Elysium::Graphics::Content
{
	class ELYSIUM_GRAPHICS_API ContentManager final
	{
	public:
		ContentManager(const Elysium::Graphics::Rendering::GraphicsDevice& GraphicsDevice, const Elysium::Core::String& RootDirectory) noexcept;
		ContentManager(const ContentManager& Source) noexcept = delete;
		ContentManager(ContentManager&& Right) noexcept = delete;
		~ContentManager() noexcept;

		ContentManager& operator=(const ContentManager& Source) noexcept = delete;
		ContentManager& operator=(ContentManager&& Right) noexcept = delete;

		const Elysium::Graphics::Rendering::GraphicsDevice& GetGraphicsDevice() const;

		template <class T>
		const T Load(const Elysium::Core::String& AssetName);
	private:
		const Elysium::Graphics::Rendering::GraphicsDevice& _GraphicsDevice;
		const Elysium::Core::String _RootDirectory;
		//Elysium::Core::Collections::Template::Dictionary<Elysium::Core::String, void*> _LoadedAssets;

		template <class T>
		const T ReadAsset(const Elysium::Core::String& AssetName);
	};

	template<class T>
	inline const T ContentManager::Load(const Elysium::Core::String& AssetName)
	{
		// ToDo: use the dictionary as to not load the same asset multiple times
		return ReadAsset<T>(AssetName);
	}

	template<class T>
	inline const T ContentManager::ReadAsset(const Elysium::Core::String& AssetName)
	{
		// ToDo: combine executing directory, _RootDirectory and AssetName via Elysium::Core::IO::Path::Combine(...)
		Elysium::Core::IO::FileStream Stream = 
			Elysium::Core::IO::FileStream(AssetName, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
		ContentReader Reader = ContentReader::Create(*this, Stream, AssetName);
		return Reader.ReadAsset<T>();
	}
}
#endif
