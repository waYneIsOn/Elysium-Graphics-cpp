/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_GRAPHICS_RENDERING_RASTERIZERSTATE
#define ELYSIUM_GRAPHICS_RENDERING_RASTERIZERSTATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_GRAPHICS_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_CULLMODE
#include "CullMode.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_RENDERING_FILLMODE
#include "FillMode.hpp"
#endif

namespace Elysium::Graphics::Rendering
{
	class ELYSIUM_GRAPHICS_API RasterizerState final
	{
	public:
		RasterizerState();
		RasterizerState(const RasterizerState& Source) = delete;
		RasterizerState(RasterizerState&& Right) noexcept = delete;
		~RasterizerState();

		RasterizerState& operator=(const RasterizerState& Source) = delete;
		RasterizerState& operator=(RasterizerState&& Right) noexcept = delete;

		const CullMode GetCullMode() const;
		const FillMode GetFillMode() const;
		const float GetLineWidth() const;

		void SetCullMode(const CullMode Value);
		void SetFillMode(const FillMode Value);
		void SetLineWidth(const float Value);
	private:
		CullMode _CullMode = CullMode::None;
		FillMode _FillMode = FillMode::Fill;
		float _LineWidth = 1.0f;
	};
}
#endif
