#include"stdafx.h"
#include"VertexDemo.h"

void VertexDemo::Initialize()
{
	shader = new Shader(L"02_Vertex.fx");
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(+0.0f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);


	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 3;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;


	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));



}

void VertexDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void VertexDemo::Update()
{
}

void VertexDemo::Render()
{
	

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	static bool bWrite = false;
	ImGui::Checkbox("WireFrame", &bWrite);
	shader->Draw(0, bWrite==false? 0:1, 3);

}
