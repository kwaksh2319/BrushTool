#include "stdafx.h"
#include "BrushToolDemo.h"
#include "Viewer/Freedom.h"
#include "Environment/Terrain.h"

void BrushToolDemo::Initialize()
{
	Context::Get()->GetCamera()->RotationDegree(0, 0, 0);
	Context::Get()->GetCamera()->Position(0, 0, -10);
	((Freedom*)Context::Get()->GetCamera())->Speed(100, 2);

	shader = new Shader(L"12_Terrain_GetHeight.fx");

	terrain = new Terrain(shader, L"Terrain/Gray256.png");
	terrain->BaseMap(L"Terrain/Dirt3.png");

	meshShader = new Shader(L"10_Mesh.fx");
	sphereBrush = new MeshSphere(meshShader, 10.0f);
	sphere = new MeshSphere(meshShader, 0.5f);
	sphere->Color(1, 0, 0, 1);
	sphereBrush->Color(0, 0, 1, 0.5f);
	
	
}

void BrushToolDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(terrain);
	SafeDelete(meshShader);
	SafeDelete(sphereBrush);
	SafeDelete(sphere);
}

void BrushToolDemo::Update()
{
	Vector3 position;
	Vector3 scale;
	Vector3 mousePoint;
	//mouse->Create();
	Mouse::Create();
	sphereBrush->Position(&mousePoint);

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
	sphereBrush->Scale(&scale);
	position.y = terrain->GetHeightPick(position) + scale.y*0.5f;
	sphere->Position(position);


	static Vector3 light = Vector3(-1, -1, 1);
	ImGui::SliderFloat3("Light", light, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(light);
	meshShader->AsVector("LightDirection")->SetFloatVector(light);




	terrain->Update();
}


void BrushToolDemo::Render()
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
	Vector3 picked = terrain->GetPickedPosition();
	string str = to_string(picked.x) + "," + to_string(picked.y) + "," + to_string(picked.z);
	Gui::Get()->RenderText(Vector2(10, 60), Color(1, 0, 0, 1), "Raycast:" + str);
	//terrain->Pass(1);
	sphere->Render();
	sphereBrush->Render();
	terrain->Render();

	ImGui::LabelText("VP", "%0.2f,%0.2f,%0.2f", result.x, result.y, result.z);

}

