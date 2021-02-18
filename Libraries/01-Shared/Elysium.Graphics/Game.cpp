#include "Game.hpp"

Elysium::Graphics::Game::Game(Rendering::INativeLogicalDevice& LogicalDevice, Rendering::INativeSwapchain& Swapchain, 
	Rendering::INativeQueue& PresentationQueue, Rendering::INativeQueue& GraphicsQueue, Rendering::INativeFence& RenderFence, 
	Rendering::INativeSemaphore& PresentSemaphore, Rendering::INativeSemaphore& RenderSemaphore)
	: _Canvas(LogicalDevice.GetPresentationParameters().GetCanvas()), _PresentationParameters(LogicalDevice.GetPresentationParameters()),

	_LogicalDevice(LogicalDevice), _Swapchain(Swapchain), _PresentationQueue(PresentationQueue), _GraphicsQueue(GraphicsQueue),
	_RenderFence(RenderFence), _PresentSemaphore(PresentSemaphore), _RenderSemaphore(RenderSemaphore),

	_GameTime(), _GraphicsDeviceManager(*this)
{
	_Canvas.FocusChanged += Elysium::Core::Delegate<void, void*, const bool>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_FocusChanged>(*this);
	_Canvas.Suspend += Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Suspend>(*this);
	_Canvas.Resume += Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Resume>(*this);
	_Canvas.SizeChanged += Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::SizeChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_SizeChanged>(*this);
	_Canvas.OrientationChanged += Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Canvas.Paint += Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Paint>(*this);
	_Canvas.Exiting += Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Exiting>(*this);
}
Elysium::Graphics::Game::~Game()
{
	_Canvas.FocusChanged -= Elysium::Core::Delegate<void, void*, const bool>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_FocusChanged>(*this);
	_Canvas.Suspend -= Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Suspend>(*this);
	_Canvas.Resume -= Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Resume>(*this);
	_Canvas.SizeChanged -= Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::SizeChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_SizeChanged>(*this);
	_Canvas.OrientationChanged -= Elysium::Core::Delegate<void, void*, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Canvas.Paint -= Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Paint>(*this);
	_Canvas.Exiting -= Elysium::Core::Delegate<void, void*>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Exiting>(*this);
}

const bool Elysium::Graphics::Game::GetIsActive() const
{
	return _IsActive;
}

const bool Elysium::Graphics::Game::GetIsFixedTimeStep() const
{
	return _IsFixedTimeStep;
}

void Elysium::Graphics::Game::SetIsFixedTimeStep(const bool Value)
{
	_IsFixedTimeStep = Value;
}

void Elysium::Graphics::Game::Run()
{
	Initialize();
	_Canvas.Show();

	_LogicalDevice.Wait();
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

void Elysium::Graphics::Game::Tick()
{
	if (_ShouldExit)
	{
		return;
	}

	if (!_Canvas.GetIsMinimized())
	{
		// begin frame
		_RenderFence.Wait(Elysium::Core::UInt64::GetMaxValue());
		_RenderFence.Reset();
		_Swapchain.AquireNextImage(_PresentSemaphore, Elysium::Core::UInt64::GetMaxValue());

		// ...
		_GraphicsQueue.Submit(_PresentSemaphore, _RenderSemaphore, _RenderFence);
		_GraphicsQueue.Wait();

		// end frame
		_Swapchain.PresentFrame(_RenderSemaphore, _PresentationQueue);
	}
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

void Elysium::Graphics::Game::Canvas_FocusChanged(void* Sender, const bool HasReceivedFocus)
{
	_IsActive = HasReceivedFocus;
}

void Elysium::Graphics::Game::Canvas_Suspend(void* Sender)
{
	_IsActive = false;
}

void Elysium::Graphics::Game::Canvas_Resume(void* Sender)
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

void Elysium::Graphics::Game::Canvas_Paint(void* Sender)
{
	Tick();
}

void Elysium::Graphics::Game::Canvas_Exiting(void* Sender)
{
	_ShouldExit = true;
}
