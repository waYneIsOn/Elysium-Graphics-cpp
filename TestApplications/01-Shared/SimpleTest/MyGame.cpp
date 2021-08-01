#include "MyGame.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_EFFECT
#include "../../../Libraries/01-Shared/Elysium.Graphics/Effect.hpp"
#endif

MyGame::MyGame(Elysium::Graphics::Rendering::GraphicsDevice& GraphicsDevice)
	: Elysium::Graphics::Game(GraphicsDevice),
	_ContentManager(GraphicsDevice, u8"Assets"),
	_CommandPool(GraphicsDevice.GetGraphicsQueue().CreateCommandPool()), _CommandBuffer(_CommandPool.CreateCommandBuffer(true))
{
	_Control.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<MyGame, &MyGame::Control_OnSizeChanged>(*this);

	RecordClearCommandBuffer();
}
MyGame::~MyGame()
{
	_Control.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<MyGame, &MyGame::Control_OnSizeChanged>(*this);
}

void MyGame::LoadContent()
{
	Elysium::Graphics::Rendering::Effect VertexShader =
		_ContentManager.Load<Elysium::Graphics::Rendering::Effect>(u8"../../../../bin/Debug/x64/Assets/SomeShader.spv");
	Elysium::Graphics::Rendering::Effect FragementShader =
		_ContentManager.Load<Elysium::Graphics::Rendering::Effect>(u8"../../../../bin/Debug/x64/Assets/SomeShader.spv");
}

void MyGame::Draw(const Elysium::Graphics::GameTime& GameTime)
{
	_GraphicsDevice.GetGraphicsQueue().Submit(_CommandBuffer, _GraphicsDevice.GetPresentationSemaphore(),
		_GraphicsDevice.GetRenderSemaphore(), _GraphicsDevice.GetRenderFence());
	_GraphicsDevice.GetGraphicsQueue().Wait();
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
	_CommandBuffer.Reset();
	_CommandBuffer.Begin();
	_CommandBuffer.ClearBackBufferImage(Elysium::Graphics::Color::CornflowerBlue);
	_CommandBuffer.ClearDepthImage(0.0f, 0);
	_CommandBuffer.End();
}
