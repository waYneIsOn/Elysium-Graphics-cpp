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

#ifndef ELYSIUM_GRAPHICS_GAMETIME
#include "GameTime.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_GRAPHICSDEVICEMANAGER
#include "GraphicsDeviceManager.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif





#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEBUFFER
#include "INativeBuffer.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEDEPTHBUFFER
#include "INativeDepthBuffer.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVELOGICALDEVICE
#include "INativeLogicalDevice.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEIMAGE2D
#include "INativeImage2D.hpp"
#endif






namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API Game
	{
	public:
		Game(Rendering::INativeLogicalDevice& LogicalDevice, Rendering::INativeSwapchain& Swapchain, Rendering::INativeQueue& PresentationQueue);
		Game(const Game& Source) = delete;
		Game(Game&& Right) noexcept = delete;
		virtual ~Game();

		Game& operator=(const Game& Source) = delete;
		Game& operator=(Game&& Right) noexcept = delete;

		const Platform::Canvas& GetCanvas() const;
		const bool GetIsActive() const;
		const bool GetIsFixedTimeStep() const;
		const bool GetIsMouseVisible() const;

		void SetIsFixedTimeStep(const bool Value);
		void SetIsMouseVisible(const bool Value);

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
	private:
		Platform::Canvas& _Canvas;
		Rendering::PresentationParameters& _PresentationParameters;


		Rendering::INativeLogicalDevice& _LogicalDevice;
		Rendering::INativeSwapchain& _Swapchain;
		Rendering::INativeQueue& _PresentationQueue;


		GameTime _GameTime;
		GraphicsDeviceManager _GraphicsDeviceManager;
		/*
		Elysium::Core::uint64_t _DesiredUpdateTimeStep = 500000ULL;	// 2 fps udpate
		Elysium::Core::uint64_t _DesiredDrawTimeStep = 33333ULL;	// 30 fps drawing while active
		Elysium::Core::uint64_t _DesiredDrawTimeStepInactive = 500000ULL;	// 2 fps drawing while inactive
		*/
		bool _IsFixedTimeStep = true;
		bool _IsMouseVisible = true;

		bool _IsActive = true;
		bool _IsInitialized = false;
		bool _ShouldExit = false;

		void Canvas_Activated(void* Sender, const Core::EventArgs& e);
		void Canvas_Deactivated(void* Sender, const Core::EventArgs& e);
		void Canvas_Suspend(void* Sender, const Core::EventArgs& e);
		void Canvas_Resume(void* Sender, const Core::EventArgs& e);
		void Canvas_SizeChanged(void* Sender, const Platform::SizeChangedEventArgs& e);
		void Canvas_OrientationChanged(void* Sender, const Platform::DisplayOrientationChangedEventArgs& e);
		void Canvas_Paint(void* Sender, const Core::EventArgs& e);
		void Canvas_Exiting(void* Sender, const Core::EventArgs& e);
	};
}
#endif
