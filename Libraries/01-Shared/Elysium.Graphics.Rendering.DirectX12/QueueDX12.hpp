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

#ifndef ELYSIUM_GRAPHICS_RENDERING_IQUEUE
#include "../Elysium.Graphics/IQueue.hpp"
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

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API QueueDX12 final : public IQueue
	{
		friend class Elysium::Core::Collections::Template::Array<QueueDX12>;
		friend class LogicalDeviceDX12;
	public:
		QueueDX12(const QueueDX12& Source) = delete;
		QueueDX12(QueueDX12&& Right) noexcept = delete;
		virtual ~QueueDX12();

		QueueDX12& operator=(const QueueDX12& Source) = delete;
		QueueDX12& operator=(QueueDX12&& Right) noexcept = delete;
	private:
		QueueDX12();

		ID3D12CommandQueue* _NativeQueue;
	};
}
#endif
