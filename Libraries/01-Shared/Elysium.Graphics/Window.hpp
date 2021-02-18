/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PLATFORM_WINDOW
#define ELYSIUM_GRAPHICS_PLATFORM_WINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _WINGDI_
#include <wingdi.h>
#endif
#elif defined(ELYSIUM_CORE_OS_ANDROID)
#error "unsupported os"
#elif defined(ELYSIUM_CORE_OS_LINUX)
#error "unsupported os"
#elif defined(ELYSIUM_CORE_OS_MAC)
#error "unsupported os"
#else
#error "unsupported os"
#endif

namespace Elysium::Graphics::Platform
{
	class ELYSIUM_GRAPHICS_API Window
	{
	public:
		Window();
		Window(Window&& Right) noexcept = delete;
		Window(const Window& Source) = delete;
		virtual ~Window();

		Window& operator=(Window&& Right) noexcept = delete;
		Window& operator=(const Window& Source) = delete;

		Elysium::Core::Event<void, const void*, const bool> ActivationChanged;

		//const bool GetIsActive() const;
		//const Elysium::Core::String& GetName() const;

		//void SetName(const Elysium::Core::String& Value);

		void Show();
		//const bool ShowDialog();
		void Close();
	private:

	protected:
		virtual void OnActivationChanged(const void* Sender, const bool HasActived);
	};
}
#endif
