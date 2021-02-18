#include "MyGame.hpp"

MyGame::MyGame(Elysium::Graphics::Rendering::INativeLogicalDevice& LogicalDevice, Elysium::Graphics::Rendering::INativeSwapchain& Swapchain,
	Elysium::Graphics::Rendering::INativeQueue& PresentationQueue, Elysium::Graphics::Rendering::INativeQueue& GraphicsQueue,
	Elysium::Graphics::Rendering::INativeFence& RenderFence, Elysium::Graphics::Rendering::INativeSemaphore& PresentSemaphore,
	Elysium::Graphics::Rendering::INativeSemaphore& RenderSemaphore)
	: Elysium::Graphics::Game(LogicalDevice, Swapchain, PresentationQueue, GraphicsQueue, RenderFence, PresentSemaphore, RenderSemaphore)
{ }
MyGame::~MyGame()
{ }

void MyGame::LoadContent()
{
}

void MyGame::Draw(const Elysium::Graphics::GameTime& GameTime)
{
}

void MyGame::Update(const Elysium::Graphics::GameTime& GameTime)
{
}
