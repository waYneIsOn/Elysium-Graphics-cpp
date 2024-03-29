/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK
#define ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSDEVICEVK

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_CONTAINER_VECTOR
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Vector.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_CONTROL
#include "../Elysium.Graphics.Presentation/Control.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#include "../Elysium.Graphics/INativeGraphicsDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FENCEVK
#include "FenceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_FRAMEBUFFERVK
#include "FramebufferVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_GRAPHICSINSTANCEVK
#include "GraphicsInstanceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PHYSICALDEVICEVK
#include "PhysicalDeviceVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_PRESENTATIONPARAMETERSVK
#include "PresentationParametersVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_QUEUEVK
#include "QueueVk.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_VULKAN_SEMAPHOREVK
#include "SemaphoreVk.hpp"
#endif

namespace Elysium::Graphics::Rendering::Vulkan
{
	class ELYSIUM_GRAPHICS_RENDERING_VULKAN_API GraphicsDeviceVk final : public Native::INativeGraphicsDevice
	{
		friend class CommandBufferVk;
		friend class CommandPoolVk;
		friend class DepthBufferVk;
		friend class FenceVk;
		friend class FrameBufferVk;
		friend class GraphicsPipelineVk;
		friend class IndexBufferVk;
		friend class QueueVk;
		friend class RenderPassVk;
		friend class SemaphoreVk;
		friend class ShaderModuleVk;
		friend class SwapchainFrameBufferVk;
		friend class VertexBufferVk;
	public:
		GraphicsDeviceVk(const GraphicsInstanceVk& GraphicsInstance, const PhysicalDeviceVk& PhysicalDevice, PresentationParametersVk& PresentationParameters);
		
		GraphicsDeviceVk(const GraphicsDeviceVk& Source) = delete;

		GraphicsDeviceVk(GraphicsDeviceVk&& Right) noexcept = delete;

		virtual ~GraphicsDeviceVk();
	public:
		GraphicsDeviceVk& operator=(const GraphicsDeviceVk& Source) = delete;

		GraphicsDeviceVk& operator=(GraphicsDeviceVk&& Right) noexcept = delete;
	public:
		virtual const PresentationParametersVk& GetPresentationParameters() const override;

		virtual const SurfaceFormat GetBackBufferFormat() const override;

		virtual const FenceVk& GetRenderFence() const override;

		virtual const SemaphoreVk& GetPresentationSemaphore() const override;

		virtual const SemaphoreVk& GetRenderSemaphore() const override;

		virtual QueueVk& GetGraphicsQueue() override;

		virtual QueueVk& GetPresentationQueue() override;
	public:
		virtual Native::INativeRenderPass* CreateRenderPass(const SurfaceFormat SurfaceFormat) override;

		virtual Native::INativeFrameBuffer* CreateFrameBuffer(const Native::INativeRenderPass& RenderPass) override;
		virtual Native::INativeGraphicsPipeline* CreateGraphicsPipeline() override;


		virtual Native::INativeVertexBuffer* CreateVertexBuffer(const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage) override;
		
		virtual Native::INativeIndexBuffer* CreateIndexBuffer(const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount, const BufferUsage Usage) override;
		
		virtual Native::INativeShaderModule* CreateShaderModule(const Elysium::Core::Template::Container::Vector<Elysium::Core::byte>& ByteCode) override;

		virtual void Wait() const override;
		
		virtual const bool BeginDraw(Native::INativeFence& RenderFence, const Native::INativeSemaphore& PresentationSemaphore) override;
		
		virtual void EndDraw(const Native::INativeSemaphore& RenderSemaphore, const Native::INativeQueue& PresentationQueue) override;

		virtual void RecreateResources() override;
	private:
		VkSurfaceKHR CreateNativeSurface();
		VkSurfaceCapabilitiesKHR RetrieveNativeSurfaceCapabilities();
		VkSurfaceFormatKHR SelectNativeSurfaceFormat();
		const Elysium::Core::uint32_t RetrieveGraphicsQueueFamilyIndex();
		const Elysium::Core::uint32_t RetrievePresentationQueueFamilyIndex();
		VkDevice CreateNativeLogicalDevice();
		VkSwapchainKHR CreateNativeSwapchain(const VkSwapchainKHR PreviousNativeSwapchainHandle);
		Elysium::Core::Template::Container::Vector<VkImage> RetrieveNativeBackBufferImages();
		Elysium::Core::Template::Container::Vector<VkImageView> CreateNativeBackBufferImageViews();
		VkImage CreateNativeDepthImage();
		VkDeviceMemory CreateNativeDepthImageMemory();
		VkImageView CreateNativeDepthImageView();

		VkPresentModeKHR SelectNativePresentMode();

		void DestroyNativeDepthImageView();
		void DestroyNativeDepthImageMemory();
		void DestroyNativeDepthImage();
		void DestroyNativeBackBufferImageViews();
		void DestroyNativeBackBufferImages();
		void DestroyNativeSwapchain(VkSwapchainKHR NativeSwapchainHandle);
		void DestroyNativeLogicalDevice();
		void DestroyNativeSurface();
	private:
		const GraphicsInstanceVk& _GraphicsInstance;
		const PhysicalDeviceVk& _PhysicalDevice;
		Presentation::Control& _Canvas;
		PresentationParametersVk& _PresentationParameters;

		VkSurfaceKHR _NativeSurfaceHandle;
		VkSurfaceCapabilitiesKHR _NativeSurfaceCapabilities;
		VkSurfaceFormatKHR _SelectedNativeSurfaceFormat;

		const Elysium::Core::uint32_t _GraphicsQueueFamilyIndex;
		const Elysium::Core::uint32_t _PresentationQueueFamilyIndex;
		VkDevice _NativeLogicalDeviceHandle;
		QueueVk _GraphicsQueue;
		QueueVk _PresentationQueue;

		VkSwapchainKHR _NativeSwapchainHandle;
		Elysium::Core::uint32_t _CurrentBackBufferImageIndex;
		Elysium::Core::Template::Container::Vector<VkImage> _BackBufferImages;
		Elysium::Core::Template::Container::Vector<VkImageView> _BackBufferImageViews;
		VkImage _NativeDepthImageHandle;
		VkDeviceMemory _NativeDepthImageMemoryHandle;
		VkImageView _NativeDepthImageViewHandle;

		FenceVk _RenderFence;
		SemaphoreVk _PresentationSemaphore;
		SemaphoreVk _RenderSemaphore;
	};
}
#endif
