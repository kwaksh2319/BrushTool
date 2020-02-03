#include"stdafx.h"
#include"RectDemo.h"

void RectDemo::Initialize()
{
	shader = new Shader(L"03_rect.fx");
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);

	vertices[3].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[4].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[5].Position = Vector3(+0.5f, +0.5f, 0.0f);



	vertices[0].Color = Color(1,1,1,1);
	vertices[1].Color = Color(1, 0, 1, 1);
	vertices[2].Color = Color(1, 1, 0, 1);

	vertices[3].Color = Color(1, 1, 1, 1);
	vertices[4].Color = Color(0, 0, 1, 1);
	vertices[5].Color = Color(0, 0, 0, 1);


	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(VertexColor) * 6;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;


	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));



}

void RectDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void RectDemo::Update()
{
}

void RectDemo::Render()
{
	UINT stride = sizeof(VertexColor);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWrite = false;

	ImGui::Checkbox("WireFrame", &bWrite);

	static Color color = Color(1, 1, 1, 1);
	ImGui::ColorEdit3("Color", color);
	shader->AsVector("Color")->SetFloatVector(color);

	shader->Draw(0, bWrite==false? 0:1, 6);

}
