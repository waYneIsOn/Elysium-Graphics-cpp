#include "../../../Libraries/01-Shared/Elysium.Graphics.Platform.GLFW/GLFWGameWindow.hpp"
//#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/GraphicsInstanceDX12.hpp"
//#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/PresentationParametersDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/GraphicsInstanceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/LogicalDeviceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/PresentationParametersVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/QueueVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/SwapchainVk.hpp"
#include "../../01-Shared/SimpleTest/MyGame.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Graphics;
using namespace Elysium::Graphics::Platform::GLFW;
using namespace Elysium::Graphics::Rendering;
using namespace Elysium::Graphics::Rendering::Vulkan;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // create a canvas
    GLFWGameWindow GameWindow = GLFWGameWindow();
    GameWindow.SetTitle(u8"Elysium Graphics :: GLFWGameWindow :: SimpleTest");
    
    // create and configure presentation parmeters (further parameters will be picked up and set along the way)
    PresentationParametersVk PresentationParameters = PresentationParametersVk(GameWindow);
    PresentationParameters.SetBackBufferWidth(GraphicsDeviceManager::DefaultBackBufferWidth);
    PresentationParameters.SetBackBufferHeight(GraphicsDeviceManager::DefaultBackBufferHeight);
    PresentationParameters.SetBackBufferCount(GraphicsDeviceManager::DefaultBackBufferCount);
    
    // create a vulkan instance and check for extensions and layers to be used
    GraphicsInstanceVk GraphicsInstance = GraphicsInstanceVk();

    const Array<ExtensionPropertyVk> AvailableInstanceExtensions = GraphicsInstance.GetAvailableExtensions();
    for (size_t i = 0; i < AvailableInstanceExtensions.GetLength(); i++)
    {
        const StringView ExtensionName = AvailableInstanceExtensions[i].GetName();
        PresentationParameters.AddInstanceExtensionProperty(AvailableInstanceExtensions[i]);
    }

    const Array<LayerPropertyVk> AvailableLayers = GraphicsInstance.GetAvailableLayers();
    for (size_t i = 0; i < AvailableLayers.GetLength(); i++)
    {
        const StringView LayerName = AvailableLayers[i].GetName();
        //if (LayerName == u8"VK_LAYER_KHRONOS_validation")
        {
            PresentationParameters.AddLayerProperty(AvailableLayers[i]);
        }
    }

    // initialize the previously created vulkan instance, create a surface, iterate physical devices and pick one
    GraphicsInstance.Initialize(PresentationParameters);
    //GraphicsInstance.EnableDebugging();

    SurfaceVk Surface = GraphicsInstance.CreateSurface(PresentationParameters);
    PresentationParameters.SetSurfaceHandle(Surface);

    const Array<PhysicalDeviceVk> PhysicalGraphicsDevices = GraphicsInstance.GetPhysicalGraphicsDevices();
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
    /*
    // create and configure presentation parmeters
    PresentationParametersDX12 PresentationParameters = PresentationParametersDX12(GameWindow);
    PresentationParameters.SetBackBufferWidth(GraphicsDeviceManager::DefaultBackBufferWidth);
    PresentationParameters.SetBackBufferHeight(GraphicsDeviceManager::DefaultBackBufferHeight);
    PresentationParameters.SetBackBufferCount(GraphicsDeviceManager::DefaultBackBufferCount);

    // create a directx12 instance and ...
    GraphicsInstanceDX12 GraphicsInstance = GraphicsInstanceDX12();

    // initialize the previously created directx12 instance, .... iterate physical devices and pick one
    GraphicsInstance.Initialize(PresentationParameters);
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

    LogicalDeviceDX12 LogicalDevice = SelectedPhysicalDevice.CreateLogicalDevice(PresentationParameters);

    // create a directx12 swapchain
    SwapchainDX12 Swapchain = LogicalDevice.CreateSwapchain(PresentationParameters);
    */




    // ...
    LogicalDeviceVk LogicalDevice = LogicalDeviceVk(SelectedPhysicalDevice, PresentationParameters);
    SwapchainVk Swapchain = SwapchainVk(LogicalDevice);
    QueueVk GraphicsQueue = QueueVk(LogicalDevice, PresentationParameters.GetGraphicsQueueFamilyIndex(), 0);
    QueueVk PresentationQueue = QueueVk(LogicalDevice, PresentationParameters.GetPresentationQueueFamilyIndex(), 0);
    //QueueVk InadequateQueue = QueueVk(LogicalDevice, 1337, 5448);




    // create and run the game
    MyGame Game = MyGame(LogicalDevice, Swapchain, PresentationQueue);
    Game.Run();
}
