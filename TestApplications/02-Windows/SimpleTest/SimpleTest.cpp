#include "../../../Libraries/01-Shared/Elysium.Graphics.Platform.GLFW/GLFWGameWindow.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/GraphicsInstanceDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.DirectX12/PresentationParametersDX12.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/GraphicsInstanceVk.hpp"
#include "../../../Libraries/01-Shared/Elysium.Graphics.Rendering.Vulkan/PresentationParametersVk.hpp"
#include "MyGame.hpp"

using namespace Elysium::Core;
using namespace Elysium::Core::Collections::Template;
using namespace Elysium::Graphics;
using namespace Elysium::Graphics::Platform::GLFW;
using namespace Elysium::Graphics::Rendering;
using namespace Elysium::Graphics::Rendering::DirectX12;
using namespace Elysium::Graphics::Rendering::Vulkan;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // create a canvas
    GLFWGameWindow GameWindow = GLFWGameWindow();
    GameWindow.SetTitle(u8"Elysium Graphics :: GLFWGameWindow :: SimpleTest");
    
    // create and configure presentation parmeters (some further parameters will be picked up along the way)
    PresentationParametersVk PresentationParameters = PresentationParametersVk(GameWindow);
    
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
        if (LayerName == u8"VK_LAYER_KHRONOS_validation")
        {
            PresentationParameters.AddLayerProperty(AvailableLayers[i]);
        }
    }

    // initialize the previously created vulkan instance, create a surface, iterate physical devices and pick one
    GraphicsInstance.Initialize(PresentationParameters);
    GraphicsInstance.EnableDebugging();
    SurfaceVk Surface = GraphicsInstance.CreateSurface(PresentationParameters);

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
        PresentationParameters.AddDeviceExtensionProperty(AvailableDeviceExtensions[i]);
    }

    // check surface against physical device to retrieve required data for swapchain-creation
    SwapchainCreateInfoVk SwapchainCreateInfo = SwapchainCreateInfoVk();

    const SurfaceCapabilitiesVk SurfaceCapabilities = Surface.GetCapabilities(SelectedPhysicalDevice);
    const Array<SurfaceFormatVk> AvailableSurfaceFormats = Surface.GetFormats(SelectedPhysicalDevice);
    const Array<PresentModeVk> AvailablePresentModes = Surface.GetPresentModes(SelectedPhysicalDevice);

    SwapchainCreateInfo.Transform = SurfaceCapabilities.GetCurrentTransform();
    SwapchainCreateInfo.NumberOfImages = 3; // triple buffering?
    if (SwapchainCreateInfo.NumberOfImages > SurfaceCapabilities.GetMaxImageCount())
    {
        SwapchainCreateInfo.NumberOfImages = SurfaceCapabilities.GetMaxImageCount();
    }
    SwapchainCreateInfo.Extend = SurfaceCapabilities.GetMaxImageExtent();

    SwapchainCreateInfo.SurfaceFormat = AvailableSurfaceFormats[0];
    for (size_t i = 0; i < AvailableSurfaceFormats.GetLength(); i++)
    {
        if (AvailableSurfaceFormats[i].Format == FormatVk::B8G8R8A8_SRGB && AvailableSurfaceFormats[i].ColorSpace == ColorSpaceVk::SRGBNonLinear)
        {
            SwapchainCreateInfo.SurfaceFormat = AvailableSurfaceFormats[i];
            break;
        }
    }

    SwapchainCreateInfo.PresentMode = PresentModeVk::Immediate;
    for (size_t i = 0; i < AvailablePresentModes.GetLength(); i++)
    {
        if (AvailablePresentModes[i] == PresentModeVk::Mailbox)
        {
            SwapchainCreateInfo.PresentMode = AvailablePresentModes[i];
            break;
        }
    }

    // check for queue familys to be used (in this case we're looking for graphics capabilities only) and create a logical device as well as queues required
    const Array<QueueFamilyPropertyVk> QueueFamilyProperties = SelectedPhysicalDevice.GetQueueFamilyProperties();
    List<DeviceQueueCreateInfoVk> DeviceQueueCreateInfos = List<DeviceQueueCreateInfoVk>();
    for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
    {
        QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();

        if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
        {
            if (SwapchainCreateInfo.GraphicsFamilyIndex != -1)
            {
                SwapchainCreateInfo.GraphicsFamilyIndex = i;
            }
            if (SwapchainCreateInfo.PresentFamilyIndex != -1)
            {
                if (SelectedPhysicalDevice.SupportsPresentation(Surface, i))
                {
                    SwapchainCreateInfo.PresentFamilyIndex = i;
                }
            }
            DeviceQueueCreateInfoVk DeviceQueueCreateInfo = DeviceQueueCreateInfoVk(QueueFamilyProperties[i].GetIndex(), 1, 1.0f, Capabilities);
            DeviceQueueCreateInfos.Add(std::move(DeviceQueueCreateInfo));
        }
    }
    LogicalDeviceVk LogicalDevice = SelectedPhysicalDevice.CreateLogicalDevice(PresentationParameters, DeviceQueueCreateInfos);

    // swapchain...
    SwapchainVk Swapchain = LogicalDevice.CreateSwapchain(Surface, SwapchainCreateInfo);

    // ...
    //QueueVk& GraphicsQueue = LogicalDevice.RetrieveQueue(GraphicsFamilyIndex, 0);
    //QueueVk& PresentationQueue = LogicalDevice.RetrieveQueue(PresentationFamilyIndex, 0);


    /*
    // create and configure presentation parmeters
    PresentationParametersDX12 PresentationParameters = PresentationParametersDX12(GameWindow);

    // create a directx12 instance and ...
    GraphicsInstanceDX12 GraphicsInstance = GraphicsInstanceDX12();

    // initialize the previously created directx12 instance, .... iterate physical devices and pick one
    GraphicsInstance.Initialize(PresentationParameters);
    const Array<PhysicalDeviceDX12> PhysicalGraphicsDevices = GraphicsInstance.GetPhysicalGraphicsDevices();
    for (size_t i = 0; i < PhysicalGraphicsDevices.GetLength(); i++)
    {
        const String DeviceName = PhysicalGraphicsDevices[i].GetName();
    }
    PhysicalDeviceDX12& SelectedPhysicalDevice = PhysicalGraphicsDevices[0];
    
    // ...
    //LogicalDeviceDX12 LogicalDevice = SelectedPhysicalDevice.CreateLogicalDevice(PresentationParameters);
    */


    const String DeviceName = SelectedPhysicalDevice.GetName();
    //SelectedPhysicalDevice.CreateLogicalDevice(PresentationParameters, DeviceQueueCreateInfos());



    // create and run the game
    MyGame Game = MyGame(GameWindow, SelectedPhysicalDevice);
    Game.Run();
}
