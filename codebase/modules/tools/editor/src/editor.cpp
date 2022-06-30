#include "editor.h"

#include "windows/window.h"
#include "graphics/DebugRenderer.h"

#include "mathematics.h"

Editor::Editor()
{

	/*Renderers = DEFAULT_RENDERERS;
	for (const auto& entry : Renderers)
	{
		iRenderer* r = entry.second;
		r->Initilize(RENDER_API, window);
	}*/
	


}

Editor::~Editor()
{

}

uint64 Editor::Initilize()
{
	clock.Start();

	return 0;
}


uint64 Editor::Tick()
{
	auto deltaTime = clock.Signal();
	
	// data gets submitted to all redererers...
	

	DebugRenderer* dbg = static_cast<DebugRenderer*>(Renderers[RenderType::Debug]);

	//dbg->DrawGridXZ(10.0, 1.0, { 0.16f, 0.16f, 0.16f, 1.0 });

	//matrix4f camera = Matrix::Identity;
	//camera = Matrix::LookAtLH({ 0.0f, 10.0f, -10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

	//dbg->UpdateViewMatrix(camera);


	//// renderers buffer data.. and submit it to the render queue
	//for (auto& entry : Renderers) {
	//	iRenderer* renderer = entry.second;
	//	renderer->Update(deltaTime);
	//	renderer->Render();
	//}
	//// now render it...
	///*for (auto& entry : Renderers) {
	//	iRenderer* renderer = entry.second;
	//}*/

	//// BAD!!! 
	//dbg->ClearLines();


	return 0;
}

uint64 Editor::Shutdown()
{

	return 0;
}
