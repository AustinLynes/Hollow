#pragma once

#include "cpch.h"
#include "cdefs.h"

#include "window.h"
#include "interfaces/iGUIElement.h"


class WindowManager : public iWindowManager {
public:
	WindowManager();
	~WindowManager();

	virtual void Update();

	bool ShouldClose() { return win->ShouldClose(); }


private:
	Window* win;

};