#pragma once

#ifndef ELYSIUM_GRAPHICS_GAME
#include "../../../Libraries/01-Shared/Elysium.Graphics/Game.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTMANAGER
#include "../../../Libraries/01-Shared/Elysium.Graphics/ContentManager.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_COMMANDBUFFER
#include "../../../Libraries/01-Shared/Elysium.Graphics/CommandBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_COMMANDPOOL
#include "../../../Libraries/01-Shared/Elysium.Graphics/CommandPool.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SHADERMODULE
#include "../../../Libraries/01-Shared/Elysium.Graphics/ShaderModule.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXBUFFER
#include "../../../Libraries/01-Shared/Elysium.Graphics/VertexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VERTEXDECLARATION
#include "../../../Libraries/01-Shared/Elysium.Graphics/VertexDeclaration.hpp"
#endif

class MyGame final : public Elysium::Graphics::Game
{
public:
	MyGame(Elysium::Graphics::Rendering::GraphicsDevice& GraphicsDevice);
	MyGame(const MyGame& Source) = delete;
	MyGame(MyGame&& Right) noexcept = delete;
	virtual ~MyGame();

	MyGame& operator=(const MyGame& Source) = delete;
	MyGame& operator=(MyGame&& Right) noexcept = delete;
protected:
	virtual void LoadContent() override;
	virtual void Draw(const Elysium::Graphics::GameTime& GameTime) override;
	virtual void Update(const Elysium::Graphics::GameTime& GameTime) override;
private:
	Elysium::Graphics::Rendering::Queue& _GraphicsQueue;
	const Elysium::Graphics::Rendering::Semaphore& _PresentationSemaphore;
	const Elysium::Graphics::Rendering::Semaphore& _RenderSemaphore;
	const Elysium::Graphics::Rendering::Fence& _RenderFence;

	Elysium::Graphics::Content::ContentManager _ContentManager;
	Elysium::Graphics::Rendering::CommandPool _CommandPool;
	Elysium::Graphics::Rendering::CommandBuffer _CommandBuffer;
	Elysium::Graphics::Rendering::CommandBuffer _SecondaryCommandBuffer;

	Elysium::Graphics::Rendering::RenderPass _MainRenderPass;
	Elysium::Graphics::Rendering::FrameBuffer _FrameBuffer;
	Elysium::Graphics::Rendering::GraphicsPipeline _RenderPipeline;

	Elysium::Graphics::Rendering::ShaderModule _FullScreenTriangleVertexShaderModule;
	Elysium::Graphics::Rendering::ShaderModule _FullScreenTriangleFragmentShaderModule;

	//Elysium::Graphics::Rendering::VertexDeclaration _VertexDeclaration;
	//Elysium::Graphics::Rendering::VertexBuffer _VertexBuffer;
	Elysium::Graphics::Rendering::ShaderModule _VertexShaderModule;
	Elysium::Graphics::Rendering::ShaderModule _FragmentShaderModule;

	Elysium::Graphics::Rendering::ShaderModule LoadShaderModule(const Elysium::Core::String& Path);

	void PrepareGraphicsPipeline();
	void PreparePrimaryCommandBuffer();

	void Control_OnSizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);
};
