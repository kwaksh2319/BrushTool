#include"Framework.h"
#include"Mesh.h"

Mesh::Mesh(Shader * shader)
	:shader(shader)
{
	D3DXMatrixIdentity(&world);
	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");
	sColor= shader->AsVector("Color");
}

Mesh::~Mesh()
{
	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);

}

void Mesh::Render()
{
	if (vertexBuffer == NULL || indexBuffer == NULL) {
		Create();
		CreateBuffer();
	}


	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride,&offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sWorld->SetMatrix(world);
	sView->SetMatrix(Context::Get()->View());
	sProjection->SetMatrix(Context::Get()->Projection());
	sColor->SetFloatVector(color);
	shader->DrawIndexed(0, pass, indexCount);
}

void Mesh::Position(float x, float y, float z)
{
	Position(Vector3(x, y, z));
}

void Mesh::Position(Vector3 & vec)
{
	position = vec;
	UpdateWorld();
}

void Mesh::Position(Vector3 * vec)
{
	*vec = position;
}

void Mesh::Rotation(float x, float y, float z)
{
	Rotation(Vector3(x, y, z));
}

void Mesh::Rotation(Vector3 & vec)
{
	rotation = vec;
	UpdateWorld();
}

void Mesh::Rotation(Vector3 * vec)
{
	*vec = rotation;
}

void Mesh::RotationDegree(float x, float y, float z)
{
	RotationDegree(Vector3(x, y, z));
}

void Mesh::RotationDegree(Vector3 & vec)
{
	rotation = vec * Math::PI / 100.0f;
	UpdateWorld();
}

void Mesh::RotationDegree(Vector3 * vec)
{
	*vec = rotation * 100.0f / Math::PI;
}

void Mesh::Scale(float x, float y, float z)
{
	Scale(Vector3(x, y, z));
}

void Mesh::Scale(Vector3 & vec)
{
	scale = vec;
	UpdateWorld();
}

void Mesh::Scale(Vector3 * vec)
{
	*vec = scale;
}

void Mesh::GetWorld(Matrix * mat)
{
	memcpy(mat, &world, sizeof(Matrix));
}

void Mesh::Color(float r, float g, float b )
{
	Color(D3DXCOLOR(r, g, b, 1.0f));
}

void Mesh::Color(float r, float g, float b, float a)
{
	Color(D3DXCOLOR(r, g, b, a));
}

void Mesh::Color(D3DXCOLOR & val)
{
	color = val;
}

void Mesh::Create()
{
}

void Mesh::CreateBuffer()
{
	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(MeshVertex)*vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer));

	}
	//Create IndexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT)*indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer));

	}

}

void Mesh::UpdateWorld()
{
	Matrix S, R, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R*T;


}
