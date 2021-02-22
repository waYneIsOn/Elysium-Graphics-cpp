#include "MyGame.hpp"

MyGame::MyGame(Elysium::Graphics::Rendering::INativeGraphicsDevice& GraphicsDevice)
	: Elysium::Graphics::Game(GraphicsDevice),
	_CommandPool(GraphicsDevice.GetGraphicsQueue().CreateCommandPool()), _CommandBuffer(_CommandPool->CreateCommandBuffer(true))
{
	RecordClearCommandBuffer();
}
MyGame::~MyGame()
{
	delete _CommandBuffer;
	delete _CommandPool;
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

void MyGame::Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	RecordClearCommandBuffer();
}

void MyGame::RecordClearCommandBuffer()
{
	_CommandBuffer->Reset();
	_CommandBuffer->Begin();
	_CommandBuffer->ClearColorImage(0.0f, 1.0f, 0.0f, 1.0f);
	_CommandBuffer->End();
}
