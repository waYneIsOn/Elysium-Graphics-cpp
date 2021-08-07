#include "MyGame.hpp"

#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/BinaryReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/Stream.hpp"
#endif

MyGame::MyGame(Elysium::Graphics::Rendering::GraphicsDevice& GraphicsDevice)
	: Elysium::Graphics::Game(GraphicsDevice),
	_GraphicsQueue(_GraphicsDevice.GetGraphicsQueue()), _PresentationSemaphore(_GraphicsDevice.GetPresentationSemaphore()),
	_RenderSemaphore(_GraphicsDevice.GetRenderSemaphore()), _RenderFence(_GraphicsDevice.GetRenderFence()),
	//_ContentManager(GraphicsDevice, u8"Assets"),
	_CommandPool(_GraphicsQueue.CreateCommandPool()),
	_CommandBuffer(_CommandPool.CreateCommandBuffer(true)), _SecondaryCommandBuffer(_CommandPool.CreateCommandBuffer(false)),
	_VertexShaderModule(LoadShaderModule(u8"../../../../bin/Debug/x64/Assets/Vulkan/VertexShader.spv")),
	_FragmentShaderModule(LoadShaderModule(u8"../../../../bin/Debug/x64/Assets/Vulkan/FragmentShader.spv")),
	_RenderPipeline(_GraphicsDevice)
{
	_Control.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<MyGame, &MyGame::Control_OnSizeChanged>(*this);

	_RenderPipeline.AddShaderModule(_VertexShaderModule, Elysium::Graphics::Rendering::ShaderModuleType::VertexShader);
	_RenderPipeline.AddShaderModule(_FragmentShaderModule, Elysium::Graphics::Rendering::ShaderModuleType::FragmentShader);

	RecordCommandBuffer();
}
MyGame::~MyGame()
{
	_Control.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<MyGame, &MyGame::Control_OnSizeChanged>(*this);
}

void MyGame::LoadContent()
{ }

void MyGame::Draw(const Elysium::Graphics::GameTime& GameTime)
{
	_GraphicsQueue.Submit(_CommandBuffer, _PresentationSemaphore, _RenderSemaphore, _RenderFence);
	_GraphicsQueue.Wait();
}

void MyGame::Update(const Elysium::Graphics::GameTime& GameTime)
{
}

void MyGame::Control_OnSizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	RecordCommandBuffer();
}

Elysium::Graphics::Rendering::ShaderModule MyGame::LoadShaderModule(const Elysium::Core::String& Path)
{
	Elysium::Core::IO::FileStream Stream = Elysium::Core::IO::FileStream(Path, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
	Elysium::Core::IO::BinaryReader Reader = Elysium::Core::IO::BinaryReader(Stream, Elysium::Core::Text::Encoding::UTF8(), false);
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Data = Reader.ReadBytes(Stream.GetLength());
	
	return Elysium::Graphics::Rendering::ShaderModule(_GraphicsDevice, Elysium::Core::Object::Move(Data));
}

void MyGame::RecordCommandBuffer()
{
	_RenderPipeline.Build(_GraphicsDevice.GetDefaultRenderPass());
	
	/*
	_SecondaryCommandBuffer.Reset();
	_SecondaryCommandBuffer.Begin();
	_SecondaryCommandBuffer.SetGraphicsPipeline(_RenderPipeline);
	_SecondaryCommandBuffer.End();
	*/
	_CommandBuffer.Reset();
	_CommandBuffer.Begin();
	_CommandBuffer.BeginRenderPass(_GraphicsDevice.GetDefaultRenderPass(), _GraphicsDevice.GetFramebuffer());
	//_CommandBuffer.ClearBackBufferImage(Elysium::Graphics::Color::CornflowerBlue);
	//_CommandBuffer.ClearDepthImage(0.0f, 0);
	//_CommandBuffer.RecordSecondaryBuffer(_SecondaryCommandBuffer);
	_CommandBuffer.SetGraphicsPipeline(_RenderPipeline);
	_CommandBuffer.Draw(3, 1, 0, 0);
	_CommandBuffer.EndRenderPass();
	_CommandBuffer.End();
}
