#include "Framebuffer.hpp"

Elysium::Graphics::Rendering::Framebuffer::~Framebuffer()
{ }

Elysium::Graphics::Rendering::Framebuffer::Framebuffer(INativeFramebuffer& NativeFramebuffer)
	: _NativeFramebuffer(NativeFramebuffer)
{ }
