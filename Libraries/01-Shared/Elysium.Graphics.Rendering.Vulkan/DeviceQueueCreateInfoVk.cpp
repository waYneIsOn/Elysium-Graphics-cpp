#include "DeviceQueueCreateInfoVk.hpp"

#ifndef ELYSIUM_CORE_ARGUMENTOUTOFRANGEEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArgumentOutOfRangeException.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk()
	: _Priorities(), _FamilyIndex(-1), _Capabilities(Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk::None)
{ }
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk(const DeviceQueueCreateInfoVk & Source)
	: _Priorities(Source._Priorities), _FamilyIndex(Source._FamilyIndex), _Capabilities(Source._Capabilities)
{ }
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::DeviceQueueCreateInfoVk(DeviceQueueCreateInfoVk&& Right) noexcept
	: _Priorities(), _FamilyIndex(-1), _Capabilities(Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk::None)
{
	*this = std::move(Right);
}
Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::~DeviceQueueCreateInfoVk()
{ }

Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::operator=(const DeviceQueueCreateInfoVk & Source)
{
	if (this != &Source)
	{
		_Priorities = Source._Priorities;
		_FamilyIndex = Source._FamilyIndex;
		_Capabilities = Source._Capabilities;
	}
	return *this;
}

Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::operator=(DeviceQueueCreateInfoVk&& Right) noexcept
{
	if (this != &Right)
	{
		_Priorities = std::move(Right._Priorities);
		_FamilyIndex = std::move(Right._FamilyIndex);
		_Capabilities = std::move(Right._Capabilities);

		Right._FamilyIndex = -1;
		Right._Capabilities = Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk::None;
	}
	return *this;
}

const Elysium::Core::uint32_t& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::GetFamilyIndex() const
{
	return _FamilyIndex;
}

const Elysium::Graphics::Rendering::Vulkan::QueueCapabilitiesVk& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::GetCapabilities() const
{
	return _Capabilities;
}

const Elysium::Core::Collections::Template::List<float>& Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::GetPriorities() const
{
	return _Priorities;
}

const void Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::SetFamilyIndex(const Elysium::Core::uint32_t Value)
{
	_FamilyIndex = Value;
}

const void Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::SetCapabilities(const QueueCapabilitiesVk Value)
{
	_Capabilities = Value;
}

const void Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::AddPriority(const float Value)
{
	if (Value < 0.0f || Value > 1.0f)
	{
		throw Elysium::Core::ArgumentOutOfRangeException(u8"Priority needs to be between 0.0f and 1.0f.");
	}

	_Priorities.Add(Value);
}

const void Elysium::Graphics::Rendering::Vulkan::DeviceQueueCreateInfoVk::ClearPriorities()
{
	_Priorities.Clear();
}

