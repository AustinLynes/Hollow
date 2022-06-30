#pragma once

#include <iostream>

#include "interfaces/IExecutable.h"

#include "time/clock.h"

#include "input/Keyboard.h"
#include "input/Mouse.h"

// runtime application
class WindowManager;
class iRuntimeLayer;

class Hollow : public iExecutable
{
public:
	Hollow();
	~Hollow();

	virtual uint64 Initilize() override;
	virtual uint64 Tick() override;
	virtual uint64 Shutdown() override;

private:
	
	Clock clock;


	std::map<InputType, iInputSystem*> InputSystems;

	std::map<const char*, iRuntimeLayer*> runtime_layers;

	WindowManager* windowManager;


	// state
	bool should_close = false;

};

iExecutable* CreateExecutable() {
	return new Hollow();
}


