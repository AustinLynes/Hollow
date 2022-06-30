#pragma once

#include <iostream>

#include "interfaces/iRuntimeApp.h"

#include "time/clock.h"

#include "interfaces/IRenderer.h"
#include "interfaces/iInputSystem.h"

// editor runtime application
class Window;

class Editor : public iRuntimeLayer
{
public:
	Editor();
	~Editor();

	virtual uint64 Initilize() override;
	virtual uint64 Tick() override;
	virtual uint64 Shutdown() override;
	
private:
	
	std::map<RenderType, iRenderer*> Renderers;


	Clock clock;
};



