#include "stdafx.h"
#include "GridDemo.h"

void GridDemo::Initialize()
{
	shader = new Shader(L"04_World.fx");

	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];

	for (UINT z = 0; z <= height; z++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			UINT index = (width + 1) * z + x;

			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = 0.0f;
			vertices[index].Position.z = (float)z;
		}
	}

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	indexCount = width * height * 6;
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1) * z + x;
			indices[index + 1] = (width + 1) * (z + 1) + x;
			indices[index + 2] = (width + 1) * z + (x + 1);
			indices[index + 3] = (width + 1) * z + (x + 1);
			indices[index + 4] = (width + 1) * (z + 1) + x;
			indices[index + 5] = (width + 1) * (z + 1) + (x + 1);

			index += 6;
		}
	}

	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
		
	}

	
}

void GridDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

void GridDemo::Update()
{
	
	

	

	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}


void GridDemo::Render()
{
	Matrix temp = Context::Get()->View();
	ImGui::LabelText("test", "%0.2f, %0.2f, %0.2f", temp._41, temp._42, temp._43);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//World
	{
		Matrix world;
		D3DXMatrixIdentity(&world);
		shader->AsMatrix("World")->SetMatrix(world);		

		Color color = Color(0, 1, 0, 1);
		shader->AsVector("Color")->SetFloatVector(color);

		shader->DrawIndexed(0, 1, indexCount);
	}

}

