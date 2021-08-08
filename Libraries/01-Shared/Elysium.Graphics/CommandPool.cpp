#include "CommandPool.hpp"

Elysium::Graphics::Rendering::CommandPool::~CommandPool()
{
	if (_NativeCommandPool != nullptr)
	{
		delete _NativeCommandPool;
		_NativeCommandPool = nullptr;
	}
}

Elysium::Graphics::Rendering::CommandBuffer Elysium::Graphics::Rendering::CommandPool::CreateCommandBuffer(const bool IsPrimary)
{
	return CommandBuffer(_NativeCommandPool->CreateCommandBuffer(IsPrimary));
}

void Elysium::Graphics::Rendering::CommandPool::Reset()
{
	_NativeCommandPool->Reset();
}

Elysium::Graphics::Rendering::CommandPool::CommandPool(Native::INativeCommandPool* NativeCommandPool)
	: _NativeCommandPool(NativeCommandPool)
{ }
