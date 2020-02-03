#include"stdafx.h"
#include"TextureDemo.h"
#include"Viewer/Freedom.h"
void TextureDemo::Initialize()
{
	Context::Get()->GetCamera()->Position(0, 0, -30);

	
	shader = new Shader(L"11_texture.fx");

	sTexture = shader->AsSRV("Texture");
	texture = new Texture(L"Box.png");

	VertexTexture vertices[4];
	vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
	vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
	vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);
	//UV:0 ~1
	/*
	vertices[0].Uv = Vector2(0.0f, 1.0f);
	vertices[1].Uv = Vector2(0.0f, 0.0f);
	vertices[2].Uv = Vector2(1.0f, 1.0f);
	vertices[3].Uv = Vector2(1.0f, 0.0f);
	*/
	//UV:0 ~0.5f
	/*
	vertices[0].Uv = Vector2(0.0f, 0.5f);
	vertices[1].Uv = Vector2(0.0f, 0.0f);
	vertices[2].Uv = Vector2(0.5f, 0.5f);
	vertices[3].Uv = Vector2(0.5f, 0.0f);
	*/
	//UV:0 ~2.0f
	
	vertices[0].Uv = Vector2(0.0f, 2.0f);
	vertices[1].Uv = Vector2(0.0f, 0.0f);
	vertices[2].Uv = Vector2(2.0f, 2.0f);
	vertices[3].Uv = Vector2(2.0f, 0.0f);
	
	UINT indices[6] = { 0,1,2,2,1,3 };


	//Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(VertexTexture) * 4;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subresource = { 0 };
		subresource.pSysMem = vertices;
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subresource, &vertexBuffer));
	}
	//index Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * 6;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA subresource = { 0 };
		subresource.pSysMem =indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subresource, &indexBuffer));

	}
}

void TextureDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void TextureDemo::Update()
{
	Matrix world;
	D3DXMatrixScaling(&world, 10, 10, 1);
	shader->AsMatrix("World")->SetMatrix(world);

	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void TextureDemo::Render()
{

	UINT stride = sizeof(VertexTexture);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	
	D3D::GetDC()->IASetIndexBuffer(indexBuffer,DXGI_FORMAT_R32_UINT,0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	

	sTexture->SetResource(texture->SRV());
	//address
	static UINT address = 0;
	ImGui::InputInt("Address", (int*)&address);
	address %= 4;
	shader->AsScalar("Address")->SetInt(address);
	//fiilter

	static UINT filter = 0;
	ImGui::InputInt("Filter", (int*)&filter);
	filter %= 3;
	shader->AsScalar("Filter")->SetInt(filter);

	shader->DrawIndexed(0, 2, 6);
	
//	D3D11_SAMPLER_DESC;

	//D3D11_SAMPLER_DESC desc;
	//ID3D11SamplerState *test;
    

}
