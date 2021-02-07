#include "DeviceQueueCreateInfoDX12.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::DeviceQueueCreateInfoDX12()
	: _NodeMask(0), _Priority(CommandQueuePriorityDX12::Normal), _Flags(CommandQueueFlagsDX12::None), _Type(CommandQueueTypeDX12::Direct)
{ }
Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::DeviceQueueCreateInfoDX12(const DeviceQueueCreateInfoDX12 & Source)
	: _NodeMask(Source._NodeMask), _Priority(Source._Priority), _Flags(Source._Flags), _Type(Source._Type)
{ }
Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::DeviceQueueCreateInfoDX12(DeviceQueueCreateInfoDX12 && Right) noexcept
	: _NodeMask(0), _Priority(CommandQueuePriorityDX12::Normal), _Flags(CommandQueueFlagsDX12::None), _Type(CommandQueueTypeDX12::Direct)
{
	*this = std::move(Right);
}
Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::~DeviceQueueCreateInfoDX12()
{ }

Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12& Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::operator=(const DeviceQueueCreateInfoDX12 & Source)
{
	if (this != &Source)
	{
		_NodeMask = Source._NodeMask;
		_Priority = Source._Priority;
		_Flags = Source._Flags;
		_Type = Source._Type;
	}
	return *this;
}

Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12& Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::operator=(DeviceQueueCreateInfoDX12&& Right) noexcept
{
	if (this != &Right)
	{
		_NodeMask = std::move(Right._NodeMask);
		_Priority = std::move(Right._Priority);
		_Flags = std::move(Right._Flags);
		_Type = std::move(Right._Type);

		Right._NodeMask = 0;
		Right._Priority = CommandQueuePriorityDX12::Normal;
		Right._Flags = CommandQueueFlagsDX12::None;
		Right._Type = CommandQueueTypeDX12::Direct;
	}
	return *this;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::GetNodeMask() const
{
	return _NodeMask;
}

const Elysium::Graphics::Rendering::DirectX12::CommandQueueFlagsDX12& Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::GetFlags() const
{
	return _Flags;
}

const Elysium::Graphics::Rendering::DirectX12::CommandQueuePriorityDX12& Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::GetPriority() const
{
	return _Priority;
}

const Elysium::Graphics::Rendering::DirectX12::CommandQueueTypeDX12& Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::GetType() const
{
	return _Type;
}

void Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::SetNodeMask(const Elysium::Core::uint32_t Value)
{
	_NodeMask = Value;
}

void Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::SetFlags(const CommandQueueFlagsDX12 Value)
{
	_Flags = Value;
}

void Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::SetPriority(const CommandQueuePriorityDX12 Value)
{
	_Priority = Value;
}

void Elysium::Graphics::Rendering::DirectX12::DeviceQueueCreateInfoDX12::SetType(const CommandQueueTypeDX12 Value)
{
	_Type = Value;
}
