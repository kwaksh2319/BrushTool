#include"Framework.h"
#include"MeshCube.h"

MeshCube::MeshCube(Shader * shader)
	:Mesh(shader)
{
}

MeshCube::~MeshCube()
{
}

void MeshCube::Create()
{
	vector<MeshVertex> v;


	float w, h, d;
	w = h = d = 0.5f;
    //front
	v.push_back(MeshVertex(-w, -h, -d,0,0,-1));
	v.push_back(MeshVertex(-w, +h, -d, 0, 0, -1));
	v.push_back(MeshVertex(+w, +h, -d, 0, 0, -1));
	v.push_back(MeshVertex(+w, -h, -d, 0, 0, -1));

	//back

	v.push_back(MeshVertex(-w, -h, +d, 0, 0, +1));
	v.push_back(MeshVertex(+w, -h, +d, 0, 0, +1));
	v.push_back(MeshVertex(+w, +h, +d, 0, 0, +1));
	v.push_back(MeshVertex(-w, +h, +d, 0, 0, +1));

	//top
	v.push_back(MeshVertex(-w, +h, -d, 0, +1,0));
	v.push_back(MeshVertex(-w, +h, +d, 0, +1, 0));
	v.push_back(MeshVertex(+w, +h, +d, 0, +1,0));
	v.push_back(MeshVertex(+w, +h, -d, 0, +1, 0));

	//bottom
	v.push_back(MeshVertex(-w, -h, -d, 0, -1, 0));
	v.push_back(MeshVertex(+w, -h, -d, 0, -1, 0));
	v.push_back(MeshVertex(+w, -h, +d, 0, -1, 0));
	v.push_back(MeshVertex(-w, -h, +d, 0, -1, 0));

	//left
	v.push_back(MeshVertex(-w, -h, +d, -1, 0, 0));
	v.push_back(MeshVertex(-w, +h, +d, -1, 0, 0));
	v.push_back(MeshVertex(-w, +h, -d, -1, 0, 0));
	v.push_back(MeshVertex(-w, -h, -d, -1, 0, 0));

	//right
	v.push_back(MeshVertex(+w, -h, -d, +1, 0, 0));
	v.push_back(MeshVertex(+w, +h, -d, +1, 0, 0));
	v.push_back(MeshVertex(+w, +h, +d, +1, 0, 0));
	v.push_back(MeshVertex(+w, -h, +d, +1, 0, 0));


	vertices = new MeshVertex[v.size()];
	vertexCount = v.size();
	copy
	(
		v.begin(), v.end(),
		stdext::checked_array_iterator<MeshVertex*>(vertices, vertexCount)
	);
	indexCount = 36;
	this->indices = new UINT[indexCount]{
		0,1,2,0,2,3,//front
		4,5,6,4,6,7,//back
		8,9,10,8,10,11,//top
		12,13,14,12,14,15,//left
		16,17,18,16,18,19,//right
		20,21,22,20,22,23//bottom

	};
}
