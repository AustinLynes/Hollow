#include "window.h"

#include "input/keyboard.h"
#include "input/mouse.h"
#include "windowsx.h"

Window::Window(const std::string& _title, int _width, int _height, int pos_x, int pos_y, Window* parent)
{
	if (!glfwInit()) { 
		throw std::runtime_error("Could Not Initilize GLFW!!"); 
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	win = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr );
	if (win == nullptr) {
		throw std::runtime_error("Could Not Create GLFW Window!!");
	}

	glfwSetWindowUserPointer(win, this);


	glfwMakeContextCurrent(win);
	glfwShowWindow(win);

}

Window::~Window()
{
}

void Window::AttachInputSystems(std::map<InputType, iInputSystem*>& _systems)
{
	systems = _systems;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(win);
}

void Window::SwapBuffers(bool _vsync)
{
	glfwPollEvents();


	glfwSwapInterval(_vsync ? 1 : 0);
	glfwSwapBuffers(win);
}

void Window::KeyCallback()
{
	//Keyboard* kbd = reinterpret_cast<Keyboard*>(systems[InputType::Keyboard]);
	//Mouse* mouse = reinterpret_cast<Mouse*>(systems[InputType::Mouse]);

	//switch (msg)
	//{
	//	if (kbd) {

	//		// default keypress
	//case WM_KEYDOWN:
	//	kbd->OnKeyDown((KeyCode)w);
	//	break;

	//case WM_KEYUP:
	//	kbd->OnKeyUp((KeyCode)w);
	//	break;

	//	}


	//	if (mouse) {

	//case WM_MOUSEMOVE:

	//	mouse->OnMouseMove(GET_X_LPARAM(l), GET_Y_LPARAM(l));

	//	break;


	//case WM_RBUTTONDOWN:
	//	mouse->OnMouseButtonDown(MouseButton::RMB);
	//	SetCapture(GetSurfacePointer());
	//	break;


	//case WM_RBUTTONUP:
	//	mouse->OnMouseButtonUp(MouseButton::RMB);
	//	ReleaseCapture();
	//	break;


	//	}

	//	// Handle All Default Messages
	//default:
	//	return iSurface::MessageHandler(msg, w, l);
	//}
}
