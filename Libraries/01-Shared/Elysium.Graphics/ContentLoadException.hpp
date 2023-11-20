/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTLOADEXCEPTION
#define ELYSIUM_GRAPHICS_CONTENT_CONTENTLOADEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"
#endif

#ifndef ELYSIUM_CORE_STRING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/String.hpp"
#endif

namespace Elysium::Graphics::Content
{
	class ELYSIUM_GRAPHICS_API ContentLoadException final : public Elysium::Core::Exception
	{
	public:
		ContentLoadException();

		ContentLoadException(const char8_t* Message);

		ContentLoadException(Elysium::Core::Utf8String&& Message);

		virtual ~ContentLoadException();
	};
}
#endif
