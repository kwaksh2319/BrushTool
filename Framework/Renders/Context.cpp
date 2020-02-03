#include "Framework.h"
#include "Context.h"
#include "Viewer/Viewport.h"
#include "Viewer/Perspective.h"
#include"./Viewer/Freedom.h"

Context* Context::instance = NULL;

Context * Context::Get()
{
	assert(instance != NULL);

	return instance;
}

void Context::Create()
{
	assert(instance == NULL);

	instance = new Context();
}

void Context::Delete()
{
	SafeDelete(instance);
}

Context::Context()
{
	D3DDesc desc = D3D::GetDesc();

	perspective = new Perspective(desc.Width, desc.Height);
	viewport = new Viewport(desc.Width, desc.Height);

	camera = new Freedom();
}

Context::~Context()
{
	SafeDelete(perspective);
	SafeDelete(viewport);
	SafeDelete(camera);
}

void Context::Update()
{
	camera->Update();
}

void Context::Render()
{


	
	viewport->RSSetViewport();
	
	
	string str = string("FPS:") + to_string(ImGui::GetIO().Framerate);
	Gui::Get()->RenderText(5, 5, 1, 1, 1, str);

	Vector3 camPos;
	camera->Position(&camPos);

	Vector3 camDir;
	camera->RotationDegree(&camDir);

	str = "camera(P):";
	str += to_string((int)camPos.x) + ","+to_string((int)camPos.y) + ","+to_string((int)camPos.z);
	Gui::Get()->RenderText(5,20,1, 1, 1, str);

	str = "camera(R):";
	str += to_string((int)camDir.x) + "," + to_string((int)camDir.y) + "," + to_string((int)camDir.z);
	Gui::Get()->RenderText(5, 35, 1, 1, 1, str);

}

Matrix Context::View()
{
	Matrix view;
	camera->GetMatrix(&view);
	return view;
}

D3DXMATRIX Context::Projection()
{
	D3DXMATRIX projection;
	perspective->GetMatrix(&projection);
	return projection;
}
