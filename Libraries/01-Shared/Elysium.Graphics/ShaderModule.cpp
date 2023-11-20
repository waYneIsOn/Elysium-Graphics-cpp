#include "ShaderModule.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::ShaderModule::ShaderModule(const GraphicsDevice& GraphicsDevice, Elysium::Core::Template::Container::Vector<Elysium::Core::byte>&& ByteCode)
	: _GraphicsDevice(GraphicsDevice), _ByteCode(Elysium::Core::Template::Functional::Move(ByteCode)), _NativeShaderModule(_GraphicsDevice._NativeGraphicsDevice.CreateShaderModule(_ByteCode))
{ }

Elysium::Graphics::Rendering::ShaderModule::~ShaderModule()
{
	if (_NativeShaderModule != nullptr)
	{
		delete _NativeShaderModule;
		_NativeShaderModule = nullptr;
	}
}
