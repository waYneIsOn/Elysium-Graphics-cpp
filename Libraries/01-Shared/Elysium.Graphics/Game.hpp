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

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif




#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDBUFFER
#include "INativeCommandBuffer.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVECOMMANDPOOL
#include "INativeCommandPool.hpp"
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
#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVESWAPCHAIN
#include "INativeSwapchain.hpp"
#endif





namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API Game
	{
	public:
		Game(Rendering::INativeGraphicsDevice& GraphicsDevice,
			Rendering::INativeLogicalDevice& LogicalDevice, Rendering::INativeSwapchain& Swapchain, 
			Rendering::INativeQueue& PresentationQueue, Rendering::INativeQueue& GraphicsQueue, Rendering::INativeFence& RenderFence,
			Rendering::INativeSemaphore& PresentSemaphore, Rendering::INativeSemaphore& RenderSemaphore);
		Game(const Game& Source) = delete;
		Game(Game&& Right) noexcept = delete;
		virtual ~Game();

		Game& operator=(const Game& Source) = delete;
		Game& operator=(Game&& Right) noexcept = delete;

		const bool GetIsActive() const;
		const bool GetIsFixedTimeStep() const;

		void SetIsFixedTimeStep(const bool Value);

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
		Presentation::Control& _Control;
		PresentationParameters& _PresentationParameters;


		Rendering::INativeLogicalDevice& _LogicalDevice;
		Rendering::INativeSwapchain& _Swapchain;
		Rendering::INativeQueue& _PresentationQueue;
		Rendering::INativeQueue& _GraphicsQueue;
		Rendering::INativeFence& _RenderFence;
		Rendering::INativeSemaphore& _PresentSemaphore;
		Rendering::INativeSemaphore& _RenderSemaphore;


		GameTime _GameTime;
		GraphicsDeviceManager _GraphicsDeviceManager;
		/*
		Elysium::Core::uint64_t _DesiredUpdateTimeStep = 500000ULL;	// 2 fps udpate
		Elysium::Core::uint64_t _DesiredDrawTimeStep = 33333ULL;	// 30 fps drawing while active
		Elysium::Core::uint64_t _DesiredDrawTimeStepInactive = 500000ULL;	// 2 fps drawing while inactive
		*/
		bool _IsFixedTimeStep = true;

		bool _IsActive = true;
		bool _IsInitialized = false;
		bool _ShouldExit = false;

		void Control_ActivationChanged(const Presentation::Control& Sender, const bool HasActivated);
		void Control_Suspend(const Presentation::Control& Sender);
		void Control_Resume(const Presentation::Control& Sender);
		void Control_SizeChanged(const Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);
		//void Control_OrientationChanged(const Presentation::Control& Sender, const Platform::DisplayOrientationChangedEventArgs& e);
		void Control_Paint(const Presentation::Control& Sender);
		void Control_Exiting(const Presentation::Control& Sender);
	};
}
#endif
