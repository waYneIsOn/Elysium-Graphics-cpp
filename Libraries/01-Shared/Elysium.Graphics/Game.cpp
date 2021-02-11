#include "Game.hpp"

Elysium::Graphics::Game::Game(Rendering::INativeLogicalDevice& LogicalDevice, Rendering::INativeSwapchain& Swapchain, Rendering::INativeQueue& PresentationQueue)
	: _Canvas(LogicalDevice.GetPresentationParameters().GetCanvas()), _PresentationParameters(LogicalDevice.GetPresentationParameters()),

	_LogicalDevice(LogicalDevice), _Swapchain(Swapchain), _PresentationQueue(PresentationQueue),


	_GameTime(), _GraphicsDeviceManager(*this)
{
	_Canvas.Activated += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Activated>(*this);
	_Canvas.Deactivated += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Deactivated>(*this);
	_Canvas.SizeChanged += Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::SizeChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_SizeChanged>(*this);
	_Canvas.OrientationChanged += Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Canvas.Paint += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Paint>(*this);
	_Canvas.Exiting += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Exiting>(*this);
}
Elysium::Graphics::Game::~Game()
{
	_Canvas.Activated -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Activated>(*this);
	_Canvas.Deactivated -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Deactivated>(*this);
	_Canvas.SizeChanged -= Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::SizeChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_SizeChanged>(*this);
	_Canvas.OrientationChanged -= Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
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

	if (_IsActive)
	{
		OutputDebugStringA("tick - active\r\n");
	}
	else
	{
		OutputDebugStringA("tick - inactive\r\n");
	}

	// begin frame
	_Swapchain.AquireNextImage(Elysium::Core::UInt64::GetMaxValue());

	// ...

	// end frame
	_Swapchain.PresentFrame(_PresentationQueue);
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

void Elysium::Graphics::Game::Canvas_SizeChanged(void* Sender, const Platform::SizeChangedEventArgs& e)
{
	if (_IsActive)
	{
		_PresentationParameters.SetExtent(e.GetWidth(), e.GetHeight());

		// ToDo: swapchain recreation should be done by reacting to events! this public method shouldn't exist!
		_Swapchain.Recreate();
	}
}

void Elysium::Graphics::Game::Canvas_OrientationChanged(void* Sender, const Platform::DisplayOrientationChangedEventArgs& e)
{
	// ToDo: create a fake once the first triangle is being rendered
}

void Elysium::Graphics::Game::Canvas_Paint(void* Sender, const Core::EventArgs& e)
{
	Tick();
}

void Elysium::Graphics::Game::Canvas_Exiting(void* Sender, const Core::EventArgs& e)
{
	_ShouldExit = true;
}
