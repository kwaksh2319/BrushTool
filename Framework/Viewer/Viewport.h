#pragma once

class Viewport
{
public:
	Viewport(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);
	~Viewport();

	void RSSetViewport();
	void Set(float width, float height, float x = 0, float y = 0, float minDepth = 0, float maxDepth = 1);

	float GetWidth() { return width; }
	float GetHeight() { return height; }

	void Project(Vector3* outPosition, Vector3 source, Matrix&w, Matrix &v, Matrix &p);
	void Unproject(Vector3* outPosition, Vector3 source, Matrix&w, Matrix &v, Matrix &p);//raycast

private:
	float x, y;
	float width, height;
	float minDepth, maxDepth;

	D3D11_VIEWPORT viewport;
};