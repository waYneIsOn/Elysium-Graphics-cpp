/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#define ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_EVENT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Event.hpp"
#endif

#ifndef ELYSIUM_CORE_EVENTARGS
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/EventArgs.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

namespace Elysium::Graphics
{
	namespace Rendering
	{
		class INativeGraphicsDevice;
	}
	class Game;

	class ELYSIUM_GRAPHICS_API GraphicsDeviceManager final
	{
		friend class Game;
	public:
		GraphicsDeviceManager(const GraphicsDeviceManager& Source) = delete;
		GraphicsDeviceManager(GraphicsDeviceManager&& Right) noexcept = delete;
		~GraphicsDeviceManager();

		GraphicsDeviceManager& operator=(const GraphicsDeviceManager& Source) = delete;
		GraphicsDeviceManager& operator=(GraphicsDeviceManager&& Right) noexcept = delete;

		static const Core::uint32_t DefaultBackBufferWidth = 800;
		static const Core::uint32_t DefaultBackBufferHeight = 480;
		static const Core::uint32_t DefaultBackBufferCount = 3;

		Rendering::INativeGraphicsDevice& GetGraphicsDevice();
	private:
		GraphicsDeviceManager(Game& Game, Rendering::INativeGraphicsDevice& GraphicsDevice);

		Game& _Game;
		Rendering::INativeGraphicsDevice& _GraphicsDevice;

		void Wait() const;
		const bool BeginDraw();
		void EndDraw();
	};
}
#endif
