#pragma once

#ifndef ELYSIUM_GRAPHICS_GAME
#include "../../../Libraries/01-Shared/Elysium.Graphics/Game.hpp"
#endif

class MyGame final : public Elysium::Graphics::Game
{
public:
	MyGame(Elysium::Graphics::Rendering::INativeGraphicsDevice& GraphicsDevice, 
		Elysium::Graphics::Rendering::INativeLogicalDevice& LogicalDevice, Elysium::Graphics::Rendering::INativeSwapchain& Swapchain,
		Elysium::Graphics::Rendering::INativeQueue& PresentationQueue, Elysium::Graphics::Rendering::INativeQueue& GraphicsQueue,
		Elysium::Graphics::Rendering::INativeFence& RenderFence, Elysium::Graphics::Rendering::INativeSemaphore& PresentSemaphore,
		Elysium::Graphics::Rendering::INativeSemaphore& RenderSemaphore);
	MyGame(const MyGame& Source) = delete;
	MyGame(MyGame&& Right) noexcept = delete;
	virtual ~MyGame();

	MyGame& operator=(const MyGame& Source) = delete;
	MyGame& operator=(MyGame&& Right) noexcept = delete;
protected:
	virtual void LoadContent() override;
	virtual void Draw(const Elysium::Graphics::GameTime& GameTime) override;
	virtual void Update(const Elysium::Graphics::GameTime& GameTime) override;
};
