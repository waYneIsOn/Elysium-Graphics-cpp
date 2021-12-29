/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTREADER
#define ELYSIUM_GRAPHICS_CONTENT_CONTENTREADER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/BinaryReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

namespace Elysium::Graphics::Content
{
	class ContentManager;

	class ELYSIUM_GRAPHICS_API ContentReader final
	{
	public:
		ContentReader(const ContentReader& Source) noexcept = delete;
		ContentReader(ContentReader&& Right) noexcept = delete;
		~ContentReader() noexcept;

		ContentReader& operator=(const ContentReader& Source) noexcept = delete;
		ContentReader& operator=(ContentReader&& Right) noexcept = delete;

		static ContentReader Create(const ContentManager& Manager, Elysium::Core::IO::Stream& Input, const Elysium::Core::Utf8String& AssetName);

		template <class T>
		T ReadAsset();
	private:
		ContentReader(const ContentManager& Manager, Elysium::Core::IO::BinaryReader& InputReader, const Elysium::Core::Utf8String& AssetName) noexcept;

		const Elysium::Graphics::Rendering::GraphicsDevice& _GraphicsDevice;
		const Elysium::Core::Utf8String& _AssetName;
		Elysium::Core::IO::BinaryReader& _InputReader;
	};

	template<class T>
	inline T ContentReader::ReadAsset()
	{
		return T(_GraphicsDevice, _InputReader);
	}
}
#endif
