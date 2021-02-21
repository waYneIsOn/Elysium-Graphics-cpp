#include "Window.hpp"

#define IDS_APP_TITLE			103

#define IDR_MAINFRAME			128
#define IDD_WINDOWSPROJECT1_DIALOG	102
#define IDD_ABOUTBOX			103
#define IDM_ABOUT				104
#define IDM_EXIT				105
#define IDI_WINDOWSPROJECT1			107
#define IDI_SMALL				108
#define IDC_WINDOWSPROJECT1			109
#define IDC_MYICON				2
#ifndef IDC_STATIC
#define IDC_STATIC				-1
#endif

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS

#define _APS_NO_MFC					130
#define _APS_NEXT_RESOURCE_VALUE	129
#define _APS_NEXT_COMMAND_VALUE		32771
#define _APS_NEXT_CONTROL_VALUE		1000
#define _APS_NEXT_SYMED_VALUE		110
#endif
#endif

size_t Elysium::Graphics::Presentation::Window::_ProgramInstanceHandle = -1;

Elysium::Graphics::Presentation::Window::Window()
	: Elysium::Graphics::Presentation::Control(),
    _WindowHandle(CreateNativeWindow())
{
    CenterToMonitor();

	ActivationChanged += Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const bool>::CreateDelegate<Elysium::Graphics::Presentation::Window, &Elysium::Graphics::Presentation::Window::OnActivationChanged>(*this);
}
Elysium::Graphics::Presentation::Window::~Window()
{
	ActivationChanged -= Elysium::Core::Delegate<void, const Elysium::Graphics::Presentation::Control&, const bool>::CreateDelegate<Elysium::Graphics::Presentation::Window, &Elysium::Graphics::Presentation::Window::OnActivationChanged>(*this);
}

const size_t Elysium::Graphics::Presentation::Window::GetHandle() const
{
    return _WindowHandle;
}

void Elysium::Graphics::Presentation::Window::Show()
{
    ShowWindow((HWND)_WindowHandle, 10);

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

size_t Elysium::Graphics::Presentation::Window::CreateNativeWindow()
{
    if (_ProgramInstanceHandle == -1)
    {
        _ProgramInstanceHandle = (size_t)GetModuleHandle(nullptr);
    }

    WNDCLASSEXW WindowClassDescription = WNDCLASSEXW();
    WindowClassDescription.cbSize = sizeof(WNDCLASSEXW);
    WindowClassDescription.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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

    size_t Result = (size_t)CreateWindowExW(0L, _ClassName, L"WindowTitle", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 480, nullptr, nullptr,
        (HINSTANCE)&_ProgramInstanceHandle, this);

    // "associate" instance with window handle
    if (!SetPropW((HWND)Result, _ClassName, this))
    {   // ToDo: throw specific exception
        throw 1;
    }

    return Result;
}

void Elysium::Graphics::Presentation::Window::CenterToMonitor()
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
    case WM_SIZING:
    {
        if (Window != nullptr)
        {
            int Edge = wParam;
            RECT* Rect = (RECT*)lParam;
            /*
            if (Edge == WMSZ_LEFT || Edge == WMSZ_BOTTOMLEFT || Edge == WMSZ_RIGHT || Edge == WMSZ_BOTTOMRIGHT)
            {

            }
            else if (Edge == WMSZ_TOPLEFT || Edge == WMSZ_TOPRIGHT)
            {

            }
            else if (Edge == WMSZ_TOP || Edge == WMSZ_BOTTOM)
            {

            }
            */
            Window->SizeChanged(*Window, Rect->right - Rect->left, Rect->bottom - Rect->top);
        }
        break;
    }
    case WM_PAINT:
    {
        if (Window != nullptr)
        {
            Window->Paint(*Window);
        }
        break;
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
    default:
        return DefWindowProc(WindowHandle, Message, wParam, lParam);
    }

    return 0;
}
