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

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class Array;
}

namespace Elysium::Graphics::Rendering::DirectX12
{
	class LogicalDeviceDX12;
	class PhysicalDeviceDX12;

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API QueueDX12 final : public INativeQueue
	{
		friend class Elysium::Core::Collections::Template::Array<QueueDX12>;
		friend class LogicalDeviceDX12;
		friend class PhysicalDeviceDX12;
	public:
		QueueDX12(const QueueDX12& Source) = delete;
		QueueDX12(QueueDX12&& Right) noexcept = delete;
		virtual ~QueueDX12();

		QueueDX12& operator=(const QueueDX12& Source) = delete;
		QueueDX12& operator=(QueueDX12&& Right) noexcept = delete;
	private:
		QueueDX12();

		ID3D12CommandQueue* _NativeQueue;
		D3D12_COMMAND_LIST_TYPE _NativeType;
		Elysium::Core::uint32_t _Index;
	};
}
#endif
