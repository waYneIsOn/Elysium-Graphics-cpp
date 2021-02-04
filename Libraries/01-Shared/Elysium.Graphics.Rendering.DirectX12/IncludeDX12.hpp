/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef VULKAN_HPP
#if defined(ELYSIUM_CORE_OS_WINDOWS)
#define COM_NO_WINDOWS_H
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif

#ifndef __d3d12_h__
#include <d3d12.h>
#endif

#ifndef __dxgi1_6_h__
#include <dxgi1_6.h>
#endif


#endif

#endif