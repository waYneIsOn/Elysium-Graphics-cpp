#include "Game.hpp"

Elysium::Graphics::Game::Game(Rendering::PresentationParameters& PresentationParameter, Rendering::INativePhysicalDevice& PhysicalDevice,
	Rendering::INativeLogicalDevice& LogicalDevice, Rendering::INativeSwapchain& Swapchain, Rendering::INativeFence& Fence,
	Rendering::INativeSemaphore& ImageAvailableSemaphore, Rendering::INativeSemaphore& WaitSemaphore, Rendering::INativeQueue& PresentationQueue)
	: _PresentationParameter(PresentationParameter), _Canvas(_PresentationParameter.GetCanvas()), _PhysicalDevice(PhysicalDevice), 
	

	_LogicalDevice(LogicalDevice), _Swapchain(Swapchain), _PresentationQueue(PresentationQueue), _Fence(Fence),
	_ImageAvailableSemaphore(ImageAvailableSemaphore), _WaitSemaphore(WaitSemaphore),


	_GameTime(),
	_GraphicsDeviceManager(*this)
{
	_Canvas.Activated += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Activated>(*this);
	_Canvas.Deactivated += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Deactivated>(*this);
	// ToDo...
	_Canvas.Paint += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Paint>(*this);
	_Canvas.Exiting += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Exiting>(*this);
}
Elysium::Graphics::Game::~Game()
{
	_Canvas.Activated -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Activated>(*this);
	_Canvas.Deactivated -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Deactivated>(*this);
	// ToDo...
	_Canvas.Paint -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Paint>(*this);
	_Canvas.Exiting -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Exiting>(*this);
}

const Elysium::Graphics::Platform::Canvas& Elysium::Graphics::Game::GetCanvas() const
{
	return _Canvas;
}

const bool Elysium::Graphics::Game::GetIsActive() const
{
	return _IsActive;
}

const bool Elysium::Graphics::Game::GetIsFixedTimeStep() const
{
	return _IsFixedTimeStep;
}

const bool Elysium::Graphics::Game::GetIsMouseVisible() const
{
	return _IsMouseVisible;
}

void Elysium::Graphics::Game::SetIsFixedTimeStep(const bool Value)
{
	_IsFixedTimeStep = Value;
}

void Elysium::Graphics::Game::SetIsMouseVisible(const bool Value)
{
	_IsMouseVisible = Value;
}

void Elysium::Graphics::Game::Run()
{
	Initialize();
	_Canvas.Show();
}

void Elysium::Graphics::Game::Exit()
{
	_ShouldExit = true;
	_Canvas.Close();
}

void Elysium::Graphics::Game::Initialize()
{
	if (!_IsInitialized)
	{
		LoadContent();
		_IsInitialized = true;
	}
}

#ifndef _WINDOWS_
#include <Windows.h>
#endif

void Elysium::Graphics::Game::Tick()
{
	if (_ShouldExit)
	{
		return;
	}

	OutputDebugStringA("tick\r\n");
	// begin frame
	_Swapchain.AquireNextImage(Elysium::Core::UInt64::GetMaxValue(), _ImageAvailableSemaphore, _Fence);
	//_ImageAvailableSemaphore.Wait(Elysium::Core::UInt64::GetMaxValue());
	//_Fence.Wait(Elysium::Core::UInt64::GetMaxValue());
	//_Fence.Reset();

	// ...

	// end frame
	_Swapchain.PresentFrame(_PresentationQueue, _WaitSemaphore);
	//_PresentationQueue.Wait();
	//_LogicalDevice.Wait();
	
}

const bool Elysium::Graphics::Game::BeginDraw()
{
	return _GraphicsDeviceManager.BeginDraw();
}

void Elysium::Graphics::Game::EndDraw()
{
	_GraphicsDeviceManager.EndDraw();
}

const bool Elysium::Graphics::Game::BeginUpdate()
{
	return true;
}

void Elysium::Graphics::Game::EndUpdate()
{
}

void Elysium::Graphics::Game::Canvas_Activated(void* Sender, const Core::EventArgs& e)
{
	_IsActive = true;
}

void Elysium::Graphics::Game::Canvas_Deactivated(void* Sender, const Core::EventArgs& e)
{
	_IsActive = false;
}

void Elysium::Graphics::Game::Canvas_Suspend(void* Sender, const Core::EventArgs& e)
{
	_IsActive = false;
}

void Elysium::Graphics::Game::Canvas_Resume(void* Sender, const Core::EventArgs& e)
{
	_IsActive = true;
}

void Elysium::Graphics::Game::Canvas_SizeChanged(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_OrientationChanged(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_Paint(void* Sender, const Core::EventArgs& e)
{
	Tick();
}

void Elysium::Graphics::Game::Canvas_Exiting(void* Sender, const Core::EventArgs& e)
{
	_ShouldExit = true;
}
