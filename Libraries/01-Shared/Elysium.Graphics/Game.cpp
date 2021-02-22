#include "Game.hpp"

Elysium::Graphics::Game::Game(Rendering::INativeGraphicsDevice& GraphicsDevice)
	: _Control(GraphicsDevice.GetPresentationParameters().GetCanvas()), _GraphicsDeviceManager(*this, GraphicsDevice), _GameTime()
{
	_Control.ActivationChanged += Elysium::Core::Delegate<void, const Presentation::Control&, const bool>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_ActivationChanged>(*this);
	//_Control.Suspend += Elysium::Core::Delegate<void, const Presentation::Control&::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Suspend>(*this);
	//_Control.Resume += Elysium::Core::Delegate<void, const Presentation::Control&::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Resume>(*this);
	_Control.SizeChanged += Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_SizeChanged>(*this);
	//_Control.OrientationChanged += Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Control.Paint += Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_Paint>(*this);
	_Control.Exiting += Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_Exiting>(*this);
}
Elysium::Graphics::Game::~Game()
{
	_Control.ActivationChanged -= Elysium::Core::Delegate<void, const Presentation::Control&, const bool>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_ActivationChanged>(*this);
	//_Control.Suspend -= Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Suspend>(*this);
	//_Control.Resume -= Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Resume>(*this);
	_Control.SizeChanged -= Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_SizeChanged>(*this);
	//_Control.OrientationChanged -= Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Control.Paint -= Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_Paint>(*this);
	_Control.Exiting -= Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_Exiting>(*this);
}

const bool Elysium::Graphics::Game::GetIsActive() const
{
	return _IsActive;
}

void Elysium::Graphics::Game::Run()
{
	Initialize();
	_Control.Show();

	_GraphicsDeviceManager.Wait();
}

void Elysium::Graphics::Game::Exit()
{
	_ShouldExit = true;
	_Control.Close();
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
	
	// ToDo: fixed timestep etc.

	// begin frame
	BeginDraw();

	// ...
	Draw(_GameTime);

	// end frame
	EndDraw();
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

void Elysium::Graphics::Game::Control_ActivationChanged(const Presentation::Control& Sender, const bool HasActivated)
{
	_IsActive = HasActivated;
}

void Elysium::Graphics::Game::Control_Suspend(const Presentation::Control& Sender)
{
	_IsActive = false;
}

void Elysium::Graphics::Game::Control_Resume(const Presentation::Control& Sender)
{
	_IsActive = true;
}

void Elysium::Graphics::Game::Control_SizeChanged(const Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	// ...
}

void Elysium::Graphics::Game::Control_OrientationChanged(const Presentation::Control& Sender, const DisplayOrientation e)
{
	// ...
}

void Elysium::Graphics::Game::Control_Paint(const Presentation::Control& Sender)
{
	Tick();
}

void Elysium::Graphics::Game::Control_Exiting(const Presentation::Control& Sender)
{
	_ShouldExit = true;
}
