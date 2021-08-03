#include "Viewport.hpp"

Elysium::Graphics::Rendering::Viewport::~Viewport()
{ }

Elysium::Graphics::Rendering::Viewport::Viewport(INativeViewport& NativeViewport)
	: _NativeViewport(NativeViewport)
{ }
