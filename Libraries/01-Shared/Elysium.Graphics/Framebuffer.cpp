#include "FrameBuffer.hpp"

Elysium::Graphics::Rendering::FrameBuffer::~FrameBuffer()
{ }

Elysium::Graphics::Rendering::FrameBuffer::FrameBuffer(Native::INativeFrameBuffer& NativeFrameBuffer)
	: _NativeFrameBuffer(NativeFrameBuffer)
{ }
