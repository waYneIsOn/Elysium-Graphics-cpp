#include "Window.hpp"

#define IDI_SMALL				108
#define IDC_WINDOWSPROJECT1			109

void* Elysium::Graphics::Presentation::Window::_ProgramInstanceHandle = GetModuleHandle(nullptr);

Elysium::Graphics::Presentation::Window::Window()
	: Elysium::Graphics::Presentation::Control(),
    _BorderStyle(WindowBorderStyle::None), _Width(800), _Height(480), _WindowHandle(CreateNativeWindow())
{
	ActivationChanged += Elysium::Core::Template::Container::Delegate<void, const Elysium::Graphics::Presentation::Control&, const bool>::Bind<Elysium::Graphics::Presentation::Window, &Elysium::Graphics::Presentation::Window::OnActivationChanged>(*this);
}

Elysium::Graphics::Presentation::Window::~Window()
{
	ActivationChanged -= Elysium::Core::Template::Container::Delegate<void, const Elysium::Graphics::Presentation::Control&, const bool>::Bind<Elysium::Graphics::Presentation::Window, &Elysium::Graphics::Presentation::Window::OnActivationChanged>(*this);
}

const void* Elysium::Graphics::Presentation::Window::GetHandle() const
{
    return _WindowHandle;
}

void Elysium::Graphics::Presentation::Window::Show()
{
    //SetWindowLong((HWND)_WindowHandle, GWL_STYLE, WS_POPUP);

    ShowWindow((HWND)_WindowHandle, SW_SHOW);
    UpdateWindow((HWND)_WindowHandle);
    SetForegroundWindow((HWND)_WindowHandle);
    SetFocus((HWND)_WindowHandle);

    HACCEL AcceleratorTableHandle = LoadAccelerators((HINSTANCE)&_ProgramInstanceHandle, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));
    MSG Message;
    while (GetMessage(&Message, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(Message.hwnd, AcceleratorTableHandle, &Message))
        {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
    }
}

void Elysium::Graphics::Presentation::Window::Close()
{
    throw 1;
}

void* Elysium::Graphics::Presentation::Window::CreateNativeWindow()
{
    WNDCLASSEXW WindowClassDescription = WNDCLASSEXW();
    WindowClassDescription.cbSize = sizeof(WNDCLASSEXW);
    //WindowClassDescription.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WindowClassDescription.style = CS_HREDRAW | CS_VREDRAW;
    WindowClassDescription.lpfnWndProc = WindowsMessageHandlerCallback;
    WindowClassDescription.cbClsExtra = 0;
    WindowClassDescription.cbWndExtra = 0;
    WindowClassDescription.hInstance = (HINSTANCE)&_ProgramInstanceHandle;
    WindowClassDescription.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WindowClassDescription.hCursor = LoadCursor(NULL, IDC_ARROW);
    //WindowClassDescription.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WindowClassDescription.hbrBackground = nullptr;
    WindowClassDescription.lpszMenuName = nullptr;
    WindowClassDescription.lpszClassName = _ClassName;
    WindowClassDescription.hIconSm = LoadIcon((HINSTANCE)&_ProgramInstanceHandle, MAKEINTRESOURCE(IDI_SMALL));

    if (!RegisterClassExW(&WindowClassDescription))
    {   // ToDo: throw specific exception
        throw 1;
    }

    /*
    // ToDo: if fullscreen and resolution differs from display device
    DEVMODE game_screen;
    memset(&game_screen, 0, sizeof(DEVMODE));
    game_screen.dmPelsWidth = 1920;
    game_screen.dmPelsHeight = 1080;
    game_screen.dmBitsPerPel = 32;
    ChangeDisplaySettings(&game_screen, CDS_FULLSCREEN);
    */

    DWORD Style =
        //WS_MAXIMIZE | WS_OVERLAPPEDWINDOW;  // maximized window with borders, menu etc.
        WS_OVERLAPPEDWINDOW;  // window with borders, menu etc.
        //WS_POPUP;   // no borders etc.

    HWND WindowHandle = CreateWindowExW(WS_EX_APPWINDOW, _ClassName, _ClassName, Style, 0, 0, _Width, _Height, nullptr, nullptr,
        (HINSTANCE)&_ProgramInstanceHandle, this);
    if (WindowHandle == nullptr)
    {   // ToDo: throw specific exception -> GetLastError()
        throw 1;
    }

    // get client bounds
    RECT Rect;
    if (!GetClientRect(WindowHandle, &Rect))
    {
        DestroyWindow(WindowHandle);
        
        // ToDo: throw specific exception
        throw 1;
    }
    _Width = Rect.right - Rect.left;
    _Height = Rect.bottom - Rect.top;

    // "associate" instance with window handle
    if (!SetPropW(WindowHandle, _ClassName, this))
    {
        DestroyWindow(WindowHandle);
        
        // ToDo: throw specific exception
        throw 1;
    }

    return WindowHandle;
}

