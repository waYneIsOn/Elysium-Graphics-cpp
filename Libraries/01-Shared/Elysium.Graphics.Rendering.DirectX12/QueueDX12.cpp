#include "QueueDX12.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#include "ExceptionDX12.hpp"
#endif

Elysium::Graphics::Rendering::DirectX12::QueueDX12::QueueDX12(const LogicalDeviceDX12& LogicalDevice, const CommandQueueTypeDX12 Family, Elysium::Core::uint32_t Index)
	: _LogicalDevice(LogicalDevice), _Family(Family), _Index(Index), _NativeQueue(nullptr)
{
	const Elysium::Core::uint32_t FamilyIndex = static_cast<const Elysium::Core::uint32_t>(_Family);

	D3D12_COMMAND_QUEUE_DESC QueueCreationInfo = D3D12_COMMAND_QUEUE_DESC();
	QueueCreationInfo.Type = (D3D12_COMMAND_LIST_TYPE)Family;
	QueueCreationInfo.Flags = (D3D12_COMMAND_QUEUE_FLAGS)_LogicalDevice.GetPresentationParameters()._DeviceQueueCreateInfos[FamilyIndex].GetFlags();
	QueueCreationInfo.Priority = (D3D12_COMMAND_QUEUE_PRIORITY)_LogicalDevice.GetPresentationParameters()._DeviceQueueCreateInfos[FamilyIndex].GetPriority();
	QueueCreationInfo.NodeMask = _LogicalDevice.GetPresentationParameters()._DeviceQueueCreateInfos[FamilyIndex].GetNodeMask();

	long Result;
	if (FAILED((Result = _LogicalDevice._NativeDevice->CreateCommandQueue(&QueueCreationInfo, IID_PPV_ARGS(&_NativeQueue)))))
	{
		throw ExceptionDX12(Result);
	}
}
Elysium::Graphics::Rendering::DirectX12::QueueDX12::~QueueDX12()
{
	if (_NativeQueue != nullptr)
	{
		_NativeQueue->Release();
		_NativeQueue = nullptr;
	}
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::DirectX12::QueueDX12::GetFamilyIndex() const
{
	return static_cast<const Elysium::Core::uint32_t>(_Family);
}

void Elysium::Graphics::Rendering::DirectX12::QueueDX12::Submit(const INativeSemaphore& PresentSemaphore, const INativeSemaphore& RenderSemaphore, const INativeFence& Fence)
{
	throw 1;
}

void Elysium::Graphics::Rendering::DirectX12::QueueDX12::Wait() const
{
	//_NativeQueue->Wait(FENCE, TIMEOUT);
	throw 1;
}
