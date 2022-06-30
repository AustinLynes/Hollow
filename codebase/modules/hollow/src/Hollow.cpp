#include "hollow.h"

#include "windows/window_manager.h"

// runtime layers
#include <editor.h>


Hollow::Hollow()
{
}

Hollow::~Hollow()
{

}

uint64 Hollow::Initilize()
{

	//window = new Window("Hollow", 640, 480, CENTER_SCREEN_X(640), CENTER_SCREEN_Y(480), nullptr);
	
	windowManager = new WindowManager();

	InputSystems = DEFAULT_INPUT_SYSTEMS;
	//window->AttachInputSystems(InputSystems);

	// simulate adding some runtime layers...
	runtime_layers["editor"] = new Editor();

	// initilize all runtime layers

	for (const auto& entry : runtime_layers)
	{
		auto runtime_layer = entry.second;

		runtime_layer->Initilize();

	}


	return 0;
}


uint64 Hollow::Tick()
{
	clock.Start();

	while (!should_close) {
		
		if (windowManager->ShouldClose()) {

			should_close = true;
			continue;
		}
		

		windowManager->Update();


		for (const auto& entry : runtime_layers)
		{
			auto runtime_layer = entry.second;

			runtime_layer->Tick();

		}
		
	}
	return 0;
}

uint64 Hollow::Shutdown()
{

	/*test->OnCleanup();
	delete test;*/

	for (const auto& entry : runtime_layers)
	{
		auto runtime_layer = entry.second;

		runtime_layer->Shutdown();

	}
	return 0;
}
