#include"stdafx.h"
#include"WorldDemo.h"

void WorldDemo::Initialize()
{
	shader = new Shader(L"04_world.fx");
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);

	vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = Vector3(+0.5f, +0.5f, 0.0f);



	vertices[0].Color = Color(1, 1, 1, 1);
	vertices[1].Color = Color(1, 0, 1, 1);
	vertices[2].Color = Color(1, 1, 0, 1);

	vertices[3].Color = Color(1, 1, 1, 1);
	vertices[4].Color = Color(0, 0, 1, 1);
	vertices[5].Color = Color(0, 0, 0, 1);


	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(VertexColor) * 6;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;


	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));

	D3DXMatrixIdentity(&world);


}

void WorldDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void WorldDemo::Update()
{
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void WorldDemo::Render()
{

	UINT stride = sizeof(VertexColor);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	

	//world
	{
		static Vector3 position = Vector3(0, 0, 0);
		ImGui::SliderFloat3("Position", position, -10, 10);
		world._41 = position.x;
		world._42 = position.y;
		world._43 = position.z;
	
		Color color = Color(1, 0, 0, 1);
		shader->AsMatrix("World")->SetMatrix(world);
		shader->AsVector("Color")->SetFloatVector(color);
		shader->Draw(0, 0, 6);
	}
}
