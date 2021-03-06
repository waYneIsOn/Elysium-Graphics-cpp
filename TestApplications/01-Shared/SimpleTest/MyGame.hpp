#pragma once

#ifndef ELYSIUM_GRAPHICS_GAME
#include "../../../Libraries/01-Shared/Elysium.Graphics/Game.hpp"
#endif

class MyGame final : public Elysium::Graphics::Game
{
public:
	MyGame(Elysium::Graphics::Rendering::INativeGraphicsDevice& GraphicsDevice);
	MyGame(const MyGame& Source) = delete;
	MyGame(MyGame&& Right) noexcept = delete;
	virtual ~MyGame();

	MyGame& operator=(const MyGame& Source) = delete;
	MyGame& operator=(MyGame&& Right) noexcept = delete;
protected:
	virtual void LoadContent() override;
	virtual void Draw(const Elysium::Graphics::GameTime& GameTime) override;
	virtual void Update(const Elysium::Graphics::GameTime& GameTime) override;
private:
	Elysium::Graphics::Rendering::INativeCommandPool* _CommandPool;
	Elysium::Graphics::Rendering::INativeCommandBuffer* _CommandBuffer;

	void RecordClearCommandBuffer();

	void Control_OnSizeChanged(const Elysium::Graphics::Presentation::Control& Sender, const Elysium::Core::int32_t Width, const Elysium::Core::int32_t Height);

};
