#pragma once

#include "cpch.h"
#include "cdefs.h"

#include <mathematics.h>

struct SceneData {
	matrix4f worldMatrix;		// 64
	matrix4f viewMatrix;		// 64
	matrix4f projectionMatrix;	// 64

	float4 padding[4];			// 64
};



namespace Graphics {
	class iSurface;
}


enum class RenderType {
	Debug,
	Terrain,

	Obj_Forward,
	Obj_Deferred
};

#define RENDERER_DEBUG			0x0000'0000'0000'0001u
#define RENDERER_TERRAIN		0x0000'0000'0000'0010u

class iRenderer {
public:
	iRenderer() {}
	virtual ~iRenderer() {}


	virtual void Initilize(uint api, Graphics::iSurface* window) = 0;
	virtual void Shutdown() = 0;
	
	virtual void Render() = 0;
	virtual void Update(double deltaTime) = 0;

	static iRenderer* Create(RenderType type);
	static std::map<RenderType, iRenderer*> CreateRenderers(uint mask);

protected:
	// GPU pipeline pointers
	uint pipeline_id;

	// GPU buffer pointers
	uint _vb;
	uint _ib;
	uint _cb;
	uint _sr;
	uint _ua;

	Graphics::iSurface* window;

};

#define DEFAULT_RENDERERS iRenderer::CreateRenderers(RENDERER_DEBUG)