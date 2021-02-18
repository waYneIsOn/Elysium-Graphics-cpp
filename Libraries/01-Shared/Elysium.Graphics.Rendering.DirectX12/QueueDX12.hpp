/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_QUEUEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_QUEUEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_INATIVEQUEUE
#include "../Elysium.Graphics/INativeQueue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_COMMANDQUEUETYPEDX12
#include "CommandQueueTypeDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_LOGICALDEVICEDX12
#include "LogicalDeviceDX12.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API QueueDX12 final : public INativeQueue
	{
		friend class LogicalDeviceDX12;
		friend class SwapchainDX12;
	public:
		QueueDX12(const LogicalDeviceDX12& LogicalDevice, const CommandQueueTypeDX12 Family, Elysium::Core::uint32_t Index);
		QueueDX12(const QueueDX12& Source) = delete;
		QueueDX12(QueueDX12&& Right) noexcept = delete;
		virtual ~QueueDX12();

		QueueDX12& operator=(const QueueDX12& Source) = delete;
		QueueDX12& operator=(QueueDX12&& Right) noexcept = delete;

		virtual const Elysium::Core::uint32_t GetFamilyIndex() const override;

		virtual void Submit(const INativeSemaphore& PresentSemaphore, const INativeSemaphore& RenderSemaphore, const INativeFence& Fence) override;
		virtual void Wait() const override;
	private:
		const LogicalDeviceDX12& _LogicalDevice;
		const CommandQueueTypeDX12 _Family;
		const Elysium::Core::uint32_t _Index;

		ID3D12CommandQueue* _NativeQueue;
	};
}
#endif
