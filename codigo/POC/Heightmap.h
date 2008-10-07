#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <vector>
#include "Node.h"
#include "Vector3.h"
#include "GL/glfw.h"
#include <IL/il.h>
using namespace::std;


class Heightmap : public Node{
private:
	int GetHeight(int, int);
	Vector3<float> GetColor(int, int);

	vector<Node*> m_children;
	vector<Node*>::iterator m_iterator;

	unsigned char* m_imageData;
	int m_height;
	int m_width;
	int m_stepSize;

	
public:
	Heightmap(char*, int);
	virtual void Render();


};

#endif