/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PHYSICALDEVICEDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PHYSICALDEVICEDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_IPHYSICALDEVICE
#include "../Elysium.Graphics/IPhysicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_LOGICALDEVICEDX12
#include "LogicalDeviceDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_INCLUDEDX12
#include "IncludeDX12.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12
#include "PresentationParametersDX12.hpp"
#endif

namespace Elysium::Core::Collections::Template
{
	template <typename T>
	class Array;
}

namespace Elysium::Graphics::Rendering::DirectX12
{
	class GraphicsInstanceDX12;

	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API PhysicalDeviceDX12 final : public IPhysicalDevice
	{
		friend class Elysium::Core::Collections::Template::Array<PhysicalDeviceDX12>;
		friend class GraphicsInstanceDX12;
	public:
		PhysicalDeviceDX12(const PhysicalDeviceDX12& Source) = delete;
		PhysicalDeviceDX12(PhysicalDeviceDX12&& Right) noexcept = delete;
		virtual ~PhysicalDeviceDX12();

		PhysicalDeviceDX12& operator=(const PhysicalDeviceDX12& Source) = delete;
		PhysicalDeviceDX12& operator=(PhysicalDeviceDX12&& Right) noexcept = delete;

		virtual const Elysium::Core::String GetName() const override;

		const Elysium::Core::uint32_t GetVendorId() const;
		const Elysium::Core::uint32_t GetDeviceId() const;
		const Elysium::Core::uint32_t GetSubSysId() const;
		const Elysium::Core::uint32_t GetRevision() const;
		const size_t GetDedicatedVideoMemory() const;
		const size_t GetDedicatedSystemMemory() const;
		const size_t GetSharedSystemMemory() const;

		LogicalDeviceDX12 CreateLogicalDevice(const PresentationParametersDX12& PresentationParameters);
	private:
		PhysicalDeviceDX12();

		IDXGIAdapter1* _NativeAdapter;
		DXGI_ADAPTER_DESC1 _NativeAdapterDescription;

		void SetNativeAdapter(IDXGIAdapter1* NativeAdapter);
	};
}
#endif
