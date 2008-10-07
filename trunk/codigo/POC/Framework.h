#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "vector"
#include "Camera.h"
#include "Node.h"
using namespace::std;

class Framework{
private:
	int m_width;
	int m_height;
	
	vector<Node*> m_sceneGraph;
	vector<Node*>::iterator m_iterator;

	Camera* camera;

	bool m_isRunning;
	void DoUpdate();
	void DoRender();
	void GLConfig();

public:
	Framework(int, int);
	void Init();
	int Start();
	

};

#endif