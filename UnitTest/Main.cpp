#include "stdafx.h"
#include "Main.h"
#include "Systems/Window.h"
#include"VertexDemo.h"
#include"RectDemo.h"
#include"WorldDemo.h"
#include"IndexDemo.h"
#include"GridDemo.h"
#include"TerrainDemo.h"
#include"MeshDemo.h"
#include"TextureDemo.h"
#include"GetHeightDemo.h"
#include"VerticalDemoPick.h"
#include"ProjectionDemo.h"
//#include"RayCastDemo.h"
#include"BrushToolDemo.h"
void Main::Initialize()
{
	D3D11_RASTERIZER_DESC;
	Push(new BrushToolDemo);
	//Push(new RayCastDemo);
	//Push(new VerticalDemoPick);
	//Push(new ProjectionDemo);
	//Push(new MeshDemo);
	//Push(new TerrainDemo);
	//Push(new GridDemo);
//	Push(new IndexDemo);
	//Push(new worldDemo);
	//Push(new RectDemo);
	//Push(new VertexDemo);
}

void Main::Ready()
{
	


}

void Main::Destroy()
{
	for (IExecute* exe : executes)
	{
		exe->Destroy();
		SafeDelete(exe);
	}
}

void Main::Update()
{
	for (IExecute* exe : executes)
		exe->Update();
}

void Main::PreRender()
{
	for (IExecute* exe : executes)
		exe->PreRender();
}

void Main::Render()
{
	for (IExecute* exe : executes)
		exe->Render();
}

void Main::PostRender()
{
	for (IExecute* exe : executes)
		exe->PostRender();
}

void Main::ResizeScreen()
{
	for (IExecute* exe : executes)
		exe->ResizeScreen();
}

void Main::Push(IExecute * execute)
{
	executes.push_back(execute);

	execute->Initialize();
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	D3DDesc desc;
	desc.AppName = L"D3D Game";
	desc.Instance = instance;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.Handle = NULL;
	desc.Width = 1280;
	desc.Height = 720;
	desc.Background = Color(0.3f, 0.3f, 0.3f, 1.0f);
	//desc.Background = Color(0.0f, 1.0f, 0.0f, 0.0f);
	D3D::SetDesc(desc);

	Main* main = new Main();
	WPARAM wParam = Window::Run(main);

	SafeDelete(main);

	return wParam;
}