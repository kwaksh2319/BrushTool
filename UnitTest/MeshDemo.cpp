#include "stdafx.h"
#include "MeshDemo.h"

#include"Environment/Terrain.h"
#include"Viewer/Freedom.h"
void MeshDemo::Initialize()
{

	Context::Get()->GetCamera()->RotationDegree(23, 0, 0);
	Context::Get()->GetCamera()->Position(0, 32, -67);
	((Freedom*)Context::Get()->GetCamera())->Speed(40, 2);// down casting 
	shader = new Shader(L"10_mesh.fx");
	//terrain = new Terrain(shader,L"Terrain/Red256.png");
    
	grid = new MeshGrid(shader);
	grid->Scale(20, 1, 20);
	grid->Color(1, 1, 1);
	//grid->Pass(1);

	cube = new MeshCube(shader);
	cube->Position(0,5,0);
	cube->Scale(20, 10, 20);
	cube->Color(0.54f, 0.01f, 0.01f);

	for (UINT i = 0; i < 5; i++) {
		cylinder[i * 2] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2]->Position(-30, 6, -15.0f + (float)i*15.0f);
		cylinder[i * 2]->Scale(5, 5, 5);
		cylinder[i * 2]->Color(0.53f, 0.55f, 0.55f);


		cylinder[i * 2+1] = new MeshCylinder(shader, 0.5f, 3.0f, 20, 20);
		cylinder[i * 2+1]->Position(30, 6, -15.0f + (float)i*15.0f);
		cylinder[i * 2+1]->Scale(5, 5, 5);
		cylinder[i * 2+1]->Color(0.53f, 0.55f, 0.55f);



		sphere[i * 2] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2]->Position(-30, 15.5f, -15.0f + (float)i*15.0f);
		sphere[i * 2]->Scale(5, 5, 5);
		sphere[i * 2]->Color(0.89f, 0.35f, 0.13f);
	

		sphere[i * 2+1] = new MeshSphere(shader, 0.5f, 20, 20);
		sphere[i * 2+1]->Position(30, 15.5f, -15.0f + (float)i*15.0f);
		sphere[i * 2+1]->Scale(5, 5, 5);
		sphere[i * 2+1]->Color(0.62f, 0.78f, 0.87f);
	}

	

}

void MeshDemo::Destroy()
{
	SafeDelete(shader);
	SafeDelete(grid);
	SafeDelete(cube);
	for (MeshCylinder*cld : cylinder)
		SafeDelete(cld);

	for(MeshSphere*spr:sphere)
		SafeDelete(spr);
}

void MeshDemo::Update()
{
	


}


void MeshDemo::Render()
{
	grid->Render();

	cube->Render();
	for (MeshCylinder*cld : cylinder)
		cld->Render();

	for (MeshSphere*spr : sphere)
		spr->Render();
}

