#include"Framework.h"
#include"MeshGrid.h"

MeshGrid::MeshGrid(Shader * shader)
	:Mesh(shader)
{
}

MeshGrid::~MeshGrid()
{
}

void MeshGrid::Create()
{
	UINT countX = 11;
	UINT countZ = 11;

	float w = ((float)countX - 1) * 0.5f;
	float h = ((float)countZ - 1) * 0.5f;
      
	vector<MeshVertex> v;
	for (UINT z = 0; z < countZ; z++) {
		for (UINT x = 0; x < countX; x++) {
			MeshVertex vertex;
			vertex.Position = D3DXVECTOR3((float)x - w, 0, (float)z - h);
			vertex.Normal = D3DXVECTOR3(0, 1, 0);

			v.push_back(vertex);
		}
	}

	vertices = new MeshVertex[v.size()];
	vertexCount = v.size();
	copy(

		v.begin(),v.end(),
		stdext::checked_array_iterator<MeshVertex*>(vertices,vertexCount)
	);
	vector<UINT> indices;
	for (UINT z = 0; z < countZ-1; z++) {
		for (UINT x = 0; x < countX-1; x++) {
			indices.push_back(countX*z + x);
			indices.push_back(countX*(z+1) + x);
			indices.push_back(countX*z  + x+1);
			indices.push_back(countX*z + x + 1);
			indices.push_back(countX*(z + 1) + x);
			indices.push_back(countX*(z+1) + x+1);

		}
	}

	this->indices = new UINT[indices.size()];
	indexCount = indices.size();
	copy(indices.begin(),indices.end(),
		stdext::checked_array_iterator<UINT*>(this->indices,indexCount)
	);
}
