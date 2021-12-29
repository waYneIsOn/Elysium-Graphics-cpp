#include "PhysicalDevicePropertiesVk.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FORMATCONVERTERVK
#include "FormatConverterVk.hpp"
#endif

Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::~PhysicalDevicePropertiesVk()
{ }

const Elysium::Core::Utf8StringView Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetName() const
{
	return Elysium::Core::Utf8StringView((char8_t*)_NativeProperties.deviceName);
}

const Elysium::Graphics::Rendering::PhysicalDeviceType Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetPhysicalGraphicsDeviceType() const
{
	return FormatConverterVk::Convert(_NativeProperties.deviceType);
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetApiVersion() const
{
	return _NativeProperties.apiVersion;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetDriverVersion() const
{
	return _NativeProperties.driverVersion;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetVendorId() const
{
	return _NativeProperties.vendorID;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetDeviceId() const
{
	return _NativeProperties.deviceID;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetResidencyStandard2DBlockShape() const
{
	return _NativeProperties.sparseProperties.residencyStandard2DBlockShape;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetResidencyStandard2DMultisampleBlockShape() const
{
	return _NativeProperties.sparseProperties.residencyStandard2DMultisampleBlockShape;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetResidencyStandard3DBlockShape() const
{
	return _NativeProperties.sparseProperties.residencyStandard3DBlockShape;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetResidencyAlignedMipSize() const
{
	return _NativeProperties.sparseProperties.residencyAlignedMipSize;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetResidencyNonResidentStrict() const
{
	return _NativeProperties.sparseProperties.residencyNonResidentStrict;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxImageDimension1D() const
{
	return _NativeProperties.limits.maxImageDimension1D;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxImageDimension2D() const
{
	return _NativeProperties.limits.maxImageDimension2D;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxImageDimension3D() const
{
	return _NativeProperties.limits.maxImageDimension3D;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxImageDimensionCube() const
{
	return _NativeProperties.limits.maxImageDimensionCube;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxImageArrayLayers() const
{
	return _NativeProperties.limits.maxImageArrayLayers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTexelBufferElements() const
{
	return _NativeProperties.limits.maxTexelBufferElements;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxUniformBufferRange() const
{
	return _NativeProperties.limits.maxUniformBufferRange;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxStorageBufferRange() const
{
	return _NativeProperties.limits.maxStorageBufferRange;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPushConstantsSize() const
{
	return _NativeProperties.limits.maxPushConstantsSize;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxMemoryAllocationCount() const
{
	return _NativeProperties.limits.maxMemoryAllocationCount;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxSamplerAllocationCount() const
{
	return _NativeProperties.limits.maxSamplerAllocationCount;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetBufferImageGranularity() const
{
	return _NativeProperties.limits.bufferImageGranularity;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSparseAddressSpaceSize() const
{
	return _NativeProperties.limits.sparseAddressSpaceSize;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxBoundDescriptorSets() const
{
	return _NativeProperties.limits.maxBoundDescriptorSets;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageDescriptorSamplers() const
{
	return _NativeProperties.limits.maxPerStageDescriptorSamplers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageDescriptorUniformBuffers() const
{
	return _NativeProperties.limits.maxPerStageDescriptorUniformBuffers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageDescriptorStorageBuffers() const
{
	return _NativeProperties.limits.maxPerStageDescriptorStorageBuffers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageDescriptorSampledImages() const
{
	return _NativeProperties.limits.maxPerStageDescriptorSampledImages;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageDescriptorStorageImages() const
{
	return _NativeProperties.limits.maxPerStageDescriptorStorageImages;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageDescriptorInputAttachments() const
{
	return _NativeProperties.limits.maxPerStageDescriptorInputAttachments;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxPerStageResources() const
{
	return _NativeProperties.limits.maxPerStageResources;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetSamplers() const
{
	return _NativeProperties.limits.maxDescriptorSetSamplers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetUniformBuffers() const
{
	return _NativeProperties.limits.maxDescriptorSetUniformBuffers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetUniformBuffersDynamic() const
{
	return _NativeProperties.limits.maxDescriptorSetUniformBuffersDynamic;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetStorageBuffers() const
{
	return _NativeProperties.limits.maxDescriptorSetStorageBuffers;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetStorageBuffersDynamic() const
{
	return _NativeProperties.limits.maxDescriptorSetStorageBuffersDynamic;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetSampledImages() const
{
	return _NativeProperties.limits.maxDescriptorSetSampledImages;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetStorageImages() const
{
	return _NativeProperties.limits.maxDescriptorSetStorageImages;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDescriptorSetInputAttachments() const
{
	return _NativeProperties.limits.maxDescriptorSetInputAttachments;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxVertexInputAttributes() const
{
	return _NativeProperties.limits.maxVertexInputAttributes;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxVertexInputBindings() const
{
	return _NativeProperties.limits.maxVertexInputBindings;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxVertexInputAttributeOffset() const
{
	return _NativeProperties.limits.maxVertexInputAttributeOffset;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxVertexInputBindingStride() const
{
	return _NativeProperties.limits.maxVertexInputBindingStride;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxVertexOutputComponents() const
{
	return _NativeProperties.limits.maxVertexOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationGenerationLevel() const
{
	return _NativeProperties.limits.maxTessellationGenerationLevel;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationPatchSize() const
{
	return _NativeProperties.limits.maxTessellationPatchSize;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationControlPerVertexInputComponents() const
{
	return _NativeProperties.limits.maxTessellationControlPerVertexInputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationControlPerVertexOutputComponents() const
{
	return _NativeProperties.limits.maxTessellationControlPerVertexOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationControlPerPatchOutputComponents() const
{
	return _NativeProperties.limits.maxTessellationControlPerPatchOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationControlTotalOutputComponents() const
{
	return _NativeProperties.limits.maxTessellationControlTotalOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationEvaluationInputComponents() const
{
	return _NativeProperties.limits.maxTessellationEvaluationInputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTessellationEvaluationOutputComponents() const
{
	return _NativeProperties.limits.maxTessellationEvaluationOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxGeometryShaderInvocations() const
{
	return _NativeProperties.limits.maxGeometryShaderInvocations;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxGeometryInputComponents() const
{
	return _NativeProperties.limits.maxGeometryInputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxGeometryOutputComponents() const
{
	return _NativeProperties.limits.maxGeometryOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxGeometryOutputVertices() const
{
	return _NativeProperties.limits.maxGeometryOutputVertices;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxGeometryTotalOutputComponents() const
{
	return _NativeProperties.limits.maxGeometryTotalOutputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFragmentInputComponents() const
{
	return _NativeProperties.limits.maxFragmentInputComponents;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFragmentOutputAttachments() const
{
	return _NativeProperties.limits.maxFragmentOutputAttachments;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFragmentDualSrcAttachments() const
{
	return _NativeProperties.limits.maxFragmentDualSrcAttachments;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFragmentCombinedOutputResources() const
{
	return _NativeProperties.limits.maxFragmentCombinedOutputResources;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxComputeSharedMemorySize() const
{
	return _NativeProperties.limits.maxComputeSharedMemorySize;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxComputeWorkGroupInvocations() const
{
	return _NativeProperties.limits.maxComputeWorkGroupInvocations;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSubPixelPrecisionBits() const
{
	return _NativeProperties.limits.subPixelPrecisionBits;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSubTexelPrecisionBits() const
{
	return _NativeProperties.limits.subTexelPrecisionBits;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMipmapPrecisionBits() const
{
	return _NativeProperties.limits.mipmapPrecisionBits;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDrawIndexedIndexValue() const
{
	return _NativeProperties.limits.maxDrawIndexedIndexValue;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxDrawIndirectCount() const
{
	return _NativeProperties.limits.maxDrawIndirectCount;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxSamplerLodBias() const
{
	return _NativeProperties.limits.maxSamplerLodBias;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxSamplerAnisotropy() const
{
	return _NativeProperties.limits.maxSamplerAnisotropy;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxViewports() const
{
	return _NativeProperties.limits.maxViewports;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetViewportSubPixelBits() const
{
	return _NativeProperties.limits.viewportSubPixelBits;
}

const size_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinMemoryMapAlignment() const
{
	return _NativeProperties.limits.minMemoryMapAlignment;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinTexelBufferOffsetAlignment() const
{
	return _NativeProperties.limits.minTexelBufferOffsetAlignment;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinUniformBufferOffsetAlignment() const
{
	return _NativeProperties.limits.minUniformBufferOffsetAlignment;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinStorageBufferOffsetAlignment() const
{
	return _NativeProperties.limits.minStorageBufferOffsetAlignment;
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinTexelOffset() const
{
	return _NativeProperties.limits.minTexelOffset;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTexelOffset() const
{
	return _NativeProperties.limits.maxTexelOffset;
}

const Elysium::Core::int32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinTexelGatherOffset() const
{
	return _NativeProperties.limits.minTexelGatherOffset;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxTexelGatherOffset() const
{
	return _NativeProperties.limits.maxTexelGatherOffset;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMinInterpolationOffset() const
{
	return _NativeProperties.limits.minInterpolationOffset;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxInterpolationOffset() const
{
	return _NativeProperties.limits.maxInterpolationOffset;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSubPixelInterpolationOffsetBits() const
{
	return _NativeProperties.limits.subPixelInterpolationOffsetBits;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFramebufferWidth() const
{
	return _NativeProperties.limits.maxFramebufferWidth;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFramebufferHeight() const
{
	return _NativeProperties.limits.maxFramebufferHeight;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxFramebufferLayers() const
{
	return _NativeProperties.limits.maxFramebufferLayers;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetFramebufferColorSampleCounts() const
{
	return _NativeProperties.limits.framebufferColorSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetFramebufferDepthSampleCounts() const
{
	return _NativeProperties.limits.framebufferDepthSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetFramebufferStencilSampleCounts() const
{
	return _NativeProperties.limits.framebufferStencilSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetFramebufferNoAttachmentsSampleCounts() const
{
	return _NativeProperties.limits.framebufferNoAttachmentsSampleCounts;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxColorAttachments() const
{
	return _NativeProperties.limits.maxColorAttachments;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSampledImageColorSampleCounts() const
{
	return _NativeProperties.limits.sampledImageColorSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSampledImageIntegerSampleCounts() const
{
	return _NativeProperties.limits.sampledImageIntegerSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSampledImageDepthSampleCounts() const
{
	return _NativeProperties.limits.sampledImageDepthSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetSampledImageStencilSampleCounts() const
{
	return _NativeProperties.limits.sampledImageStencilSampleCounts;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetStorageImageSampleCounts() const
{
	return _NativeProperties.limits.storageImageSampleCounts;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxSampleMaskWords() const
{
	return _NativeProperties.limits.maxSampleMaskWords;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetTimestampComputeAndGraphics() const
{
	return _NativeProperties.limits.timestampComputeAndGraphics;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetTimestampPeriod() const
{
	return _NativeProperties.limits.timestampPeriod;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxClipDistances() const
{
	return _NativeProperties.limits.maxClipDistances;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxCullDistances() const
{
	return _NativeProperties.limits.maxCullDistances;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetMaxCombinedClipAndCullDistances() const
{
	return _NativeProperties.limits.maxCombinedClipAndCullDistances;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetDiscreteQueuePriorities() const
{
	return _NativeProperties.limits.discreteQueuePriorities;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetPointSizeGranularity() const
{
	return _NativeProperties.limits.pointSizeGranularity;
}

const float Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetLineWidthGranularity() const
{
	return _NativeProperties.limits.lineWidthGranularity;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetStrictLines() const
{
	return _NativeProperties.limits.strictLines;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetStandardSampleLocations() const
{
	return _NativeProperties.limits.standardSampleLocations;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetOptimalBufferCopyOffsetAlignment() const
{
	return _NativeProperties.limits.optimalBufferCopyOffsetAlignment;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetOptimalBufferCopyRowPitchAlignment() const
{
	return _NativeProperties.limits.optimalBufferCopyRowPitchAlignment;
}

const Elysium::Core::uint64_t Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::GetNonCoherentAtomSize() const
{
	return _NativeProperties.limits.nonCoherentAtomSize;
}

Elysium::Graphics::Rendering::Vulkan::PhysicalDevicePropertiesVk::PhysicalDevicePropertiesVk()
{ }
