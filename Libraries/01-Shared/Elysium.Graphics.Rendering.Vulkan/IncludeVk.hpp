/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef VULKAN_HPP
#if defined(ELYSIUM_CORE_OS_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ELYSIUM_CORE_OS_ANDROID)

#elif defined(ELYSIUM_CORE_OS_LINUX)

#elif defined(ELYSIUM_CORE_OS_MAC)

#else
#error "unsupported os"
#endif
#include "../../../../Vulkan/1.2.162.1/Include/vulkan/vulkan.hpp"
#endif

#endif