#include "Framebuffer.hpp"

Elysium::Graphics::Rendering::Framebuffer::~Framebuffer()
{ }

Elysium::Graphics::Rendering::Framebuffer::Framebuffer(Native::INativeFramebuffer& NativeFramebuffer)
	: _NativeFramebuffer(NativeFramebuffer)
{ }
