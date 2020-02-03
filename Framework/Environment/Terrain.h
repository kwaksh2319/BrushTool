#pragma once
class Terrain {
public:
	typedef VertexTextureNormal TerrainVertex;
public:
	Terrain(Shader*shader,wstring heightFile);
	~Terrain();

	void Update();
	void Render();

	void Pass(UINT val) { pass = val; }
	void BaseMap(wstring file);
	float GetHeight(Vector3& position);
	float GetHeightPick(Vector3& position);
	Vector3 GetPickedPosition();
private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateNormalData();
	void CreateBuffer();
private:
	
	UINT pass = 0;
	Shader*shader;
	Texture*heightMap;
	Matrix world;

	UINT width;//= 128;
	UINT height; //= 128;

	UINT vertexCount;
	TerrainVertex * vertices;
	ID3D11Buffer *vertexBuffer;

	UINT indexCount;
	UINT *indices;
	ID3D11Buffer *indexBuffer;
	Texture* baseMap = NULL;
	ID3DX11EffectShaderResourceVariable* sBaseMap;
	
};