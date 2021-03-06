/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_GAME
#define ELYSIUM_GRAPHICS_GAME

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_DISPLAYORIENTATION
#include "DisplayOrientation.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GAMETIME
#include "GameTime.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "GraphicsDeviceManager.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif




#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEDEPTHBUFFER
#include "../Elysium.Graphics/INativeDepthBuffer.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE
#include "../Elysium.Graphics/INativeLogicalDevice.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN
#include "../Elysium.Graphics/INativeSwapchain.hpp"
#endif




namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API Game
	{
	public:
		Game(Rendering::INativeGraphicsDevice& GraphicsDevice);
		Game(const Game& Source) = delete;
		Game(Game&& Right) noexcept = delete;
		virtual ~Game();

		Game& operator=(const Game& Source) = delete;
		Game& operator=(Game&& Right) noexcept = delete;

		const bool GetIsActive() const;

		void Run();
		void Exit();
	protected:
		virtual void Initialize();
		virtual void LoadContent() = 0;
		void Tick();

		virtual const bool BeginDraw();
		virtual void Draw(const GameTime& GameTime) = 0;
		virtual void EndDraw();

		virtual const bool BeginUpdate();
		virtual void Update(const GameTime& GameTime) = 0;
		virtual void EndUpdate();
	protected:
		Presentation::Control& _Control;
		GraphicsDeviceManager _GraphicsDeviceManager;
	private:
		GameTime _GameTime;
		/*
		Elysium::Core::uint64_t _DesiredUpdateTimeStep = 500000ULL;	// 2 fps udpate
		Elysium::Core::uint64_t _DesiredDrawTimeStep = 33333ULL;	// 30 fps drawing while active
		Elysium::Core::uint64_t _DesiredDrawTimeStepInactive = 500000ULL;	// 2 fps drawing while inactive
		*/
		bool _IsActive = true;
		bool _IsInitialized = false;
		bool _ShouldExit = false;

		void Control_OnActivationChanged(const Presentation::Control& Sender, const bool HasActivated);
		void Control_OnSuspend(const Presentation::Control& Sender);
		void Control_OnResume(const Presentation::Control& Sender);
		void Control_OnSizeChanged(const Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);
		void Control_OnOrientationChanged(const Presentation::Control& Sender, const DisplayOrientation e);
		void Control_OnPaint(const Presentation::Control& Sender);
		void Control_OnExiting(const Presentation::Control& Sender);
	};
}
#endif
