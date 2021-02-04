#pragma once

#ifndef ELYSIUM_GRAPHICS_GAME
#include "../../../Libraries/01-Shared/Elysium.Graphics/Game.hpp"
#endif

class MyGame final : public Elysium::Graphics::Game
{
public:
	MyGame(Elysium::Graphics::Platform::Canvas& Canvas, Elysium::Graphics::Rendering::IPhysicalDevice& PhysicalDevice);
	MyGame(const MyGame& Source) = delete;
	MyGame(MyGame&& Right) noexcept = delete;
	virtual ~MyGame();

	MyGame& operator=(const MyGame& Source) = delete;
	MyGame& operator=(MyGame&& Right) noexcept = delete;
protected:
	virtual void Draw(const Elysium::Graphics::GameTime& GameTime) override;
	virtual void Update(const Elysium::Graphics::GameTime& GameTime) override;
};

