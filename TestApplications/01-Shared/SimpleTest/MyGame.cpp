#include "MyGame.hpp"

#ifndef ELYSIUM_CORE_IO_BINARYREADER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/BinaryReader.hpp"
#endif

#ifndef ELYSIUM_CORE_IO_STREAM
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.IO/Stream.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

MyGame::MyGame(Elysium::Graphics::Rendering::GraphicsDevice& GraphicsDevice)
	: Elysium::Graphics::Game(GraphicsDevice),
	_GraphicsQueue(_GraphicsDevice.GetGraphicsQueue()), _PresentationSemaphore(_GraphicsDevice.GetPresentationSemaphore()),
	_RenderSemaphore(_GraphicsDevice.GetRenderSemaphore()), _RenderFence(_GraphicsDevice.GetRenderFence()),
	_ContentManager(_GraphicsDevice, u8"Assets"),
	_CommandPool(_GraphicsQueue.CreateCommandPool()),
	_CommandBuffer(_CommandPool.CreateCommandBuffer(true)), _SecondaryCommandBuffer(_CommandPool.CreateCommandBuffer(false)),
	_MainRenderPass(_GraphicsDevice, Elysium::Graphics::Rendering::SurfaceFormat::R8G8B8A8_sRGB), _FrameBuffer(_GraphicsDevice, _MainRenderPass), 
	_RenderPipeline(_GraphicsDevice),
	_FullScreenTriangleVertexShaderModule(LoadShaderModule(u8"../../../../bin/Debug/x64/Assets/Vulkan/FullScreenTriangle.Vertex.spv")),
	_FullScreenTriangleFragmentShaderModule(LoadShaderModule(u8"../../../../bin/Debug/x64/Assets/Vulkan/FullScreenTriangle.Fragment.spv")),
	_Vertices(CreateVertices()), _VertexBuffer(CreateVertexBuffer()),
	_Indices(CreateIndices()), _IndexBuffer(CreateIndexBuffer()),

	_VertexShaderModule(LoadShaderModule(u8"../../../../bin/Debug/x64/Assets/Vulkan/VertexShader.Buffer.Vert.spv")),
	_FragmentShaderModule(LoadShaderModule(u8"../../../../bin/Debug/x64/Assets/Vulkan/FragmentShader.spv"))
{
	_Control.SizeChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<MyGame, &MyGame::Control_OnSizeChanged>(*this);
}
MyGame::~MyGame()
{
	_Control.SizeChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const Elysium::Core::int32_t, const Elysium::Core::int32_t>::Bind<MyGame, &MyGame::Control_OnSizeChanged>(*this);
}

void MyGame::LoadContent()
{
	_RenderPipeline.AddShaderModule(_VertexShaderModule, Elysium::Graphics::Rendering::ShaderModuleType::VertexShader);
	_RenderPipeline.AddShaderModule(_FragmentShaderModule, Elysium::Graphics::Rendering::ShaderModuleType::FragmentShader);
	PrepareGraphicsPipeline();
	PreparePrimaryCommandBuffer();
}

void MyGame::Draw(const Elysium::Graphics::GameTime& GameTime)
{
	_GraphicsQueue.Submit(_CommandBuffer, _PresentationSemaphore, _RenderSemaphore, _RenderFence);
	_GraphicsQueue.Wait();
}

void MyGame::Update(const Elysium::Graphics::GameTime& GameTime)
{
	const Elysium::Core::TimeSpan& ElapsedGameTime = GameTime.GetElapsedGameTime();
	const Elysium::Core::int32_t TotalMilliseconds = ElapsedGameTime.GetTotalMilliseconds();

	int a = 45;
}

Elysium::Graphics::Rendering::ShaderModule MyGame::LoadShaderModule(const Elysium::Core::String& Path)
{
	Elysium::Core::IO::FileStream Stream = Elysium::Core::IO::FileStream(Path, Elysium::Core::IO::FileMode::Open, Elysium::Core::IO::FileAccess::Read);
	Elysium::Core::IO::BinaryReader Reader = Elysium::Core::IO::BinaryReader(Stream, Elysium::Core::Text::Encoding::UTF8(), false);
	Elysium::Core::Collections::Template::Array<Elysium::Core::byte> Data = Reader.ReadBytes(Stream.GetLength());
	
	return Elysium::Graphics::Rendering::ShaderModule(_GraphicsDevice, Elysium::Core::Template::Move(Data));
}

Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::VertexPositionColor> MyGame::CreateVertices()
{
	return Elysium::Core::Collections::Template::Array<Elysium::Graphics::Rendering::VertexPositionColor>
	{
		Elysium::Graphics::Rendering::VertexPositionColor(Elysium::Core::Math::Numerics::Vector3<float>(-0.5f, -0.5f, 0.0f), Elysium::Graphics::Color::White),
		Elysium::Graphics::Rendering::VertexPositionColor(Elysium::Core::Math::Numerics::Vector3<float>(0.5f, -0.5f, 0.0f), Elysium::Graphics::Color::Gray),
		Elysium::Graphics::Rendering::VertexPositionColor(Elysium::Core::Math::Numerics::Vector3<float>(0.5f, 0.5f, 0.0f), Elysium::Graphics::Color::Silver),
		Elysium::Graphics::Rendering::VertexPositionColor(Elysium::Core::Math::Numerics::Vector3<float>(-0.5f, 0.5f, 0.0f), Elysium::Graphics::Color::Black),
	};
}

