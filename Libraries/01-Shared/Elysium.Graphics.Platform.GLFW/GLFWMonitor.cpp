#include "GLFWMonitor.hpp"

#ifndef ELYSIUM_CORE_TEXT_ENCODING
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Text/Encoding.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_APINOTAVAILABLEEXCEPTION
#include "../Elysium.Graphics/APINotAvailableException.hpp"
#endif

Elysium::Graphics::Platform::GLFW::GLFWMonitor::GLFWMonitor()
	: _NativeMonitor(nullptr), _NativeVideoMode(nullptr), _PhysicalSize(), _Position(), _CurrentResolution()
{ }
Elysium::Graphics::Platform::GLFW::GLFWMonitor::~GLFWMonitor()
{
	glfwSetMonitorCallback(nullptr);
	glfwTerminate();
}

const void* Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetHandle() const
{
	return _NativeMonitor;
}

const bool Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetIsPrimaryMonitor() const
{
	return _NativeMonitor == glfwGetPrimaryMonitor();
}

const Elysium::Core::String Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetName() const
{
	return Elysium::Core::String((const char8_t*)glfwGetMonitorName(_NativeMonitor));
}

const Elysium::Core::Math::Geometry::Point& Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetPhysicalSize() const
{
	return _PhysicalSize;
}

const Elysium::Core::Math::Geometry::Point& Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetCurrentResolution() const
{
	return _CurrentResolution;
}

const Elysium::Core::uint32_t Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetCurrentRefreshRate() const
{
	return _NativeVideoMode->refreshRate;
}

const Elysium::Core::Math::Geometry::Point& Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetPosition() const
{
	return _Position;
}

const Elysium::Core::Collections::Template::Array<Elysium::Graphics::Platform::GLFW::GLFWMonitor> Elysium::Graphics::Platform::GLFW::GLFWMonitor::GetMonitors()
{
	if (glfwInit() != GLFW_TRUE)
	{
		throw APINotAvailableException(u8"GLFW");
	}
	Elysium::Core::int32_t MonitorCount;
	GLFWmonitor** NativeMonitors = glfwGetMonitors(&MonitorCount);

	Elysium::Core::Collections::Template::Array<Elysium::Graphics::Platform::GLFW::GLFWMonitor> Result =
		Elysium::Core::Collections::Template::Array<Elysium::Graphics::Platform::GLFW::GLFWMonitor>(MonitorCount);
	for (size_t i = 0; i < MonitorCount; i++)
	{
		Result[i].SetNativeMonitor(NativeMonitors[i]);
	}

	return Result;
}

void Elysium::Graphics::Platform::GLFW::GLFWMonitor::SetNativeMonitor(GLFWmonitor* NativeMonitor)
{
	_NativeMonitor = NativeMonitor;
	_NativeVideoMode = glfwGetVideoMode(_NativeMonitor);

	_CurrentResolution.X = _NativeVideoMode->width;
	_CurrentResolution.Y = _NativeVideoMode->height;

	glfwGetMonitorPhysicalSize(_NativeMonitor, &_PhysicalSize.X, &_PhysicalSize.Y);
	glfwGetMonitorPos(_NativeMonitor, &_Position.X, &_Position.Y);

	glfwSetMonitorUserPointer(_NativeMonitor, static_cast<void*>(this));
	glfwSetMonitorCallback(Monitor_Callback);
}

void Elysium::Graphics::Platform::GLFW::GLFWMonitor::Monitor_Callback(GLFWmonitor* NativeMonitor, Elysium::Core::int32_t Event)
{
	GLFWMonitor* Handler = static_cast<GLFWMonitor*>(glfwGetMonitorUserPointer(NativeMonitor));
	// ToDo: this callback is called when a monitor is connected/disconnected
}
