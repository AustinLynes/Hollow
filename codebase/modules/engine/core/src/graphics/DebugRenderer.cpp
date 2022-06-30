#include "DebugRenderer.h"

#include "commands.h"

#include "interfaces/iSurface.h"

#include "DirectXTK/include/SimpleMath.h"

using namespace Graphics;
using namespace DirectX;

DebugRenderer::DebugRenderer() {
}

DebugRenderer::~DebugRenderer() {
	RenderCommands::Cleanup();
}

void DebugRenderer::Initilize(uint api, Graphics::iSurface* pWindow)
{
	window = pWindow;

	view = Matrix::Identity;

	RenderCommands::SelectAPI((API)api, reinterpret_cast<iSurface*>(window));


	uint cbuffers[1]{
		sizeof(SceneData)
	};

	pipeline_id = RenderCommands::CreateShaderPipeline(
		"assets/shaders/debug/vertex.hlsl",
		"assets/shaders/debug/lines.hlsl",
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT , D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },

		},
		TopologyType::Line,
		_countof(cbuffers),
		cbuffers
	);

	_vb = RenderCommands::CreateVertexBuffer(sizeof(DLine_Vertex));

}

void DebugRenderer::Shutdown()
{
}

void DebugRenderer::Render()
{
	RenderCommands::BeginFrame();
	{	// Set Frame Clear Color
		RenderCommands::SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Set Frame Depth Value
		RenderCommands::SetDepth(1.0);
		// Clear The Current Frame
		RenderCommands::Clear(COLOR_BUFFER | DEPTH_BUFFER);

		RenderCommands::BindShaderPipeline(pipeline_id);

		RenderCommands::SetTopology(TopologyType::Line);

		
		RenderCommands::BindVertexBuffer(_vb);
		RenderCommands::Draw(lines.data.size());
		RenderCommands::SubmitDrawData();
		
	}

	RenderCommands::Present(false);

	RenderCommands::EndFrame();
}

void DebugRenderer::AddLine(Line line, Color4 color) {

	lines.AddLine(line, color);
}

void DebugRenderer::AddLine(Line line, Color4 colorA, Color4 colorB) {

	lines.AddLine(line, colorA, colorB);
}

void DebugRenderer::ClearLines()
{
	lines.ClearLines();
}

void DebugRenderer::DrawGridXZ(float scale, float step, float4 color) {
	float minX = -scale;
	float maxX = scale;
	float minZ = -scale;
	float maxZ = scale;

	for (float x = minX; x <= maxX; x+= step)
	{
		AddLine({ {x, 0, minZ}, {x, 0, maxZ} }, color);
	}

	for (float z = minZ; z <= maxZ; z+= step)
	{
		AddLine({ { minX, 0, z}, {maxX, 0, z} }, color);
	}
}

void DebugRenderer::UpdateViewMatrix(matrix4f _view) {
	view = _view;
}

void DebugRenderer::DrawMatrix(matrix4f matrix) {

	// assert that the matrix is normalized
	float3 right = Math::Normalize(matrix.row0.xyz());	
	float3 up = Math::Normalize(matrix.row1.xyz());
	float3 forward = Math::Normalize(matrix.row2.xyz());
	float3 origin = matrix.row3.xyz();

	
	AddLine({ origin, origin + right}, { 1.0f, 0.0f, 0.0f, 1.0f });
	AddLine({ origin, origin + up},  { 0.0f, 1.0f, 0.0f, 1.0f });
	AddLine({ origin, origin + forward }, { 0.0f, 0.0f, 1.0f, 1.0f });

}

void DebugRenderer::DrawColliderAABB(matrix4f matrix, Color4 color)
{

	float3 origin = matrix.row3.xyz();
	float3 size = { matrix.row0.x, matrix.row1.y, matrix.row2.z };

	float3 right = {1.0f, 0.0f, 0.0f};

	float3 up = {0.0f, 1.0f, 0.0f};

	float3 forward = {0.0f, 0.0f, 1.0f};

	// calculate each of the corners of the bounding box

	float3 blb = (origin - (right) - (forward) - (up));
	float3 blf = (origin - (right) + (forward) - (up));
	float3 brb = (origin + (right) - (forward) - (up));
	float3 brf = (origin + (right) + (forward) - (up));
	float3 tlb = (origin - (right) - (forward) + (up));
	float3 tlf = (origin - (right) + (forward) + (up));
	float3 trb = (origin + (right) - (forward) + (up));
	float3 trf = (origin + (right) + (forward) + (up));

	// draw the bottom face
	AddLine({ blb, blf }, color);
	AddLine({ brb, brf }, color);
	
	AddLine({ blb, brb }, color);
	AddLine({ blf, brf }, color);


	// draw the top face
	AddLine({ tlb, tlf }, color);
	AddLine({ trb, trf }, color);

	AddLine({ tlb, trb }, color);
	AddLine({ tlf, trf }, color);


	// connect left edges

	AddLine({ blb, tlb }, color);
	AddLine({ blf, tlf }, color);


	// connect right edges
	AddLine({ brb, trb }, color);
	AddLine({ brf, trf }, color);


}

