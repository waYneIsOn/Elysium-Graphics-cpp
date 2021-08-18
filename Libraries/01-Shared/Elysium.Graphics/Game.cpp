#include "Game.hpp"

Elysium::Graphics::Game::Game(Rendering::GraphicsDevice& GraphicsDevice)
	: _GraphicsDevice(GraphicsDevice), _GraphicsDeviceManager(*this, _GraphicsDevice), _Control(_GraphicsDevice.GetPresentationParameters().GetCanvas()), 
	_GameTimer(), _GameTime()
{
	_Control.ActivationChanged += Elysium::Core::Delegate<void, const Presentation::Control&, const bool>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnActivationChanged>(*this);
	//_Control.Suspend += Elysium::Core::Delegate<void, const Presentation::Control&::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Suspend>(*this);
	//_Control.Resume += Elysium::Core::Delegate<void, const Presentation::Control&::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Resume>(*this);
	_Control.SizeChanged += Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnSizeChanged>(*this);
	//_Control.OrientationChanged += Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Control.Paint += Elysium::Core::Delegate<void, const Presentation::Control&>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnPaint>(*this);
	_Control.Exiting += Elysium::Core::Delegate<void, const Presentation::Control&>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnExiting>(*this);
}
Elysium::Graphics::Game::~Game()
{
	_Control.ActivationChanged -= Elysium::Core::Delegate<void, const Presentation::Control&, const bool>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnActivationChanged>(*this);
	//_Control.Suspend -= Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Suspend>(*this);
	//_Control.Resume -= Elysium::Core::Delegate<void, const Presentation::Control&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_Resume>(*this);
	_Control.SizeChanged -= Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnSizeChanged>(*this);
	//_Control.OrientationChanged -= Elysium::Core::Delegate<void, const Presentation::Control&, const Elysium::Graphics::Platform::DisplayOrientationChangedEventArgs&>::CreateDelegate<Elysium::Graphics::Game, &Elysium::Graphics::Game::Canvas_OrientationChanged>(*this);
	_Control.Paint -= Elysium::Core::Delegate<void, const Presentation::Control&>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnPaint>(*this);
	_Control.Exiting -= Elysium::Core::Delegate<void, const Presentation::Control&>::Bind<Elysium::Graphics::Game, &Elysium::Graphics::Game::Control_OnExiting>(*this);
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
	
	// update on a fixed timestep (as many times as required)
	_GameTimer.Update();
	_AccumulatedGameTime += _GameTimer.GetElapsedTimeSpan().GetTicks();
	Elysium::Core::int32_t NumberOfUpdates = _AccumulatedGameTime / _DesiredUpdateTimeStep;
	_GameTime._IsUpdatingSlowly = NumberOfUpdates > 1;
	while (NumberOfUpdates > 0)
	{
		if (_ShouldExit)
		{
			break;
		}

		_GameTime._ElapsedGameTime = _DesiredUpdateTimeStep;
		_GameTime._TotalGameTime += _DesiredUpdateTimeStep;
		_GameTime._Delta = (_DesiredUpdateTimeStep / 10000.0);
		_AccumulatedGameTime -= _DesiredUpdateTimeStep;

		if (BeginUpdate())
		{
			Update(_GameTime);
			EndUpdate();
		}

		NumberOfUpdates--;
	}
	
	// render a frame
	if (BeginDraw())
	{
		Draw(_GameTime);
		EndDraw();
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

void Elysium::Graphics::Game::Control_OnActivationChanged(const Presentation::Control& Sender, const bool HasActivated)
{
	_IsActive = HasActivated;
}

void Elysium::Graphics::Game::Control_OnSuspend(const Presentation::Control& Sender)
{
	_IsActive = false;
}

void Elysium::Graphics::Game::Control_OnResume(const Presentation::Control& Sender)
{
	_IsActive = true;
}

void Elysium::Graphics::Game::Control_OnSizeChanged(const Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	// ...
}

void Elysium::Graphics::Game::Control_OnOrientationChanged(const Presentation::Control& Sender, const DisplayOrientation e)
{
	// ...
}

void Elysium::Graphics::Game::Control_OnPaint(const Presentation::Control& Sender)
{
	Tick();
}

void Elysium::Graphics::Game::Control_OnExiting(const Presentation::Control& Sender)
{
	_ShouldExit = true;
}
