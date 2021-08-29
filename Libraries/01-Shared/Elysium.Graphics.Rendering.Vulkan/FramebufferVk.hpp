/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAY
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Array.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER
#include "../Elysium.Graphics/INativeFrameBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_INCLUDEVK
#include "IncludeVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_RENDERPASSVK
#include "RenderPassVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API FrameBufferVk final : public Native::INativeFrameBuffer
	{
		friend class CommandBufferVk;
		friend class GraphicsPipelineVk;
	public:
		FrameBufferVk(const GraphicsDeviceVk& GraphicsDevice, const RenderPassVk& RenderPass);
		FrameBufferVk(const FrameBufferVk& Source) = delete;
		FrameBufferVk(FrameBufferVk&& Right) noexcept = delete;
		virtual ~FrameBufferVk();

		FrameBufferVk& operator=(const FrameBufferVk& Source) = delete;
		FrameBufferVk& operator=(FrameBufferVk&& Right) noexcept = delete;

		virtual const Elysium::Core::uint32_t GetWidth() const override;
		virtual const Elysium::Core::uint32_t GetHeight() const override;
		virtual const Elysium::Core::uint32_t GetDepth() const override;
	private:
		const GraphicsDeviceVk& _GraphicsDevice;
		const RenderPassVk& _RenderPass;
		VkExtent3D _Extent;

		Elysium::Core::Collections::Template::Array<VkImage> _NativeImages;
		VkDeviceMemory _NativeImageMemory;
		Elysium::Core::Collections::Template::Array<VkImageView> _NativeImageViews;
		Elysium::Core::Collections::Template::Array<VkFramebuffer> _NativeFramebuffers;

		VkExtent3D RetrieveExtent();
		Elysium::Core::Collections::Template::Array<VkImage> CreateNativeImages();
		VkDeviceMemory CreateNativeImageMemory();
		Elysium::Core::Collections::Template::Array<VkImageView> CreateNativeImageViews();
		Elysium::Core::Collections::Template::Array<VkFramebuffer> CreateNativeFramebuffers();

		void DestroyNativeFramebuffers();
		void DestroyNativeImageViews();
		void DestroyNativeImageMemory();
		void DestroyNativeImages();

		void Control_SizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);
	};
}
#endif
