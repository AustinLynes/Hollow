#include "IRenderer.h"

#include "graphics/DebugRenderer.h"
#include "graphics/TerrainRenderer.h"

iRenderer* iRenderer::Create(RenderType type)
{
	switch (type)
	{
	case RenderType::Debug:
		return new DebugRenderer();
		break;
	case RenderType::Terrain:
		return new TerrainRenderer();
		break;
	
	// unimplemented
	case RenderType::Obj_Deferred:
	case RenderType::Obj_Forward:
		break;
	default:
		break;
	}
}

std::map<RenderType, iRenderer*> iRenderer::CreateRenderers(uint mask)
{
	std::map<RenderType, iRenderer*> renderers;

	if ((mask & RENDERER_DEBUG) == RENDERER_DEBUG)
	{
		renderers[RenderType::Debug] = iRenderer::Create(RenderType::Debug);
	}
	if ((mask & RENDERER_TERRAIN) == RENDERER_TERRAIN)
	{
		renderers[RenderType::Terrain] = iRenderer::Create(RenderType::Terrain);
	}

	return renderers;
}
