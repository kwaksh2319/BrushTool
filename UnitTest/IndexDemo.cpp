#include"stdafx.h"
#include"IndexDemo.h"

void IndexDemo::Initialize()
{
	shader = new Shader(L"04_world.fx");
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);
	
	//Create Vertex buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;


		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));

		
	}
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;

	//Create IndexBuffer
	{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(UINT) * 6;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = indices;


	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));

	


	}
	
}

void IndexDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void IndexDemo::Update()
{
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void IndexDemo::Render()
{

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer,DXGI_FORMAT_R32_UINT,0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	

	//world
	{
		Matrix world;
		D3DXMatrixIdentity(&world);
		shader->AsMatrix("World")->SetMatrix(world);

	
		Color color = Color(1, 0, 0, 1);
	
		shader->AsVector("Color")->SetFloatVector(color);
		shader->DrawIndexed(0, 0, 6);
	}
}
