/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_PRESENTATION_WINDOW
#define ELYSIUM_GRAPHICS_PRESENTATION_WINDOW

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_MONITOR
#include "Monitor.hpp"
#endif

#if defined(ELYSIUM_CORE_OS_WINDOWS)
#ifndef _WINDOWS_
#include <Windows.h>
#endif

#ifndef _WINGDI_
#include <wingdi.h>
#endif

#ifndef _GDIPLUS_H
#include <gdiplus.h>
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

namespace Elysium::Graphics::Presentation
{
	class ELYSIUM_GRAPHICS_PRESENTATION_API Window : public Control
	{
		friend class Monitor;
	public:
		Window();
		Window(Window&& Right) noexcept = delete;
		Window(const Window& Source) = delete;
		virtual ~Window();

		Window& operator=(Window&& Right) noexcept = delete;
		Window& operator=(const Window& Source) = delete;

		virtual const size_t GetHandle() const override;
		//virtual const bool GetIsActive() const = 0;
		//const Elysium::Core::String& GetName() const;

		//void SetName(const Elysium::Core::String& Value);

		virtual void Show() override;
		//const bool ShowDialog();
		virtual void Close() override;
	private:
		size_t _WindowHandle;

		size_t CreateNativeWindow();
	protected:
		void CenterToMonitor();

		virtual void OnActivationChanged(const Elysium::Graphics::Presentation::Control& Sender, const bool HasActived);
	private:
		inline static const wchar_t* _ClassName = L"Elysium::Graphics::Presentation::Window";
		static size_t _ProgramInstanceHandle;

		static LRESULT CALLBACK WindowsMessageHandlerCallback(HWND WindowHandle, UINT Message, WPARAM wParam, LPARAM lParam);
	};
}
#endif
