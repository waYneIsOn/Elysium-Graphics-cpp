#include "MyGame.hpp"

MyGame::MyGame(Elysium::Graphics::Rendering::INativeGraphicsDevice& GraphicsDevice)
	: Elysium::Graphics::Game(GraphicsDevice),
	_CommandPool(GraphicsDevice.GetGraphicsQueue().CreateCommandPool()), _CommandBuffer(_CommandPool->CreateCommandBuffer(true))
{
	_Control.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::CreateDelegate<MyGame, &MyGame::Control_OnSizeChanged>(*this);

	RecordClearCommandBuffer();
}
MyGame::~MyGame()
{
	_Control.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::CreateDelegate<MyGame, &MyGame::Control_OnSizeChanged>(*this);

	if (_CommandBuffer != nullptr)
	{
		delete _CommandBuffer;
	}
	if (_CommandPool != nullptr)
	{
		delete _CommandPool;
	}
}

void MyGame::LoadContent()
{
}

void MyGame::Draw(const Elysium::Graphics::GameTime& GameTime)
{
	_GraphicsDeviceManager.GetGraphicsDevice().GetGraphicsQueue().Submit(*_CommandBuffer, _GraphicsDeviceManager.GetGraphicsDevice().GetPresentationSemaphore(),
		_GraphicsDeviceManager.GetGraphicsDevice().GetRenderSemaphore(), _GraphicsDeviceManager.GetGraphicsDevice().GetRenderFence());
	_GraphicsDeviceManager.GetGraphicsDevice().GetGraphicsQueue().Wait();
}

void MyGame::Update(const Elysium::Graphics::GameTime& GameTime)
{
}

void MyGame::Control_OnSizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	RecordClearCommandBuffer();
}

void MyGame::RecordClearCommandBuffer()
{
	_CommandBuffer->Reset();
	_CommandBuffer->Begin();
	_CommandBuffer->ClearBackBufferImage(Elysium::Graphics::Color::CornflowerBlue);
	_CommandBuffer->ClearDepthImage(0.0f, 0);
	_CommandBuffer->End();
}
