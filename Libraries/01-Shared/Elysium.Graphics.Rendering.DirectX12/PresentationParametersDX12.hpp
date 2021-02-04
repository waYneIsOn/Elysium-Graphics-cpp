/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12
#define ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_PRESENTATIONPARAMETERSDX12

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_PRESENTATIONPARAMETERS
#include "../Elysium.Graphics/PresentationParameters.hpp"
#endif

namespace Elysium::Graphics::Rendering::DirectX12
{
	class ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_API PresentationParametersDX12 final : public PresentationParameters
	{
	public:
		PresentationParametersDX12(const Platform::Canvas& Canvas);
		PresentationParametersDX12(const PresentationParametersDX12& Source) = delete;
		PresentationParametersDX12(PresentationParametersDX12&& Right) noexcept = delete;
		virtual ~PresentationParametersDX12();

		PresentationParametersDX12& operator=(const PresentationParametersDX12& Source) = delete;
		PresentationParametersDX12& operator=(PresentationParametersDX12&& Right) noexcept = delete;

		virtual void Bla() override
		{ }
	};
}
#endif
