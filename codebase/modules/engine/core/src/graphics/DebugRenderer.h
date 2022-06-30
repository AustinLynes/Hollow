#pragma once

#include "cpch.h"
#include "cdefs.h"

#include "interfaces/IRenderer.h"
#include "structures/vertices.h"
#include <array>

// Forward Decleration from modules/Graphics
namespace Graphics {
enum class API;
class iSurface;
}


class DebugRenderer : public iRenderer {
public:
	DebugRenderer();
	~DebugRenderer();

	// Inherited via IRenderer
	virtual void Initilize(uint api, Graphics::iSurface* window) override;

	virtual void Shutdown() override;

	virtual void Render() override;

	virtual void Update(double deltaTime) override;

	void UpdateViewMatrix(matrix4f _view);

	void AddLine(Line line, Color4 color);
	void AddLine(Line line, Color4 colorA, Color4 colorB);

	void DrawGridXZ(float size, float step, float4 color);
	void DrawMatrix(matrix4f matrix);
	
	void DrawColliderAABB(matrix4f matrix, Color4 color);
	void DrawColliderOBB(matrix4f matrix, Color4 color);
	
	void DrawFrustrum(frustum_t frustrum);

	void ClearLines();

private:

	// cpu side vertex buffer
	LineList lines;


	matrix4f view;
	matrix4f projection;

};