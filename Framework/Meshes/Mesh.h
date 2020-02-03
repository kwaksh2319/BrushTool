#pragma once
class Mesh {

public:
	typedef VertexNormal MeshVertex;

public:
	Mesh(Shader*shader);
	virtual ~Mesh();
	void Render();

public:
	void Pass(UINT val) { pass = val; }
	Shader*GetShader() { return shader; }
	void Position(float x, float y, float z);
	void Position(Vector3& vec);
	void Position(Vector3* vec);

	void Rotation(float x, float y, float z);
	void Rotation(Vector3& vec);
	void Rotation(Vector3* vec);

	void RotationDegree(float x, float y, float z);
	void RotationDegree(Vector3& vec);
	void RotationDegree(Vector3*vec);

	void Scale(float x, float y, float z);
	void Scale(Vector3& vec);
	void Scale(Vector3*vec);

	void GetWorld(Matrix *mat);

	void Color(float r, float g, float b);
	void Color(float r, float g, float b,float a);
	void Color(D3DXCOLOR& val);

protected:
	virtual void Create() = 0;
	void CreateBuffer();

private:
	void UpdateWorld();


protected:
	MeshVertex* vertices;
	UINT* indices;

	UINT vertexCount;
	UINT indexCount;


private:

	UINT pass = 0;

	Vector3 position = Vector3(0, 0, 0);
	Vector3 scale = Vector3(1, 1, 1);
	Vector3 rotation = Vector3(0, 0, 0);

	Matrix world;

	Shader*shader;
	ID3D11Buffer*vertexBuffer = NULL;
	ID3D11Buffer*indexBuffer = NULL;
	D3DXCOLOR color = D3DXCOLOR(0, 0, 0, 1);
	
	ID3DX11EffectMatrixVariable*sWorld, *sView, *sProjection;
	ID3DX11EffectVectorVariable *sColor;



};