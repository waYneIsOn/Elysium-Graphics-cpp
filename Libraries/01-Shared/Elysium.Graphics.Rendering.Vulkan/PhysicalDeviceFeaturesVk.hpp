/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEFEATURESVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEFEATURESVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PhysicalDeviceFeaturesVk final
	{
		friend class GraphicsInstanceVk;
		friend class PhysicalDeviceVk;
	public:
		PhysicalDeviceFeaturesVk(const PhysicalDeviceFeaturesVk& Source) = delete;
		PhysicalDeviceFeaturesVk(PhysicalDeviceFeaturesVk&& Right) noexcept = delete;
		~PhysicalDeviceFeaturesVk();

		PhysicalDeviceFeaturesVk& operator=(const PhysicalDeviceFeaturesVk& Source) = delete;
		PhysicalDeviceFeaturesVk& operator=(PhysicalDeviceFeaturesVk&& Right) noexcept = delete;

		const Elysium::Core::uint32_t GetRobustBufferAccess() const;
		const Elysium::Core::uint32_t GetFullDrawIndexUint32() const;
		const Elysium::Core::uint32_t GetImageCubeArray() const;
		const Elysium::Core::uint32_t GetIndependentBlend() const;
		const Elysium::Core::uint32_t GetGeometryShader() const;
		const Elysium::Core::uint32_t GetTessellationShader() const;
		const Elysium::Core::uint32_t GetSampleRateShading() const;
		const Elysium::Core::uint32_t GetDualSrcBlend() const;
		const Elysium::Core::uint32_t GetLogicOp() const;
		const Elysium::Core::uint32_t GetMultiDrawIndirect() const;
		const Elysium::Core::uint32_t GetDrawIndirectFirstInstance() const;
		const Elysium::Core::uint32_t GetDepthClamp() const;
		const Elysium::Core::uint32_t GetDepthBiasClamp() const;
		const Elysium::Core::uint32_t GetFillModeNonSolid() const;
		const Elysium::Core::uint32_t GetDepthBounds() const;
		const Elysium::Core::uint32_t GetWideLines() const;
		const Elysium::Core::uint32_t GetLargePoints() const;
		const Elysium::Core::uint32_t GetAlphaToOne() const;
		const Elysium::Core::uint32_t GetMultiViewport() const;
		const Elysium::Core::uint32_t GetSamplerAnisotropy() const;
		const Elysium::Core::uint32_t GetTextureCompressionETC2() const;
		const Elysium::Core::uint32_t GetTextureCompressionASTC_LDR() const;
		const Elysium::Core::uint32_t GetTextureCompressionBC() const;
		const Elysium::Core::uint32_t GetOcclusionQueryPrecise() const;
		const Elysium::Core::uint32_t GetPipelineStatisticsQuery() const;
		const Elysium::Core::uint32_t GetVertexPipelineStoresAndAtomics() const;
		const Elysium::Core::uint32_t GetFragmentStoresAndAtomics() const;
		const Elysium::Core::uint32_t GetShaderTessellationAndGeometryPointSize() const;
		const Elysium::Core::uint32_t GetShaderImageGatherExtended() const;
		const Elysium::Core::uint32_t GetShaderStorageImageExtendedFormats() const;
		const Elysium::Core::uint32_t GetShaderStorageImageMultisample() const;
		const Elysium::Core::uint32_t GetShaderStorageImageReadWithoutFormat() const;
		const Elysium::Core::uint32_t GetShaderStorageImageWriteWithoutFormat() const;
		const Elysium::Core::uint32_t GetShaderUniformBufferArrayDynamicIndexing() const;
		const Elysium::Core::uint32_t GetShaderSampledImageArrayDynamicIndexing() const;
		const Elysium::Core::uint32_t GetShaderStorageBufferArrayDynamicIndexing() const;
		const Elysium::Core::uint32_t GetShaderStorageImageArrayDynamicIndexing() const;
		const Elysium::Core::uint32_t GetShaderClipDistance() const;
		const Elysium::Core::uint32_t GetShaderCullDistance() const;
		const Elysium::Core::uint32_t GetShaderFloat64() const;
		const Elysium::Core::uint32_t GetShaderInt64() const;
		const Elysium::Core::uint32_t GetShaderInt16() const;
		const Elysium::Core::uint32_t GetShaderResourceResidency() const;
		const Elysium::Core::uint32_t GetShaderResourceMinLod() const;
		const Elysium::Core::uint32_t GetSparseBinding() const;
		const Elysium::Core::uint32_t GetSparseResidencyBuffer() const;
		const Elysium::Core::uint32_t GetSparseResidencyImage2D() const;
		const Elysium::Core::uint32_t GetSparseResidencyImage3D() const;
		const Elysium::Core::uint32_t GetSparseResidency2Samples() const;
		const Elysium::Core::uint32_t GetSparseResidency4Samples() const;
		const Elysium::Core::uint32_t GetSparseResidency8Samples() const;
		const Elysium::Core::uint32_t GetSparseResidency16Samples() const;
		const Elysium::Core::uint32_t GetSparseResidencyAliased() const;
		const Elysium::Core::uint32_t GetVariableMultisampleRate() const;
		const Elysium::Core::uint32_t GetInheritedQueries() const;
	private:
		PhysicalDeviceFeaturesVk();

		VkPhysicalDeviceFeatures _NativeFeatures = VkPhysicalDeviceFeatures();
	};
}
#endif
