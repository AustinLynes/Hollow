#pragma once

#include "cpch.h"
#include "cdefs.h"

#include <map>

#include "interfaces/isurface.h"
#include "interfaces/iInputSystem.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


class Window
{
public:
	Window(const std::string& _title, int _width, int _height, int pos_x = 0, int pos_y = 0, Window* parent=nullptr);
	~Window();


	void AttachInputSystems(std::map<InputType, iInputSystem*>& _systems);

	bool ShouldClose();

	GLFWwindow* GetWindowPointer() { return win; }

	void SwapBuffers(bool _vsync = true);

protected:
	void KeyCallback();


private:
	std::map<InputType, iInputSystem*> systems;


	GLFWwindow* win;
};

