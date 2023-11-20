#include "../../01-Shared/SimpleTest/MyGame.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Presentation/DisplayDevice.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Presentation/Window.hpp"
/*
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/FenceDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/GraphicsInstanceDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/LogicalDeviceDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/PhysicalDeviceDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/PresentationParametersDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/QueueDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/SwapchainDX12.hpp"
*/
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/CommandBufferVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/CommandPoolVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/FenceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/GraphicsInstanceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/GraphicsDeviceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/PresentationParametersVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/QueueVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/RenderPassVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/SemaphoreVk.hpp"

#include "../../../Libraries/01-Shared/Elysium.Graphics/GraphicsDevice.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Template::Container;
using namespace Elysium::Graphics;
using namespace Elysium::Graphics::Presentation;
using namespace Elysium::Graphics::Rendering;
//using namespace Elysium::Graphics::Rendering::DirectX12;
using namespace Elysium::Graphics::Rendering::Vulkan;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // instantiate a window to be used as canvas and find the primary display device index
    Window Canvas = Window();
    const Vector<DisplayDevice>& DisplayDevices = DisplayDevice::GetActiveDisplayDevices();
    size_t PrimaryDisplayDeviceIndex = -1;
    for (size_t i = 0; i < DisplayDevices.GetLength(); i++)
    {
        if (DisplayDevices[i].GetIsPrimaryDisplayDevice())
        {
            PrimaryDisplayDeviceIndex = i;
            break;
        }
    }

    // instantiate and prepare vulkan
    GraphicsInstanceVk GraphicsAPI = GraphicsInstanceVk();
    GraphicsAPI.EnableDebugging();

    const Elysium::Core::Template::Container::Vector<ExtensionPropertyVk> AvailableInstanceExtensions = GraphicsAPI.GetAvailableExtensions();
    const Elysium::Core::Template::Container::Vector<LayerPropertyVk> AvailableLayers = GraphicsAPI.GetAvailableLayers();

    // get the most suitable graphics device
    const Elysium::Core::Template::Container::Vector<PhysicalDeviceVk>& PhysicalGraphicsDevices = GraphicsAPI.GetPhysicalDevices();
    size_t MostSuitablePhysicalDeviceIndex = -1;
    size_t HighestScore = 0;
    for (size_t i = 0; i < PhysicalGraphicsDevices.GetLength(); i++)
    {
        const PhysicalDevicePropertiesVk& Properties = PhysicalGraphicsDevices[i].GetProperties();
        const PhysicalDeviceFeaturesVk& Features = PhysicalGraphicsDevices[i].GetFeatures();

        size_t Score = 0;
        if (Properties.GetPhysicalGraphicsDeviceType() == PhysicalDeviceType::DiscreteGPU)
        {
            Score += 1000;
        }
        Score += Properties.GetMaxImageDimension2D();

        if (!Features.GetGeometryShader())
        {
            Score = 0;
        }

        if (Score > HighestScore)
        {
            HighestScore = Score;
            MostSuitablePhysicalDeviceIndex = i;
        }
    }
    
    // create and configure presentation parameters (further values will set along the way)
    PresentationParametersVk PresentationParameters = PresentationParametersVk(GraphicsAPI, Canvas);
    PresentationParameters.SetBackBufferWidth(GraphicsDeviceManager::DefaultBackBufferWidth);
    PresentationParameters.SetBackBufferHeight(GraphicsDeviceManager::DefaultBackBufferHeight);
    PresentationParameters.SetBackBufferCount(GraphicsDeviceManager::DefaultBackBufferCount);
    PresentationParameters.SetDisplayMode(DisplayMode::Windowed);
    PresentationParameters.SetDisplayDeviceIndex(PrimaryDisplayDeviceIndex);
    PresentationParameters.SetGraphicsDeviceIndex(MostSuitablePhysicalDeviceIndex);
    //PresentationParameters.SetPresentMode(PresentMode::Immediate);
    //PresentationParameters.SetRenderResolution(20);
    PresentationParameters.SetRenderResolution(150);

    // ...
    const PhysicalDeviceVk& SelectedPhysicalDevice = PhysicalGraphicsDevices[MostSuitablePhysicalDeviceIndex];

    const Elysium::Core::Template::Container::Vector<ExtensionPropertyVk> AvailableDeviceExtensions = SelectedPhysicalDevice.GetAvailableExtensions();
    for (size_t i = 0; i < AvailableDeviceExtensions.GetLength(); i++)
    {
        const Utf8StringView ExtensionName = AvailableDeviceExtensions[i].GetName();
        if (ExtensionName != u8"VK_EXT_buffer_device_address")
        {
            PresentationParameters.AddDeviceExtensionProperty(AvailableDeviceExtensions[i]);
        }
    }

    // ...
    GraphicsDeviceVk GraphicsDeviceVulkan = GraphicsDeviceVk(GraphicsAPI, SelectedPhysicalDevice, PresentationParameters);
    GraphicsDevice WrappedGraphicsDevice = GraphicsDevice(GraphicsDeviceVulkan);

    // create and run the game
    MyGame Game = MyGame(WrappedGraphicsDevice);
    Game.Run();

    /*
    // create and configure presentation parmeters (further parameters will be picked up and set along the way)
    PresentationParametersDX12 PresentationParameters = PresentationParametersDX12();
    PresentationParameters.SetBackBufferWidth(GraphicsDeviceManager::DefaultBackBufferWidth);
    PresentationParameters.SetBackBufferHeight(GraphicsDeviceManager::DefaultBackBufferHeight);
    PresentationParameters.SetBackBufferCount(GraphicsDeviceManager::DefaultBackBufferCount);

    // create a directx12 instance and ...
    GraphicsInstanceDX12 GraphicsInstance = GraphicsInstanceDX12();

    // initialize the previously created vulkan instance, create a surface, iterate physical devices and pick one
    GraphicsInstance.Initialize(PresentationParameters);
    GraphicsInstance.EnableDebugging();

    //SurfaceDX12 Surface = GraphicsInstance.CreateSurface(PresentationParameters);
    //PresentationParameters.SetSurfaceHandle(Surface);

    const Elysium::Core::Template::Container::Vector<PhysicalDeviceDX12> PhysicalGraphicsDevices = GraphicsInstance.GetPhysicalGraphicsDevices();
    size_t MostSuitableGraphicsDeviceIndex = -1;
    size_t HighestScore = 0;
    for (size_t i = 0; i < PhysicalGraphicsDevices.GetLength(); i++)
    {
        const String DeviceName = PhysicalGraphicsDevices[i].GetName();

        size_t Score = 0;
        Score += PhysicalGraphicsDevices[i].GetDedicatedSystemMemory();
        Score += PhysicalGraphicsDevices[i].GetDedicatedVideoMemory();
        Score += PhysicalGraphicsDevices[i].GetSharedSystemMemory();

        if (Score > HighestScore)
        {
            HighestScore = Score;
            MostSuitableGraphicsDeviceIndex = i;
        }
    }
    PhysicalDeviceDX12& SelectedPhysicalDevice = PhysicalGraphicsDevices[MostSuitableGraphicsDeviceIndex];
    
    // create a logical device as well as queues required
    DeviceQueueCreateInfoDX12 GraphicsQueueCreateInfo = DeviceQueueCreateInfoDX12();
    GraphicsQueueCreateInfo.SetNodeMask(0);
    GraphicsQueueCreateInfo.SetFlags(CommandQueueFlagsDX12::None);
    GraphicsQueueCreateInfo.SetPriority(CommandQueuePriorityDX12::Normal);
    GraphicsQueueCreateInfo.SetType(CommandQueueTypeDX12::Direct);

    PresentationParameters.AddDeviceQueueCreateInfo(Elysium::Core::Template::Functional::Move(GraphicsQueueCreateInfo));

    // ...
    LogicalDeviceDX12 LogicalDevice = LogicalDeviceDX12(SelectedPhysicalDevice, PresentationParameters);
    QueueDX12 PresentationQueue = QueueDX12(LogicalDevice, CommandQueueTypeDX12::Direct, 0);
    QueueDX12 GraphicsQueue = QueueDX12(LogicalDevice, CommandQueueTypeDX12::Direct, 0);
    SwapchainDX12 Swapchain = SwapchainDX12(LogicalDevice, PresentationQueue);

    FenceDX12 RenderFence = FenceDX12(LogicalDevice, true);
    //SemaphoreDX12 PresentSemaphore = SemaphoreDX12(LogicalDevice);
    //SemaphoreDX12 RenderSemaphore = SemaphoreDX12(LogicalDevice);
    */




}
