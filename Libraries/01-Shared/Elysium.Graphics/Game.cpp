#include "Game.hpp"

Elysium::Graphics::Game::Game(Platform::Canvas& Canvas, Rendering::IPhysicalDevice& PhysicalDevice)
	: _Canvas(Canvas), _PhysicalDevice(PhysicalDevice), _GraphicsDeviceManager(*this)
{
	_Canvas.Activated += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Activated>(*this);
	_Canvas.Deactivated += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Deactivated>(*this);
	// ToDo...
	_Canvas.Exiting += Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Exiting>(*this);
}
Elysium::Graphics::Game::~Game()
{
	_Canvas.Activated -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Activated>(*this);
	_Canvas.Deactivated -= Elysium::Core::Delegate<void, void*, const Elysium::Core::EventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Deactivated>(*this);
	// ToDo...
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

void Elysium::Graphics::Game::Exit()
{
	_ShouldExit = true;
	_Canvas.Close();
}

void Elysium::Graphics::Game::ResetElapsedTime()
{
}

void Elysium::Graphics::Game::Run()
{
	_Canvas.Show();
}

void Elysium::Graphics::Game::RunOneFrame()
{
}

void Elysium::Graphics::Game::SuppressDraw()
{
}

void Elysium::Graphics::Game::Tick()
{
}

const bool Elysium::Graphics::Game::BeginDraw()
{
	return false;
}

const bool Elysium::Graphics::Game::BeginRun()
{
	return false;
}

void Elysium::Graphics::Game::EndDraw()
{
}

void Elysium::Graphics::Game::EndRun()
{
}

void Elysium::Graphics::Game::Initialize()
{
}

void Elysium::Graphics::Game::Update(const GameTime& GameTime)
{
}

void Elysium::Graphics::Game::Canvas_Activated(void* Sender, const Core::EventArgs& e)
{
	if (!GetIsActive())
	{
		_IsActive = true;
		// ...
	}
}

void Elysium::Graphics::Game::Canvas_Deactivated(void* Sender, const Core::EventArgs& e)
{
	if (GetIsActive())
	{
		_IsActive = false;
		// ...
	}
}

void Elysium::Graphics::Game::Canvas_Suspend(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_Resume(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_SizeChanged(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_OrientationChanged(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_Idle(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_Paint(void* Sender, const Core::EventArgs& e)
{
}

void Elysium::Graphics::Game::Canvas_Exiting(void* Sender, const Core::EventArgs& e)
{
	_ShouldExit = true;
	// ...
}
