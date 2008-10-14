#ifndef TERRAIN_H
#define TERRAIN_H

#include "node.h"
#include "Heightmask.h"
#include "Vector3.h"

class Terrain : public Node{
protected:
	void RenderQuad(int, int);
	int GetArrayPosition(int, int);
	virtual void Render();

	vector<Node*> m_children;
	vector<Node*>::iterator m_iterator;
	Vector3<float> m_position;
	unsigned char* m_heightMap;
	int m_height;
	int m_width;
	int m_stepSize;
	bool m_hasHeightmask;
	Heightmask m_heightmask;

public:
	Terrain(int, Vector3<float>, int, int);
	virtual void FillHeightMap() = 0;
	void SetHeightMask(Heightmask);
	int GetHeight(int, int);
	Vector3<float> GetColor(int, int);


};

#endif
