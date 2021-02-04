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
    /*
    // create and configure presentation parmeters
    PresentationParametersVk PresentationParameters = PresentationParametersVk(GameWindow);

    // create a vulkan instance and check for extensions and layers to be used
    GraphicsInstanceVk GraphicsInstance = GraphicsInstanceVk();

    const Array<ExtensionPropertyVk> AvailableExtensions = GraphicsInstance.GetAvailableExtensions();
    for (size_t i = 0; i < AvailableExtensions.GetLength(); i++)
    {
        const StringView ExtensionName = AvailableExtensions[i].GetName();
        PresentationParameters.AddExtensionProperty(AvailableExtensions[i]);
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
    SurfaceVk Surface = GraphicsInstance.CreateSurface(PresentationParameters);
    const Array<PhysicalDeviceVk> PhysicalGraphicsDevices = GraphicsInstance.GetPhysicalGraphicsDevices();
    for (size_t i = 0; i < PhysicalGraphicsDevices.GetLength(); i++)
    {
        const PhysicalDevicePropertiesVk& Properties = PhysicalGraphicsDevices[i].GetProperties();
        const PhysicalDeviceFeaturesVk& Features = PhysicalGraphicsDevices[i].GetFeatures();

        const StringView DeviceName = Properties.GetName();
        const PhysicalDeviceTypeVk DeviceType = Properties.GetPhysicalGraphicsDeviceType();
    }
    PhysicalDeviceVk& SelectedPhysicalDevice = PhysicalGraphicsDevices[0];




    
    // check for queue familys to be used (in this case we're looking for graphics capabilities only) and create a logical device as well as queues required
    const Array<QueueFamilyPropertyVk> QueueFamilyProperties = SelectedPhysicalDevice.GetQueueFamilyProperties();
    List<DeviceQueueCreateInfoVk> DeviceQueueCreateInfos = List<DeviceQueueCreateInfoVk>();
    for (size_t i = 0; i < QueueFamilyProperties.GetLength(); i++)
    {
        QueueCapabilitiesVk Capabilities = QueueFamilyProperties[i].GetSupportedOperations();

        if ((Capabilities & QueueCapabilitiesVk::Graphics) == QueueCapabilitiesVk::Graphics)
        {
            DeviceQueueCreateInfoVk DeviceQueueCreateInfo = DeviceQueueCreateInfoVk(QueueFamilyProperties[i].GetIndex(), 1, 1.0f, Capabilities);
            DeviceQueueCreateInfos.Add(std::move(DeviceQueueCreateInfo));
        }
    }
    LogicalDeviceVk LogicalDevice = SelectedPhysicalDevice.CreateLogicalDevice(PresentationParameters, DeviceQueueCreateInfos);

    // ...
    QueueVk& Queue = LogicalDevice.RetrieveQueue(0, 0);
    */


    
    GraphicsInstanceDX12 GraphicsInstance = GraphicsInstanceDX12();
    PresentationParametersDX12 PresentationParameters = PresentationParametersDX12(GameWindow);
    GraphicsInstance.Initialize(PresentationParameters);
    const Array<PhysicalDeviceDX12> PhysicalGraphicsDevices = GraphicsInstance.GetPhysicalGraphicsDevices();
    PhysicalDeviceDX12& SelectedPhysicalDevice = PhysicalGraphicsDevices[0];
    

    const Elysium::Core::String DeviceName = SelectedPhysicalDevice.GetName();




    MyGame Game = MyGame(GameWindow, SelectedPhysicalDevice);
    Game.Run();
}
