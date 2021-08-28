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

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

namespace Elysium::Graphics
{
	class Game;

	class ELYSIUM_GRAPHICS_API GraphicsDeviceManager final
	{
		friend class Game;
	public:
		GraphicsDeviceManager(const Game& Game, Rendering::GraphicsDevice& GraphicsDevice);
		GraphicsDeviceManager(const GraphicsDeviceManager& Source) = delete;
		GraphicsDeviceManager(GraphicsDeviceManager&& Right) noexcept = delete;
		~GraphicsDeviceManager();

		GraphicsDeviceManager& operator=(const GraphicsDeviceManager& Source) = delete;
		GraphicsDeviceManager& operator=(GraphicsDeviceManager&& Right) noexcept = delete;

		/// <summary>
		/// Specifies the default minimum back-buffer width.
		/// </summary>
		static const Core::uint32_t DefaultBackBufferWidth = 800;

		/// <summary>
		/// Specifies the default minimum back-buffer height.
		/// </summary>
		static const Core::uint32_t DefaultBackBufferHeight = 480;

		/// <summary>
		/// Specifies the default minimum back-buffer count.
		/// </summary>
		static const Core::uint32_t DefaultBackBufferCount = 3;

		/// <summary>
		/// Gets the GraphicsDevice associated with the GraphicsDeviceManager.
		/// </summary>
		/// <returns></returns>
		Rendering::GraphicsDevice& GetGraphicsDevice();

		/// <summary>
		/// Applies any changes to device-related properties, changing the graphics device as necessary.
		/// </summary>
		void ApplyChanges();
	private:
		const Game& _Game;
		Rendering::GraphicsDevice& _GraphicsDevice;

		void Wait() const;
		const bool BeginDraw();
		void EndDraw();
	};
}
#endif
