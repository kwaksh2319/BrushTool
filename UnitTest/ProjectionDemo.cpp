#include "stdafx.h"
#include "ProjectionDemo.h"
#include "Viewer/Freedom.h"
#include "Environment/Terrain.h"

void ProjectionDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(0, 0, 0);
	Context::Get()->GetCamera()->Position(0, 0, -10);
	((Freedom*)Context::Get()->GetCamera())->Speed(100, 2);

	shader = new Shader(L"12_Terrain_GetHeight.fx");

	terrain = new Terrain(shader, L"Terrain/Gray256.png");
	terrain->BaseMap(L"Terrain/Dirt3.png");

	meshShader = new Shader(L"10_Mesh.fx");
	sphere = new MeshSphere(meshShader, 0.5f);
	sphere->Color(1, 0, 0);
}

void ProjectionDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
	SafeDelete(meshShader);
	SafeDelete(sphere);
}

void ProjectionDemo::Update()
{
	Vector3 position;
	Vector3 scale;
	sphere->Position(&position);

	if (Keyboard::Get()->Press(VK_UP))
		position.z += 20.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_DOWN))
		position.z -= 20.0f * Time::Delta();

	if (Keyboard::Get()->Press(VK_RIGHT))
		position.x += 20.0f * Time::Delta();
	else if (Keyboard::Get()->Press(VK_LEFT))
		position.x -= 20.0f * Time::Delta();

	//position.y = terrain->GetHeight(position);
	sphere->Scale(&scale);
	position.y = terrain->GetHeightPick(position) + scale.y*0.5f;
	sphere->Position(position);


	static Vector3 light = Vector3(-1, -1, 1);
	ImGui::SliderFloat3("Light", light, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(light);
	meshShader->AsVector("LightDirection")->SetFloatVector(light);




	terrain->Update();
}


void ProjectionDemo::Render()
{

	Matrix w, v, p;
	D3DXMatrixIdentity(&w);
	v = Context::Get()->View();
	p = Context::Get()->Projection();
	Viewport*vp = Context::Get()->GetViewport();

	Vector3 result, position;
	sphere->Position(&position);

	vp->Project(&result, position, w, v, p);
	Gui::Get()->RenderText(result.x, result.y, 0, 0, 1, "ssss");
	//terrain->Pass(1);
	sphere->Render();
	terrain->Render();

	ImGui::LabelText("VP", "%0.2f,%0.2f,%0.2f", result.x, result.y, result.z);

}

