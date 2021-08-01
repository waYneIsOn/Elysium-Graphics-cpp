#include "Queue.hpp"

Elysium::Graphics::Rendering::Queue::~Queue()
{ }

void Elysium::Graphics::Rendering::Queue::Wait() const
{
	_NativeQueue.Wait();
}

Elysium::Graphics::Rendering::Queue::Queue(INativeQueue& NativeQueue)
	: _NativeQueue(NativeQueue)
{ }

Elysium::Graphics::Rendering::CommandPool Elysium::Graphics::Rendering::Queue::CreateCommandPool()
{
	return CommandPool(_NativeQueue.CreateCommandPool());
}

void Elysium::Graphics::Rendering::Queue::Submit(const CommandBuffer& CommmandBuffer, const Semaphore& PresentSemaphore, const Semaphore& RenderSemaphore, const Fence& Fence)
{
	_NativeQueue.Submit(*CommmandBuffer._NativeCommandBuffer, PresentSemaphore._NativeSemaphore, RenderSemaphore._NativeSemaphore, Fence._NativeFence);
}
