/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE
#define ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSDEVICE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_COLLECTIONS_TEMPLATE_ARRAYOFBYTE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/ArrayOfByte.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_PRESENTATIONPARAMETERS
#include "PresentationParameters.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFENCE
#include "INativeFence.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEFRAMEBUFFER
#include "INativeFramebuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSPIPELINE
#include "INativeGraphicsPipeline.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEGRAPHICSAPI
#include "INativeGraphicsAPI.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEINDEXBUFFER
#include "INativeIndexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEPHYSICALDEVICE
#include "INativePhysicalDevice.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEQUEUE
#include "INativeQueue.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVERENDERPASS
#include "INativeRenderPass.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVESEMAPHORE
#include "INativeSemaphore.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_NATIVE_INATIVEVERTEXBUFFER
#include "INativeVertexBuffer.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_SURFACEFORMAT
#include "SurfaceFormat.hpp"
#endif

namespace Elysium::Graphics::Rendering::Native
{
	class ELYSIUM_GRAPHICS_API INativeGraphicsDevice
	{
	public:
		virtual ~INativeGraphicsDevice() { }
		
		virtual const PresentationParameters& GetPresentationParameters() const = 0;

		virtual const SurfaceFormat GetBackBufferFormat() const = 0;

		virtual const INativeFence& GetRenderFence() const = 0;
		virtual const INativeSemaphore& GetPresentationSemaphore() const = 0;
		virtual const INativeSemaphore& GetRenderSemaphore() const = 0;

		virtual INativeQueue& GetGraphicsQueue() = 0;
		virtual INativeQueue& GetPresentationQueue() = 0;

		virtual INativeRenderPass* CreateRenderPass(const SurfaceFormat SurfaceFormat) = 0;
		virtual INativeFrameBuffer* CreateFrameBuffer(const INativeRenderPass& RenderPass) = 0;
		virtual INativeGraphicsPipeline* CreateGraphicsPipeline() = 0;

		virtual INativeVertexBuffer* CreateVertexBuffer(const VertexDeclaration& Declaration, const Elysium::Core::uint32_t VertexCount, const BufferUsage Usage) = 0;
		virtual INativeIndexBuffer* CreateIndexBuffer(const IndexElementSize ElementSize, const Elysium::Core::uint32_t IndexCount, const BufferUsage Usage) = 0;
		virtual INativeShaderModule* CreateShaderModule(const Elysium::Core::Collections::Template::Array<Elysium::Core::byte>& ByteCode) = 0;

		virtual void Wait() const = 0;
		virtual const bool BeginDraw(INativeFence& RenderFence, const INativeSemaphore& PresentationSemaphore) = 0;
		virtual void EndDraw(const INativeSemaphore& RenderSemaphore, const INativeQueue& PresentationQueue) = 0;

		virtual void RecreateResources() = 0;
	};
}
#endif
