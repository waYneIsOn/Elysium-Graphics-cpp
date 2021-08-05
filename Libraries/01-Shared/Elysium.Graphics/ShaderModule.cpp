#include "ShaderModule.hpp"

Elysium::Graphics::Rendering::ShaderModule::ShaderModule(const GraphicsDevice& GraphicsDevice, const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& Data)
	: _GraphicsDevice(GraphicsDevice)
{ }
Elysium::Graphics::Rendering::ShaderModule::~ShaderModule()
{ }
