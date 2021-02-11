#include "MyGame.hpp"

MyGame::MyGame(Elysium::Graphics::Rendering::INativeLogicalDevice& LogicalDevice, Elysium::Graphics::Rendering::INativeSwapchain& Swapchain,
	Elysium::Graphics::Rendering::INativeQueue& PresentationQueue)
	: Elysium::Graphics::Game(LogicalDevice, Swapchain, PresentationQueue)
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
