#include "PhysicalDeviceFeaturesVk.hpp"

Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::~PhysicalDeviceFeaturesVk()
{ }

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetRobustBufferAccess() const
{
	return _NativeFeatures.robustBufferAccess;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetFullDrawIndexUint32() const
{
	return _NativeFeatures.fullDrawIndexUint32;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetImageCubeArray() const
{
	return _NativeFeatures.imageCubeArray;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetIndependentBlend() const
{
	return _NativeFeatures.independentBlend;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetGeometryShader() const
{
	return _NativeFeatures.geometryShader;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetTessellationShader() const
{
	return _NativeFeatures.tessellationShader;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSampleRateShading() const
{
	return _NativeFeatures.sampleRateShading;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetDualSrcBlend() const
{
	return _NativeFeatures.dualSrcBlend;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetLogicOp() const
{
	return _NativeFeatures.logicOp;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetMultiDrawIndirect() const
{
	return _NativeFeatures.multiDrawIndirect;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetDrawIndirectFirstInstance() const
{
	return _NativeFeatures.drawIndirectFirstInstance;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetDepthClamp() const
{
	return _NativeFeatures.depthClamp;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetDepthBiasClamp() const
{
	return _NativeFeatures.depthBiasClamp;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetFillModeNonSolid() const
{
	return _NativeFeatures.fillModeNonSolid;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetDepthBounds() const
{
	return _NativeFeatures.depthBounds;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetWideLines() const
{
	return _NativeFeatures.wideLines;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetLargePoints() const
{
	return _NativeFeatures.largePoints;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetAlphaToOne() const
{
	return _NativeFeatures.alphaToOne;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetMultiViewport() const
{
	return _NativeFeatures.multiViewport;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSamplerAnisotropy() const
{
	return _NativeFeatures.samplerAnisotropy;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetTextureCompressionETC2() const
{
	return _NativeFeatures.textureCompressionETC2;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetTextureCompressionASTC_LDR() const
{
	return _NativeFeatures.textureCompressionASTC_LDR;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetTextureCompressionBC() const
{
	return _NativeFeatures.textureCompressionBC;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetOcclusionQueryPrecise() const
{
	return _NativeFeatures.occlusionQueryPrecise;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetPipelineStatisticsQuery() const
{
	return _NativeFeatures.pipelineStatisticsQuery;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetVertexPipelineStoresAndAtomics() const
{
	return _NativeFeatures.vertexPipelineStoresAndAtomics;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetFragmentStoresAndAtomics() const
{
	return _NativeFeatures.fragmentStoresAndAtomics;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderTessellationAndGeometryPointSize() const
{
	return _NativeFeatures.shaderTessellationAndGeometryPointSize;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderImageGatherExtended() const
{
	return _NativeFeatures.shaderImageGatherExtended;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderStorageImageExtendedFormats() const
{
	return _NativeFeatures.shaderStorageImageExtendedFormats;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderStorageImageMultisample() const
{
	return _NativeFeatures.shaderStorageImageMultisample;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderStorageImageReadWithoutFormat() const
{
	return _NativeFeatures.shaderStorageImageReadWithoutFormat;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderStorageImageWriteWithoutFormat() const
{
	return _NativeFeatures.shaderStorageImageWriteWithoutFormat;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderUniformBufferArrayDynamicIndexing() const
{
	return _NativeFeatures.shaderUniformBufferArrayDynamicIndexing;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderSampledImageArrayDynamicIndexing() const
{
	return _NativeFeatures.shaderSampledImageArrayDynamicIndexing;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderStorageBufferArrayDynamicIndexing() const
{
	return _NativeFeatures.shaderStorageBufferArrayDynamicIndexing;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderStorageImageArrayDynamicIndexing() const
{
	return _NativeFeatures.shaderStorageImageArrayDynamicIndexing;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderClipDistance() const
{
	return _NativeFeatures.shaderClipDistance;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderCullDistance() const
{
	return _NativeFeatures.shaderCullDistance;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderFloat64() const
{
	return _NativeFeatures.shaderFloat64;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderInt64() const
{
	return _NativeFeatures.shaderInt64;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderInt16() const
{
	return _NativeFeatures.shaderInt16;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderResourceResidency() const
{
	return _NativeFeatures.shaderResourceResidency;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetShaderResourceMinLod() const
{
	return _NativeFeatures.shaderResourceMinLod;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseBinding() const
{
	return _NativeFeatures.sparseBinding;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidencyBuffer() const
{
	return _NativeFeatures.sparseResidencyBuffer;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidencyImage2D() const
{
	return _NativeFeatures.sparseResidencyImage2D;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidencyImage3D() const
{
	return _NativeFeatures.sparseResidencyImage3D;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidency2Samples() const
{
	return _NativeFeatures.sparseResidency2Samples;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidency4Samples() const
{
	return _NativeFeatures.sparseResidency4Samples;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidency8Samples() const
{
	return _NativeFeatures.sparseResidency8Samples;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidency16Samples() const
{
	return _NativeFeatures.sparseResidency16Samples;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetSparseResidencyAliased() const
{
	return _NativeFeatures.sparseResidencyAliased;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetVariableMultisampleRate() const
{
	return _NativeFeatures.variableMultisampleRate;
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::GetInheritedQueries() const
{
	return _NativeFeatures.inheritedQueries;
}

Elysium::Graphics::Rendering::Vulkan::PhysicalDeviceFeaturesVk::PhysicalDeviceFeaturesVk()
{ }