void Elysium::Graphics::Presentation::Window::CenterToDisplayDevice()
{
    const DisplayDevice& ClosestDisplayDevice = DisplayDevice::GetDisplayDeviceFromWindow(*this);
    const Elysium::Core::Math::Geometry::Rectangle& DisplayDeviceBounds = ClosestDisplayDevice.GetCurrentBounds();

    RECT WindowRectangle;
    if (!GetWindowRect((HWND)_WindowHandle, &WindowRectangle))
    {   // ToDo: throw specfic position
        throw 1;
    }

    if (!SetWindowPos((HWND)_WindowHandle, nullptr, (DisplayDeviceBounds.Width - (WindowRectangle.right - WindowRectangle.left)) >> 1,
        (DisplayDeviceBounds.Height - (WindowRectangle.bottom - WindowRectangle.top)) >> 1, 0, 0, SWP_NOSIZE | SWP_NOZORDER))
    {   // ToDo: throw specfic position
        throw 1;
    }
}

void Elysium::Graphics::Presentation::Window::OnActivationChanged(const Elysium::Graphics::Presentation::Control& Sender, const bool HasActived)
{
    throw 1;
}

LRESULT Elysium::Graphics::Presentation::Window::WindowsMessageHandlerCallback(HWND WindowHandle, UINT Message, WPARAM wParam, LPARAM lParam)
{
    // grab window from handle
    Elysium::Graphics::Presentation::Window* Window = (Elysium::Graphics::Presentation::Window*)GetPropW(WindowHandle, _ClassName);

    // process specific messages
    switch (Message)
    {
    case WM_COMMAND:
    {
        /*
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        */
        break;
    }
    case WM_SETFOCUS:
    {
        // ...
        break;
    }
    case WM_KILLFOCUS:
    {
        // ...
        break;
    }
    //case WM_DISPLAYCHANGE:
    case WM_SIZE:
    {
        if (Window != nullptr)
        {
            // get client bounds
            RECT Rect;
            if (!GetClientRect((HWND)WindowHandle, &Rect))
            {   // ToDo: throw specific exception
                throw 1;
            }

            Elysium::Core::uint32_t Width = Rect.right - Rect.left;
            Elysium::Core::uint32_t Height = Rect.bottom - Rect.top;
            if (Width != Window->_Width || Height != Window->_Height)
            {
                Window->_Width = Width;
                Window->_Height = Height;
                Window->SizeChanged(*Window, Width, Height);
            }
        }
        break;
    }
    break;
    case WM_SIZING:
    {
        // ...
    }
    break;
    case WM_PAINT:
    {
        if (Window != nullptr)
        {
            Window->Paint(*Window);
        }
        return 0;
    }
    case WM_DESTROY:
    {
        if (Window != nullptr)
        {
            Window->Exiting(*Window);
        }
        PostQuitMessage(0);
        break;
    }
    }

    // "auto"-process all other messages
    return DefWindowProc(WindowHandle, Message, wParam, lParam);
}
