#pragma once
#include"Mesh.h"
class MeshCube :public Mesh {

public:
	MeshCube(Shader*shader);
	~MeshCube();

private:

	void Create() override;

};