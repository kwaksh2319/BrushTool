#include "Framework.h"
#include "Viewport.h"

Viewport::Viewport(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	Set(width, height, x, y, minDepth, maxDepth);
}

Viewport::~Viewport()
{
	
}

void Viewport::Set(float width, float height, float x, float y, float minDepth, float maxDepth)
{
	viewport.TopLeftX = this->x = x;
	viewport.TopLeftY = this->y = y;
	viewport.Width = this->width = width;
	viewport.Height = this->height = height;
	viewport.MinDepth = this->minDepth = minDepth;
	viewport.MaxDepth = this->maxDepth = maxDepth;

	RSSetViewport();
}

void Viewport::Project(Vector3 * outPosition, Vector3 source, Matrix & w, Matrix & v, Matrix & p)
{
	Vector3 position = source;
	Matrix wvp = w * v*p;
	D3DXVec3TransformCoord(outPosition, &position, &wvp);

	outPosition->x = ((outPosition->x + 1.0f)*0.5f)*width + x;
	outPosition->y = ((-outPosition->y + 1.0f)*0.5f)*height + y;
	outPosition->z = ((-outPosition->z* (maxDepth - minDepth))) + minDepth;
}

void Viewport::Unproject(Vector3 * outPosition, Vector3 source, Matrix & w, Matrix & v, Matrix & p)
{
	Vector3 position = source;
	
	outPosition->x = ((position.x - x) / width)*2.0f - 1.0f;
	outPosition->y = (((position.y - y) / height)*2.0f - 1.0f)*-1.0f;
	outPosition->z = ((position.z - minDepth) / (maxDepth - minDepth));
	//outPosition->x = ((outPosition->x + 1.0f)*0.5f)*width + x;
	//outPosition->y = ((-outPosition->y + 1.0f)*0.5f)*height + y;
	//outPosition->z = ((-outPosition->z* (maxDepth - minDepth))) + minDepth;
	Matrix wvp = w * v*p;
	D3DXMatrixInverse(&wvp, NULL, &wvp);


	D3DXVec3TransformCoord(outPosition, outPosition, &wvp);
}

void Viewport::RSSetViewport()
{
	D3D::GetDC()->RSSetViewports(1, &viewport);
}