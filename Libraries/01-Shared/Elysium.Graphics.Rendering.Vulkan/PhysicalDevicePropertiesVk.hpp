/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEPROPERTIESVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEPROPERTIESVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_PRIMITIVES
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Primitives.hpp"
#endif

#ifndef ELYSIUM_CORE_STRINGVIEW
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/StringView.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICETYPEVK
#include "PhysicalDeviceTypeVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class GraphicsInstanceVk;
	class PhysicalDeviceVk;

	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API PhysicalDevicePropertiesVk final
	{
		friend class GraphicsInstanceVk;
		friend class PhysicalDeviceVk;
	public:
		PhysicalDevicePropertiesVk(const PhysicalDevicePropertiesVk& Source) = delete;
		PhysicalDevicePropertiesVk(PhysicalDevicePropertiesVk&& Right) noexcept = delete;
		~PhysicalDevicePropertiesVk();

		PhysicalDevicePropertiesVk& operator=(const PhysicalDevicePropertiesVk& Source) = delete;
		PhysicalDevicePropertiesVk& operator=(PhysicalDevicePropertiesVk&& Right) noexcept = delete;
		
		const Elysium::Core::StringView GetName() const;
		const PhysicalDeviceTypeVk GetPhysicalGraphicsDeviceType() const;
		const Elysium::Core::uint32_t GetApiVersion() const;
		const Elysium::Core::uint32_t GetDriverVersion() const;
		const Elysium::Core::uint32_t GetVendorId() const;
		const Elysium::Core::uint32_t GetDeviceId() const;
		//const Elysium::Core::uint8_t pipelineCacheUUID() const;

		const Elysium::Core::uint32_t GetResidencyStandard2DBlockShape() const;
		const Elysium::Core::uint32_t GetResidencyStandard2DMultisampleBlockShape() const;
		const Elysium::Core::uint32_t GetResidencyStandard3DBlockShape() const;
		const Elysium::Core::uint32_t GetResidencyAlignedMipSize() const;
		const Elysium::Core::uint32_t GetResidencyNonResidentStrict() const;

		const Elysium::Core::uint32_t GetMaxImageDimension1D() const;
		const Elysium::Core::uint32_t GetMaxImageDimension2D() const;
		const Elysium::Core::uint32_t GetMaxImageDimension3D() const;
		const Elysium::Core::uint32_t GetMaxImageDimensionCube() const;
		const Elysium::Core::uint32_t GetMaxImageArrayLayers() const;
		const Elysium::Core::uint32_t GetMaxTexelBufferElements() const;
		const Elysium::Core::uint32_t GetMaxUniformBufferRange() const;
		const Elysium::Core::uint32_t GetMaxStorageBufferRange() const;
		const Elysium::Core::uint32_t GetMaxPushConstantsSize() const;
		const Elysium::Core::uint32_t GetMaxMemoryAllocationCount() const;
		const Elysium::Core::uint32_t GetMaxSamplerAllocationCount() const;
		const Elysium::Core::uint64_t GetBufferImageGranularity() const;
		const Elysium::Core::uint64_t GetSparseAddressSpaceSize() const;
		const Elysium::Core::uint32_t GetMaxBoundDescriptorSets() const;
		const Elysium::Core::uint32_t GetMaxPerStageDescriptorSamplers() const;
		const Elysium::Core::uint32_t GetMaxPerStageDescriptorUniformBuffers() const;
		const Elysium::Core::uint32_t GetMaxPerStageDescriptorStorageBuffers() const;
		const Elysium::Core::uint32_t GetMaxPerStageDescriptorSampledImages() const;
		const Elysium::Core::uint32_t GetMaxPerStageDescriptorStorageImages() const;
		const Elysium::Core::uint32_t GetMaxPerStageDescriptorInputAttachments() const;
		const Elysium::Core::uint32_t GetMaxPerStageResources() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetSamplers() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetUniformBuffers() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetUniformBuffersDynamic() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetStorageBuffers() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetStorageBuffersDynamic() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetSampledImages() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetStorageImages() const;
		const Elysium::Core::uint32_t GetMaxDescriptorSetInputAttachments() const;
		const Elysium::Core::uint32_t GetMaxVertexInputAttributes() const;
		const Elysium::Core::uint32_t GetMaxVertexInputBindings() const;
		const Elysium::Core::uint32_t GetMaxVertexInputAttributeOffset() const;
		const Elysium::Core::uint32_t GetMaxVertexInputBindingStride() const;
		const Elysium::Core::uint32_t GetMaxVertexOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxTessellationGenerationLevel() const;
		const Elysium::Core::uint32_t GetMaxTessellationPatchSize() const;
		const Elysium::Core::uint32_t GetMaxTessellationControlPerVertexInputComponents() const;
		const Elysium::Core::uint32_t GetMaxTessellationControlPerVertexOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxTessellationControlPerPatchOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxTessellationControlTotalOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxTessellationEvaluationInputComponents() const;
		const Elysium::Core::uint32_t GetMaxTessellationEvaluationOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxGeometryShaderInvocations() const;
		const Elysium::Core::uint32_t GetMaxGeometryInputComponents() const;
		const Elysium::Core::uint32_t GetMaxGeometryOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxGeometryOutputVertices() const;
		const Elysium::Core::uint32_t GetMaxGeometryTotalOutputComponents() const;
		const Elysium::Core::uint32_t GetMaxFragmentInputComponents() const;
		const Elysium::Core::uint32_t GetMaxFragmentOutputAttachments() const;
		const Elysium::Core::uint32_t GetMaxFragmentDualSrcAttachments() const;
		const Elysium::Core::uint32_t GetMaxFragmentCombinedOutputResources() const;
		const Elysium::Core::uint32_t GetMaxComputeSharedMemorySize() const;
		//const Elysium::Core::uint32_t mGetMxComputeWorkGroupCount() const;
		const Elysium::Core::uint32_t GetMaxComputeWorkGroupInvocations() const;
		//const Elysium::Core::uint32_t GetMaxComputeWorkGroupSize() const;
		const Elysium::Core::uint32_t GetSubPixelPrecisionBits() const;
		const Elysium::Core::uint32_t GetSubTexelPrecisionBits() const;
		const Elysium::Core::uint32_t GetMipmapPrecisionBits() const;
		const Elysium::Core::uint32_t GetMaxDrawIndexedIndexValue() const;
		const Elysium::Core::uint32_t GetMaxDrawIndirectCount() const;
		const float GetMaxSamplerLodBias() const;
		const float GetMaxSamplerAnisotropy() const;
		const Elysium::Core::uint32_t GetMaxViewports() const;
		//const Elysium::Core::uint32_t GetMaxViewportDimensions() const;
		//const float GetViewportBoundsRange() const;
		const Elysium::Core::uint32_t GetViewportSubPixelBits() const;
		const size_t GetMinMemoryMapAlignment() const;
		const Elysium::Core::uint64_t GetMinTexelBufferOffsetAlignment() const;
		const Elysium::Core::uint64_t GetMinUniformBufferOffsetAlignment() const;
		const Elysium::Core::uint64_t GetMinStorageBufferOffsetAlignment() const;
		const Elysium::Core::int32_t GetMinTexelOffset() const;
		const Elysium::Core::uint32_t GetMaxTexelOffset() const;
		const Elysium::Core::int32_t GetMinTexelGatherOffset() const;
		const Elysium::Core::uint32_t GetMaxTexelGatherOffset() const;
		const float GetMinInterpolationOffset() const;
		const float GetMaxInterpolationOffset() const;
		const Elysium::Core::uint32_t GetSubPixelInterpolationOffsetBits() const;
		const Elysium::Core::uint32_t GetMaxFramebufferWidth() const;
		const Elysium::Core::uint32_t GetMaxFramebufferHeight() const;
		const Elysium::Core::uint32_t GetMaxFramebufferLayers() const;
		const Elysium::Core::uint64_t GetFramebufferColorSampleCounts() const;
		const Elysium::Core::uint64_t GetFramebufferDepthSampleCounts() const;
		const Elysium::Core::uint64_t GetFramebufferStencilSampleCounts() const;
		const Elysium::Core::uint64_t GetFramebufferNoAttachmentsSampleCounts() const;
		const Elysium::Core::uint32_t GetMaxColorAttachments() const;
		const Elysium::Core::uint64_t GetSampledImageColorSampleCounts() const;
		const Elysium::Core::uint64_t GetSampledImageIntegerSampleCounts() const;
		const Elysium::Core::uint64_t GetSampledImageDepthSampleCounts() const;
		const Elysium::Core::uint64_t GetSampledImageStencilSampleCounts() const;
		const Elysium::Core::uint64_t GetStorageImageSampleCounts() const;
		const Elysium::Core::uint32_t GetMaxSampleMaskWords() const;
		const Elysium::Core::uint32_t GetTimestampComputeAndGraphics() const;
		const float GetTimestampPeriod() const;
		const Elysium::Core::uint32_t GetMaxClipDistances() const;
		const Elysium::Core::uint32_t GetMaxCullDistances() const;
		const Elysium::Core::uint32_t GetMaxCombinedClipAndCullDistances() const;
		const Elysium::Core::uint32_t GetDiscreteQueuePriorities() const;
		//const float GetPointSizeRange() const;
		//const float GetLineWidthRange() const;
		const float GetPointSizeGranularity() const;
		const float GetLineWidthGranularity() const;
		const Elysium::Core::uint32_t GetStrictLines() const;
		const Elysium::Core::uint32_t GetStandardSampleLocations() const;
		const Elysium::Core::uint64_t GetOptimalBufferCopyOffsetAlignment() const;
		const Elysium::Core::uint64_t GetOptimalBufferCopyRowPitchAlignment() const;
		const Elysium::Core::uint64_t GetNonCoherentAtomSize() const;
	private:
		PhysicalDevicePropertiesVk();

		VkPhysicalDeviceProperties _NativeProperties = VkPhysicalDeviceProperties();
	};
}
#endif
