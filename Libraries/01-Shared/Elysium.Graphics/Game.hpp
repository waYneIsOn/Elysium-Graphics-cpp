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

#ifndef ELYSIUM_GRAPHICS_PLATFORM_CANVAS
#include "Canvas.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_IPHYSICALDEVICE
#include "IPhysicalDevice.hpp"
#endif
#ifndef ELYSIUM_GRAPHICS_RENDERING_ILOGICALDEVICE
#include "ILogicalDevice.hpp"
#endif

namespace Elysium::Graphics
{
	class ELYSIUM_GRAPHICS_API Game
	{
	public:
		Game(Platform::Canvas& Canvas, Rendering::IPhysicalDevice& PhysicalDevice);
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

		void Exit();
		void ResetElapsedTime();
		void Run();
		void RunOneFrame();
		void SuppressDraw();
		void Tick();
	protected:
		virtual const bool BeginDraw();
		virtual const bool BeginRun();
		virtual void Draw(const GameTime& GameTime) = 0;
		virtual void EndDraw();
		virtual void EndRun();
		virtual void Initialize();
		virtual void Update(const GameTime& GameTime) = 0;
	private:
		Platform::Canvas& _Canvas;
		Rendering::IPhysicalDevice& _PhysicalDevice;
		//Rendering::ILogicalDevice* _LogicalDevice;
		GameTime _GameTime;
		GraphicsDeviceManager _GraphicsDeviceManager;

		bool _IsActive = true;
		bool _ShouldExit = false;
		bool _IsFixedTimeStep = true;
		bool _IsMouseVisible = true;

		void Canvas_Activated(void* Sender, const Core::EventArgs& e);
		void Canvas_Deactivated(void* Sender, const Core::EventArgs& e);
		void Canvas_Suspend(void* Sender, const Core::EventArgs& e);
		void Canvas_Resume(void* Sender, const Core::EventArgs& e);
		void Canvas_SizeChanged(void* Sender, const Core::EventArgs& e);
		void Canvas_OrientationChanged(void* Sender, const Core::EventArgs& e);
		void Canvas_Idle(void* Sender, const Core::EventArgs& e);
		void Canvas_Paint(void* Sender, const Core::EventArgs& e);
		void Canvas_Exiting(void* Sender, const Core::EventArgs& e);
	};
}
#endif
