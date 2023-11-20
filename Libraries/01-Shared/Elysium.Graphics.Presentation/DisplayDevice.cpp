#include "DisplayDevice.hpp"

#ifndef ELYSIUM_GRAPHICS_PRESENTATION_WINDOW
#include "Window.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice> Elysium::Graphics::Presentation::DisplayDevice::_DisplayDevices = RetrieveDisplayDevices();

Elysium::Graphics::Presentation::DisplayDevice::DisplayDevice()
    : Elysium::Graphics::Presentation::DisplayDevice::DisplayDevice(-1)
{ }

Elysium::Graphics::Presentation::DisplayDevice::DisplayDevice(const Elysium::Core::uint32_t Handle)
    : _DisplayDeviceHandle(Handle), _IsPrimaryDisplayDevice(false), _CurrentBounds()
{ }

Elysium::Graphics::Presentation::DisplayDevice::DisplayDevice(DisplayDevice && Right) noexcept
    : _DisplayDeviceHandle(-1), _IsPrimaryDisplayDevice(false), _CurrentBounds()
{
    *this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Graphics::Presentation::DisplayDevice::~DisplayDevice()
{ }

Elysium::Graphics::Presentation::DisplayDevice& Elysium::Graphics::Presentation::DisplayDevice::operator=(DisplayDevice&& Right) noexcept
{
    if (this != &Right)
    {
        _DisplayDeviceHandle = Right._DisplayDeviceHandle;
        _IsPrimaryDisplayDevice = Right._IsPrimaryDisplayDevice;
        _CurrentBounds = Elysium::Core::Template::Functional::Move(Right._CurrentBounds);

        Right._DisplayDeviceHandle = -1;
        Right._IsPrimaryDisplayDevice = false;
    }
    return *this;
}

const Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice>& Elysium::Graphics::Presentation::DisplayDevice::GetActiveDisplayDevices()
{
	return _DisplayDevices;
}

const Elysium::Graphics::Presentation::DisplayDevice& Elysium::Graphics::Presentation::DisplayDevice::GetPrimaryDisplayDevice()
{
    if (_DisplayDevices.GetLength() == 0)
    {   // ToDo: throw specific exception
        throw 1;
    }

    // primary monitor should always be the first
    return _DisplayDevices[0];
}

const Elysium::Graphics::Presentation::DisplayDevice& Elysium::Graphics::Presentation::DisplayDevice::GetDisplayDeviceFromWindow(const Window& Window)
{
    HMONITOR MonitorHandle = MonitorFromWindow((HWND)Window._WindowHandle, MONITOR_DEFAULTTONEAREST);
    for (size_t i = 0; i < _DisplayDevices.GetLength(); i++)
    {
        if ((HMONITOR)_DisplayDevices[i]._DisplayDeviceHandle == MonitorHandle)
        {
            return _DisplayDevices[i];
        }
    }
}

const bool& Elysium::Graphics::Presentation::DisplayDevice::GetIsPrimaryDisplayDevice() const
{
    return _IsPrimaryDisplayDevice;
}

const Elysium::Core::Math::Geometry::Rectangle& Elysium::Graphics::Presentation::DisplayDevice::GetCurrentBounds() const
{
    return _CurrentBounds;
}

void Elysium::Graphics::Presentation::DisplayDevice::RefreshValues()
{
    MONITORINFOEXW Info = MONITORINFOEXW();
    Info.cbSize = sizeof(MONITORINFOEXW);
    if (!GetMonitorInfoW((HMONITOR)_DisplayDeviceHandle, (MONITORINFO*)&Info))
    {   // ToDo: throw specific exception
        throw 1;
    }

    _IsPrimaryDisplayDevice = (Info.dwFlags == MONITORINFOF_PRIMARY);
    _CurrentBounds.X = Info.rcMonitor.left;
    _CurrentBounds.Y = Info.rcMonitor.top;
    _CurrentBounds.Width = Info.rcMonitor.right;
    _CurrentBounds.Height = Info.rcMonitor.bottom;




    // ToDo:
    // refresh rate, dpi, bits per pixel etc.
    DEVMODEW DeviceMode = DEVMODEW();
    DeviceMode.dmSize = sizeof(DEVMODEW);
    if (!EnumDisplaySettingsW(Info.szDevice, ENUM_CURRENT_SETTINGS, &DeviceMode))
    {
        throw 1;
    }



    int sdf = 45;
}

Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice> Elysium::Graphics::Presentation::DisplayDevice::RetrieveDisplayDevices()
{
    Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice> Monitors =
        Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice>();

#if defined(ELYSIUM_CORE_OS_WINDOWS)
    if (!EnumDisplayMonitors(nullptr, nullptr, EnumDisplayDevicesCallback, (LPARAM)&Monitors))
    {   // ToDo: throw specific exception
        throw 1;
    }

    for (size_t i = 0; i < Monitors.GetLength(); i++)
    {
        Monitors[i].RefreshValues();
    }
#else
#error "unsupported os"
#endif

    return Monitors;
}

Elysium::Core::int32_t Elysium::Graphics::Presentation::DisplayDevice::EnumDisplayDevicesCallback(HMONITOR Handle, HDC Dc, RECT* Rectangle, LPARAM Data)
{
    Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice>* Monitors =
        reinterpret_cast<Elysium::Core::Template::Container::Vector<Elysium::Graphics::Presentation::DisplayDevice>*>(Data);
    Monitors->PushBack((Elysium::Core::uint32_t)Handle);

    return 1;
}
