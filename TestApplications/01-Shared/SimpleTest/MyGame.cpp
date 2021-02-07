#include "MyGame.hpp"

MyGame::MyGame(Elysium::Graphics::Rendering::PresentationParameters& PresentationParameter, Elysium::Graphics::Rendering::INativePhysicalDevice& PhysicalDevice,
	Elysium::Graphics::Rendering::INativeLogicalDevice& LogicalDevice, Elysium::Graphics::Rendering::INativeSwapchain& Swapchain,
	Elysium::Graphics::Rendering::INativeFence& Fence, Elysium::Graphics::Rendering::INativeSemaphore& ImageAvailableSemaphore,
	Elysium::Graphics::Rendering::INativeSemaphore& WaitSemaphore, Elysium::Graphics::Rendering::INativeQueue& PresentationQueue)
	: Elysium::Graphics::Game(PresentationParameter, PhysicalDevice, LogicalDevice, Swapchain, Fence, ImageAvailableSemaphore, WaitSemaphore, PresentationQueue)
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