void DebugRenderer::DrawColliderOBB(matrix4f matrix, Color4 color)
{
	float3 size = { matrix.row0.x, matrix.row1.y, matrix.row2.z };
	float3 origin = matrix.row3.xyz();

	float3 right = matrix.row0.xyz();
	float3 up = matrix.row1.xyz();
	float3 forward = matrix.row2.xyz();

	// calculate each of the corners of the bounding box
	float3 blb = origin - right - forward - up;
	float3 blf = origin - right + forward - up;
	float3 brb = origin + right - forward - up;
	float3 brf = origin + right + forward - up;

	float3 tlb = origin - right - forward + up;
	float3 tlf = origin - right + forward + up;
	float3 trb = origin + right - forward + up;
	float3 trf = origin + right + forward + up;

	// draw the bottom face
	AddLine({ blb, blf }, color);
	AddLine({ brb, brf }, color);

	AddLine({ blb, brb }, color);
	AddLine({ blf, brf }, color);


	// draw the top face
	AddLine({ tlb, tlf }, color);
	AddLine({ trb, trf }, color);

	AddLine({ tlb, trb }, color);
	AddLine({ tlf, trf }, color);


	// connect left edges
	AddLine({ blb, tlb }, color);
	AddLine({ blf, tlf }, color);


	// connect right edges
	AddLine({ brb, trb }, color);
	AddLine({ brf, trf }, color);

}

void DebugRenderer::DrawFrustrum(frustum_t frust) {

	float3 NTL =  frust.edge_points[FrustrumPoint::NTL];
	float3 NTR =  frust.edge_points[FrustrumPoint::NTR];
	float3 NBL =  frust.edge_points[FrustrumPoint::NBL];
	float3 NBR =  frust.edge_points[FrustrumPoint::NBR];

	float3 FTL = frust.edge_points[FrustrumPoint::FTL] ;
	float3 FTR = frust.edge_points[FrustrumPoint::FTR] ;
	float3 FBL = frust.edge_points[FrustrumPoint::FBL] ;
	float3 FBR = frust.edge_points[FrustrumPoint::FBR] ;

	// Draw Frustum

	// draw near plane
	AddLine({ NTL, NTR }, { 1.0, 0.0, 1.0 });
	AddLine({ NTR, NBR }, { 1.0, 0.0, 1.0 });
	AddLine({ NBR, NBL }, { 1.0, 0.0, 1.0 });
	AddLine({ NBL, NTL }, { 1.0, 0.0, 1.0 });

	// draw far plane
	AddLine({ FTL, FTR }, { 1.0, 0.0, 1.0 });
	AddLine({ FTR, FBR }, { 1.0, 0.0, 1.0 });
	AddLine({ FBR, FBL }, { 1.0, 0.0, 1.0 });
	AddLine({ FBL, FTL }, { 1.0, 0.0, 1.0 });


	AddLine({ NTR, FTR }, { 1.0, 0.0, 1.0 });
	AddLine({ NTL, FTL }, {1.0, 0.0, 1.0});

	AddLine({ NBR, FBR}, { 1.0, 0.0, 1.0 });
	AddLine({ NBL, FBL}, { 1.0, 0.0, 1.0 });


	// Draw Plane Normals
	
	// NEAR PLANE
	float3 np_c = frust.centers[Near];
	AddLine({ np_c, np_c + frust.planes[Near].normal }, { 1.0, 1.0, 0.0f, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });
	
	// FAR PLANE
	float3 fp_c = frust.centers[Far];
	AddLine({ fp_c, fp_c + frust.planes[Far].normal }, { 1.0, 1.0, 0.0f, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });

	// LEFT PLANE
	float3 lp_c = frust.centers[Left];

	AddLine({ lp_c, lp_c + frust.planes[Left].normal }, { 1.0, 1.0, 0.0f, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });

	// RIGHT PLANE
	float3 rp_c =	frust.centers[Right];
	AddLine({ rp_c, rp_c + frust.planes[Right].normal }, { 1.0, 1.0, 0.0f, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });


	// TOP PLANE
	float3 tp_c = frust.centers[Top];
	AddLine({ tp_c, tp_c + frust.planes[Top].normal }, { 1.0, 1.0, 0.0f, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });

	float3 bp_c = frust.centers[Bottom];
	AddLine({bp_c, bp_c + frust.planes[Bottom].normal }, { 1.0, 1.0, 0.0f, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });


	// BOTTOM PLANE


}

void DebugRenderer::Update(double deltaTime)
{
	// Buffer Data
	RenderCommands::UpdateVertexBuffer(_vb, lines.data.data(), sizeof(DLine_Vertex) * lines.data.size());

	SceneData scene_data{};


	// Buffer Projection Matrix
	float aspect = window->GetWidth() / (float)window->GetHeight();

	projection = Matrix::ProjectionLH(to_radian(65.0f), aspect, 0.1f, 100.0f);

	scene_data.worldMatrix = Matrix::Identity;

	scene_data.projectionMatrix = projection;


	// Buffer Projection Matrix
	scene_data.viewMatrix = view;

	RenderCommands::UpdateConstantBuffer(pipeline_id, 0, (void*)&scene_data, sizeof(SceneData));


}
