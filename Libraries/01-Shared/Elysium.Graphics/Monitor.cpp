#include "Monitor.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor> Elysium::Graphics::Platform::Monitor::_Monitors = Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor>();

Elysium::Graphics::Platform::Monitor::~Monitor()
{ }

const Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor>& Elysium::Graphics::Platform::Monitor::GetActiveMonitors()
{
    _Monitors.Clear();
#if defined(ELYSIUM_CORE_OS_WINDOWS)
    if (!EnumDisplayMonitors(nullptr, nullptr, EnumDisplayMonitorsCallback, (LPARAM)&_Monitors))
    {   // ToDo: throw specific exception
        throw 1;
    }

    for (size_t i = 0; i < _Monitors.GetCount(); i++)
    {
        _Monitors[i].RefreshValues();
    }

    return _Monitors;
#else
#error "unsupported os"
#endif
}

const Elysium::Graphics::Platform::Monitor& Elysium::Graphics::Platform::Monitor::GetPrimaryMonitor()
{
    if (_Monitors.GetCount() == 0)
    {
        GetActiveMonitors();
    }

    // primary monitor should always be the first
    return _Monitors[0];
}

const bool& Elysium::Graphics::Platform::Monitor::GetIsPrimaryMonitor() const
{
    return _IsPrimaryMonitor;
}

Elysium::Graphics::Platform::Monitor::Monitor()
    : Elysium::Graphics::Platform::Monitor::Monitor(-1)
{ }
Elysium::Graphics::Platform::Monitor::Monitor(const Elysium::Core::uint32_t Handle)
    : _Handle(Handle), _IsPrimaryMonitor(false), _CurrentBounds()
{ }
Elysium::Graphics::Platform::Monitor::Monitor(Monitor&& Right) noexcept
    : _Handle(-1), _IsPrimaryMonitor(false), _CurrentBounds()
{
    *this = std::move(Right);
}

Elysium::Graphics::Platform::Monitor& Elysium::Graphics::Platform::Monitor::operator=(Monitor&& Right) noexcept
{
    if (this != &Right)
    {
        _Handle = Right._Handle;
        _IsPrimaryMonitor = Right._IsPrimaryMonitor;
        _CurrentBounds = std::move(Right._CurrentBounds);

        Right._Handle = -1;
        Right._IsPrimaryMonitor = false;
    }
    return *this;
}

void Elysium::Graphics::Platform::Monitor::RefreshValues()
{
    MONITORINFOEXW Info = MONITORINFOEXW();
    Info.cbSize = sizeof(MONITORINFOEXW);
    if (!GetMonitorInfoW((HMONITOR)_Handle, (MONITORINFO*)&Info))
    {   // ToDo: throw specific exception
        throw 1;
    }

    _IsPrimaryMonitor = (Info.dwFlags == MONITORINFOF_PRIMARY);
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

Elysium::Core::int32_t Elysium::Graphics::Platform::Monitor::EnumDisplayMonitorsCallback(HMONITOR Handle, HDC Dc, RECT* Rectangle, LPARAM Data)
{
    Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor>* Monitors = (Elysium::Core::Collections::Template::List<Elysium::Graphics::Platform::Monitor>*)Data;
    Monitors->Add((Elysium::Core::uint32_t)Handle);

    return 1;
}
