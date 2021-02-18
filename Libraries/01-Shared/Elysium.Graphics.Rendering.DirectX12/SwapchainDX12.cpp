#include "SwapchainDX12.hpp"

#ifndef ELYSIUM_GRAPHICS_RENDERING_DIRECTX12_EXCEPTIONDX12
#include "ExceptionDX12.hpp"
#endif

Elysium::Graphics::Rendering::DirectX12::SwapchainDX12::SwapchainDX12(const LogicalDeviceDX12& LogicalDevice, const QueueDX12& DirectQueue)
	: _LogicalDevice(LogicalDevice), _DirectQueue(DirectQueue), _NativeSwapchain(nullptr)
{
	const PresentationParametersDX12& DX12PresentationParameters = static_cast<const PresentationParametersDX12&>(LogicalDevice.GetPresentationParameters());
	Elysium::Graphics::Platform::Canvas& Canvas = DX12PresentationParameters.GetCanvas();
	const Elysium::Core::Math::Geometry::Rectangle& ClientBounds = Canvas.GetClientBounds();
	
	DXGI_SWAP_CHAIN_DESC CreateInfo = DXGI_SWAP_CHAIN_DESC();
	CreateInfo.BufferCount = DX12PresentationParameters.GetBackBufferCount();
	CreateInfo.BufferDesc.Width = ClientBounds.Width;
	CreateInfo.BufferDesc.Height = ClientBounds.Height;
	//CreateInfo.BufferDesc.RefreshRate.Denominator = 0;
	//CreateInfo.BufferDesc.RefreshRate.Numerator = 0;
	//CreateInfo.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;
	//CreateInfo.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_CENTERED;
	//CreateInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//CreateInfo.BufferUsage = 0;
	//CreateInfo.Flags = 0;
	CreateInfo.OutputWindow = (HWND)DX12PresentationParameters.GetCanvas().GetHandle();
	//CreateInfo.SampleDesc.Count = 0;
	//CreateInfo.SampleDesc.Quality = 0;
	//CreateInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_SEQUENTIAL;
	//CreateInfo.Windowed = true;
	
	long Result;
	if (FAILED(Result = _LogicalDevice._Factory->CreateSwapChain(_DirectQueue._NativeQueue, &CreateInfo, &_NativeSwapchain)))
	{
		throw ExceptionDX12(Result);
	}
}
Elysium::Graphics::Rendering::DirectX12::SwapchainDX12::~SwapchainDX12()
{
	if (_NativeSwapchain != nullptr)
	{
		_NativeSwapchain->Release();
		_NativeSwapchain = nullptr;
	}
}

const Elysium::Core::uint32_t Elysium::Graphics::Rendering::DirectX12::SwapchainDX12::GetBackBufferImageCount() const
{
	throw 1;
}

void Elysium::Graphics::Rendering::DirectX12::SwapchainDX12::Recreate()
{
	throw 1;
}

void Elysium::Graphics::Rendering::DirectX12::SwapchainDX12::AquireNextImage(const INativeSemaphore& PresentSemaphore, const Elysium::Core::uint64_t Timeout)
{
	throw 1;
}

void Elysium::Graphics::Rendering::DirectX12::SwapchainDX12::PresentFrame(const INativeSemaphore& RenderSemaphore, const INativeQueue& PresentationQueue)
{
	/*
	Elysium::Core::uint32_t SyncInterval = 0;
	Elysium::Core::uint32_t Flags = 0;

	long Result;
	if (FAILED(Result = _NativeSwapchain->Present(SyncInterval, Flags)))
	{
		throw ExceptionDX12(Result);
	}
	*/
	throw 1;
}
