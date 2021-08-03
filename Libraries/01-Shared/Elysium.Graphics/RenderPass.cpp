#include "RenderPass.hpp"

Elysium::Graphics::Rendering::RenderPass::~RenderPass()
{ }

Elysium::Graphics::Rendering::RenderPass::RenderPass(INativeRenderPass& NativeRenderPass)
	: _NativeRenderPass(NativeRenderPass)
{ }
