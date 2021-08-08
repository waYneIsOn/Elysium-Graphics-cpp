#include "RenderPass.hpp"

Elysium::Graphics::Rendering::RenderPass::~RenderPass()
{ }

Elysium::Graphics::Rendering::RenderPass::RenderPass(Native::INativeRenderPass& NativeRenderPass)
	: _NativeRenderPass(NativeRenderPass)
{ }
