#include "ShaderModule.hpp"

#ifndef ELYSIUM_CORE_OBJECT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Object.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_GRAPHICSDEVICE
#include "GraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "INativeGraphicsDevice.hpp"
#endif

Elysium::Graphics::Rendering::ShaderModule::ShaderModule(const GraphicsDevice& GraphicsDevice, Elysium::Core::Collections::Template::Array<Elysium::Core::byte>&& ByteCode)
	: _GraphicsDevice(GraphicsDevice), _ByteCode(Elysium::Core::Object::Move(ByteCode)), _NativeShaderModule(_GraphicsDevice._NativeGraphicsDevice.CreateShaderModule(_ByteCode))
{ }
Elysium::Graphics::Rendering::ShaderModule::~ShaderModule()
{
	if (_NativeShaderModule != nullptr)
	{
		delete _NativeShaderModule;
		_NativeShaderModule = nullptr;
	}
}
