/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION
#define ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_EXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Exception.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API APINotAvailableException : public Core::Exception
	{
	public:
		APINotAvailableException();
		APINotAvailableException(const char8_t* Message);
		APINotAvailableException(Elysium::Core::String&& Message);
		virtual ~APINotAvailableException();
	};
}
#endif
