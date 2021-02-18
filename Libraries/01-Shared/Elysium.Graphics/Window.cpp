#include "Window.hpp"

Elysium::Graphics::Platform::Window::Window()
{
	ActivationChanged += Elysium::Core::Delegate<void, const void*, const bool>::CreateDelegate<Elysium::Graphics::Platform::Window, &Elysium::Graphics::Platform::Window::OnActivationChanged>(*this);
}
Elysium::Graphics::Platform::Window::~Window()
{
	ActivationChanged -= Elysium::Core::Delegate<void, const void*, const bool>::CreateDelegate<Elysium::Graphics::Platform::Window, &Elysium::Graphics::Platform::Window::OnActivationChanged>(*this);
}

void Elysium::Graphics::Platform::Window::Show()
{
	throw 1;
}

void Elysium::Graphics::Platform::Window::Close()
{
	throw 1;
}

void Elysium::Graphics::Platform::Window::OnActivationChanged(const void* Sender, const bool HasActived)
{
	throw 1;
}
