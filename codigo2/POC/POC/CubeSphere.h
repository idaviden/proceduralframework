#ifndef CUBESPHERE_H
#define CUBESPHERE_H


#include <vector>
using namespace::std;
#include "Vector3.h"
#include "node.h"
#include "GL/glew.h"
#include "GL/glfw.h"



class CubeSphere : public Node{
	
	void Render();
	void FillVertices();
	void BuildVBOs();

	GLuint m_vboVertices;
	GLuint m_vboColors;
	GLfloat* m_vertices;
	GLfloat* m_colors;


public:
	CubeSphere();
	~ CubeSphere();
	

};

#endif