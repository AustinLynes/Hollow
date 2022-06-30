#include "TerrainRenderer.h"

#include "commands.h"

using namespace Graphics;

void TerrainRenderer::Initilize(uint api, Graphics::iSurface* pWindow)
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

void TerrainRenderer::Shutdown()
{
}

void TerrainRenderer::Render()
{
	RenderCommands::BeginFrame();
	{	// Set Frame Clear Color
		RenderCommands::SetClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// Set Frame Depth Value
		RenderCommands::SetDepth(1.0);
		// Clear The Current Frame
		RenderCommands::Clear(COLOR_BUFFER | DEPTH_BUFFER);

		RenderCommands::BindShaderPipeline(pipeline_id);

		RenderCommands::SetTopology(TopologyType::Triangle);


		RenderCommands::BindVertexBuffer(_vb);
		RenderCommands::Draw(vertex_buffer.size());
		RenderCommands::SubmitDrawData();

	}

	RenderCommands::Present(false);

	RenderCommands::EndFrame();

}

void TerrainRenderer::Update(double deltaTime)
{
}

// for now just copy the data to the vertex buffer...
// after finished i will move the file loading functionality to the terrain renderer itself
void TerrainRenderer::LoadTerrainData(std::vector<Vertex_PCNU> buffer)
{
	vertex_buffer = buffer;
}
