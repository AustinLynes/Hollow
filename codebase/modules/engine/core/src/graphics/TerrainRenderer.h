#pragma once

#include "cpch.h"
#include "cdefs.h"

#include "interfaces/irenderer.h"
#include "structures/vertices.h"

namespace Graphics {
	enum class API;
	class iSurface;
}

class TerrainRenderer : public iRenderer
{
public:
	virtual void Initilize(uint api, Graphics::iSurface* window) override;
	virtual void Shutdown() override;

	virtual void Render() override;

	virtual void Update(double deltaTime) override;

	void LoadTerrainData(std::vector<Vertex_PCNU> buffer);

private:
	// CPU side vertex buffer
	std::vector<Vertex_PCNU> vertex_buffer;


	// REALLY WANNA GET THIS OUTTA HERE...
	// THIS DATA IS CONTAINED WITHIN THE SCENE DATA STRUCT
	// THERE IS NO NEED TO HAVE IT AS A MEMEBER IN EACH RENDERER
	// THIS MAKES IT SO THAT BOUND RENDERERS MAY HAVE NON-MATCHING RENDERERS
	matrix4f view;
	matrix4f projection;

};

