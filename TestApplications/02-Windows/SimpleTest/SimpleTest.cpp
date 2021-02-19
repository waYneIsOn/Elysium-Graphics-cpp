#include "../../01-Shared/SimpleTest/MyGame.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Presentation/Monitor.hpp"
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
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/LogicalDeviceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/PresentationParametersVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/QueueVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/SemaphoreVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/SwapchainVk.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Graphics;
using namespace Elysium::Graphics::Presentation;
using namespace Elysium::Graphics::Rendering;
//using namespace Elysium::Graphics::Rendering::DirectX12;
using namespace Elysium::Graphics::Rendering::Vulkan;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 01 - instantiate a window to be used as canvas
    Window Canvas = Window();

    // 02 - instantiate and prepare vulkan api
    GraphicsInstanceVk GraphicsAPI = GraphicsInstanceVk();
    const Array<ExtensionPropertyVk> AvailableInstanceExtensions = GraphicsAPI.GetAvailableExtensions();
    for (size_t i = 0; i < AvailableInstanceExtensions.GetLength(); i++)
    {
        const StringView ExtensionName = AvailableInstanceExtensions[i].GetName();
        GraphicsAPI.AddInstanceExtensionProperty(AvailableInstanceExtensions[i]);
    }

    const Array<LayerPropertyVk> AvailableLayers = GraphicsAPI.GetAvailableLayers();
    for (size_t i = 0; i < AvailableLayers.GetLength(); i++)
    {
        const StringView LayerName = AvailableLayers[i].GetName();
        GraphicsAPI.AddLayerProperty(AvailableLayers[i]);
    }

    GraphicsAPI.Initialize();
    GraphicsAPI.EnableDebugging();

    Array<PhysicalDeviceVk> PhysicalGraphicsDevices = GraphicsAPI.GetPhysicalGraphicsDevices();
    size_t MostSuitableGraphicsDeviceIndex = -1;
    size_t HighestScore = 0;
    for (size_t i = 0; i < PhysicalGraphicsDevices.GetLength(); i++)
    {
        const PhysicalDevicePropertiesVk& Properties = PhysicalGraphicsDevices[i].GetProperties();
        const PhysicalDeviceFeaturesVk& Features = PhysicalGraphicsDevices[i].GetFeatures();

        size_t Score = 0;
        if (Properties.GetPhysicalGraphicsDeviceType() == PhysicalDeviceTypeVk::DiscreteGPU)
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
            MostSuitableGraphicsDeviceIndex = i;
        }
    }

    // 03 - create and configure presentation parameters (further values will set along the way)
    PresentationParametersVk PresentationParameters = PresentationParametersVk(GraphicsAPI, Canvas);
    PresentationParameters.SetBackBufferWidth(GraphicsDeviceManager::DefaultBackBufferWidth);
    PresentationParameters.SetBackBufferHeight(GraphicsDeviceManager::DefaultBackBufferHeight);
    PresentationParameters.SetBackBufferCount(GraphicsDeviceManager::DefaultBackBufferCount);
    PresentationParameters.SetDisplayMode(DisplayMode::Windowed);
    PresentationParameters.SetDisplayMonitorIndex(0);
    PresentationParameters.SetDisplayDeviceIndex(MostSuitableGraphicsDeviceIndex);

    // ... - prepare vulkan specific presentation parameters
    //PresentationParameters.SetSurfaceFormat(...);

    // ... - iterate physical devices and select one
    PhysicalDeviceVk& SelectedPhysicalDevice = PhysicalGraphicsDevices[MostSuitableGraphicsDeviceIndex];

    const Array<ExtensionPropertyVk> AvailableDeviceExtensions = SelectedPhysicalDevice.GetAvailableExtensions();
    for (size_t i = 0; i < AvailableDeviceExtensions.GetLength(); i++)
    {
        const StringView ExtensionName = AvailableDeviceExtensions[i].GetName();
        if (ExtensionName != u8"VK_EXT_buffer_device_address")
        {
            PresentationParameters.AddDeviceExtensionProperty(AvailableDeviceExtensions[i]);
        }
    }

    // ...
    GraphicsDeviceVk GraphicsDevice = GraphicsDeviceVk(GraphicsAPI, PresentationParameters);













    // ... initialize the previously created vulkan instance, create a surface, iterate physical devices and pick one
    SurfaceVk Surface = SurfaceVk(GraphicsAPI, PresentationParameters);
    PresentationParameters.SetSurfaceHandle(Surface);

    // check surface against physical device to retrieve required data for swapchain-creation
    const SurfaceCapabilitiesVk SurfaceCapabilities = Surface.GetCapabilities(SelectedPhysicalDevice);
    const Array<SurfaceFormatVk> AvailableSurfaceFormats = Surface.GetFormats(SelectedPhysicalDevice);
    const Array<PresentModeVk> AvailablePresentModes = Surface.GetPresentModes(SelectedPhysicalDevice);

    PresentationParameters.SetTransform(SurfaceCapabilities.GetCurrentTransform());
    if (PresentationParameters.GetBackBufferCount() > SurfaceCapabilities.GetMaxImageCount())
    {
        PresentationParameters.SetBackBufferCount(SurfaceCapabilities.GetMaxImageCount());
    }
    PresentationParameters.SetExtent(SurfaceCapabilities.GetMaxImageExtent().Width, SurfaceCapabilities.GetMaxImageExtent().Height);

    PresentationParameters.SetSurfaceFormat(AvailableSurfaceFormats[0]);
    for (size_t i = 0; i < AvailableSurfaceFormats.GetLength(); i++)
    {
        if (AvailableSurfaceFormats[i].Format == FormatVk::B8G8R8A8_SRGB && AvailableSurfaceFormats[i].ColorSpace == ColorSpaceVk::SRGBNonLinear)
        {
            PresentationParameters.SetSurfaceFormat(AvailableSurfaceFormats[i]);
            break;
        }
    }

    PresentationParameters.SetPresentMode(PresentModeVk::Immediate);
    for (size_t i = 0; i < AvailablePresentModes.GetLength(); i++)
    {
        if (AvailablePresentModes[i] == PresentModeVk::Mailbox)
        {
            PresentationParameters.SetPresentMode(AvailablePresentModes[i]);
            break;
        }
    }

    // check for queue familys to be used (in this case we're looking for graphics capabilities only) and create a logical device as well as queues required
    const Array<QueueFamilyPropertyVk> QueueFamilyProperties = SelectedPhysicalDevice.GetQueueFamilyProperties();
    for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
    {
        QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();

        if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
        {
            if (PresentationParameters.GetGraphicsQueueFamilyIndex() == -1)
            {
                PresentationParameters.SetGraphicsQueueFamilyIndex(i);
            }
            if (PresentationParameters.GetPresentationQueueFamilyIndex() == -1)
            {
                if (SelectedPhysicalDevice.SupportsPresentation(Surface, i))
                {
                    PresentationParameters.SetPresentationQueueFamilyIndex(i);
                }
            }
            
            DeviceQueueCreateInfoVk QueueCreateInfo = DeviceQueueCreateInfoVk();
            QueueCreateInfo.SetFamilyIndex(QueueFamilyProperties[i].GetIndex());
            QueueCreateInfo.AddPriority(1.0f);
            QueueCreateInfo.SetCapabilities(Capabilities);

            PresentationParameters.AddDeviceQueueCreateInfo(std::move(QueueCreateInfo));
        }
    }

    // ...
    LogicalDeviceVk LogicalDevice = LogicalDeviceVk(SelectedPhysicalDevice, PresentationParameters);
    SwapchainVk Swapchain = SwapchainVk(LogicalDevice);
    QueueVk PresentationQueue = QueueVk(LogicalDevice, PresentationParameters.GetPresentationQueueFamilyIndex(), 0);
    QueueVk GraphicsQueue = QueueVk(LogicalDevice, PresentationParameters.GetGraphicsQueueFamilyIndex(), 0);

    FenceVk RenderFence = FenceVk(LogicalDevice, true);
    SemaphoreVk PresentSemaphore = SemaphoreVk(LogicalDevice);
    SemaphoreVk RenderSemaphore = SemaphoreVk(LogicalDevice);

    CommandPoolVk GraphicsPool = CommandPoolVk(LogicalDevice, GraphicsQueue);
    CommandBufferVk PrimaryGraphicsBuffer = CommandBufferVk(GraphicsPool, true);

    // create and run the game
    MyGame Game = MyGame(GraphicsDevice, LogicalDevice, Swapchain, PresentationQueue, GraphicsQueue, RenderFence, PresentSemaphore, RenderSemaphore);
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

    const Array<PhysicalDeviceDX12> PhysicalGraphicsDevices = GraphicsInstance.GetPhysicalGraphicsDevices();
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

    PresentationParameters.AddDeviceQueueCreateInfo(std::move(GraphicsQueueCreateInfo));

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