Elysium::Graphics::Rendering::VertexBuffer MyGame::CreateVertexBuffer()
{
	return Elysium::Graphics::Rendering::VertexBuffer(_GraphicsDevice, _Vertices[0].GetVertexDeclaration(), 
		_Vertices.GetLength(), Elysium::Graphics::Rendering::BufferUsage::WriteOnly);
}

Elysium::Core::Collections::Template::Array<Elysium::Core::uint16_t> MyGame::CreateIndices()
{
	return Elysium::Core::Collections::Template::Array<Elysium::Core::uint16_t>
	{
		0, 1, 2, 2, 3, 0
	};
}

Elysium::Graphics::Rendering::IndexBuffer MyGame::CreateIndexBuffer()
{
	return Elysium::Graphics::Rendering::IndexBuffer(_GraphicsDevice, Elysium::Graphics::Rendering::IndexElementSize::SixteenBits, _Indices.GetLength(),
		Elysium::Graphics::Rendering::BufferUsage::WriteOnly);
}

void MyGame::PrepareGraphicsPipeline()
{
	/*
	Elysium::Graphics::Rendering::RasterizerState& RasterizerState = _RenderPipeline.GetRasterizerState();
	RasterizerState.SetFillMode(Elysium::Graphics::Rendering::FillMode::Line);
	RasterizerState.SetLineWidth(20.0f);
	*/
	const Elysium::Core::uint32_t FrameBufferWidth = _FrameBuffer.GetWidth();
	const Elysium::Core::uint32_t FrameBufferHeight = _FrameBuffer.GetHeight();

	_RenderPipeline.ClearViewports();
	_RenderPipeline.AddViewport(0, 0, FrameBufferWidth, FrameBufferHeight, 0.0f, 1.0f);

	_RenderPipeline.ClearScissorRectangles();
	_RenderPipeline.AddScissorRectangle(0, 0, FrameBufferWidth, FrameBufferHeight);
	
	_VertexBuffer.SetData(&_Vertices[0], _Vertices.GetLength());
	_RenderPipeline.SetVertexBuffer(_VertexBuffer);

	_IndexBuffer.SetData(&_Indices[0], _Indices.GetLength());
	
	_RenderPipeline.Build(_MainRenderPass);
}

void MyGame::PreparePrimaryCommandBuffer()
{
	/*
	_SecondaryCommandBuffer.Reset();
	_SecondaryCommandBuffer.BeginRecording();
	_SecondaryCommandBuffer.RecordSetGraphicsPipeline(_RenderPipeline);
	_SecondaryCommandBuffer.EndRecording();
	*/
	_CommandBuffer.Reset();
	_CommandBuffer.BeginRecording();
	//_CommandBuffer.RecordClearBackBufferColorImage(Elysium::Graphics::Color::CornflowerBlue);
	//_CommandBuffer.RecordClearBackBufferDepthImage(0.0f, 0);
	_CommandBuffer.RecordBeginRenderPass(_MainRenderPass, _FrameBuffer, Elysium::Graphics::Color::CornflowerBlue, 0.0f, 0);
	//_CommandBuffer.RecordSecondaryBuffer(_SecondaryCommandBuffer);
	_CommandBuffer.RecordSetGraphicsPipeline(_RenderPipeline);
	_CommandBuffer.RecordSetVertexBuffer(_VertexBuffer);
	//_CommandBuffer.RecordDrawPrimitives(_Vertices.GetLength(), 1, 0, 0);
	//_CommandBuffer.RecordDrawPrimitives(3, 1, 0, 0);
	_CommandBuffer.RecordSetIndexBuffer(_IndexBuffer);
	_CommandBuffer.RecordDrawIndexedPrimitives(Elysium::Graphics::Rendering::PrimitiveType::TriangleList, 0, 0, _Vertices.GetLength(), 0, _Indices.GetLength());
	_CommandBuffer.RecordEndRenderPass();

	_CommandBuffer.RecordBlit(_FrameBuffer, Elysium::Graphics::Rendering::BlitFilter::Nearest);

	_CommandBuffer.EndRecording();
}

void MyGame::Control_OnSizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height)
{
	PrepareGraphicsPipeline();
	PreparePrimaryCommandBuffer();
}
