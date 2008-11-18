#ifndef TERRAIN_H
#define TERRAIN_H

#include "node.h"
#include "Heightmask.h"
#include "Vector3.h"
#include "Mesh.h"

class Terrain : public Node{
protected:
	//void RenderQuad(int, int);
	//int GetArrayPosition(int, int);
	virtual void Render();

	vector<Node*> m_children;
	vector<Node*>::iterator m_iterator;
	

	
	int m_height;
	int m_width;
	int m_renderStepSize;
	bool m_hasHeightmask;
	Heightmask m_heightmask;

	


	//Shaders
	cwc::glShader *m_shader;
	GLuint m_programObj;

	//Textures
	GLuint m_texture0;
	GLuint m_texture1;
	GLuint m_texture2;

public:
	Terrain(int, Vector3<float>, int, int);
	~ Terrain();

	Vector3<float> m_position;
	//VBO
	Mesh* m_mesh;

	virtual void FillHeightMap() = 0;
	void SetHeightMask(Heightmask);
	//int GetHeight(int, int);
	//Vector3<float> GetColor(int, int);

	void SetShader();
	void LoadTexture(char*, GLuint&, GLuint);
	void Normalize(float, float);


};

#endif
