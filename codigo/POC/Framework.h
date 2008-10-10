#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "vector"
#include "Camera.h"
#include "Node.h"
using namespace::std;

class Framework{

protected:
	int m_width;
	int m_height;
	
	vector<Node*> m_sceneGraph;
	vector<Node*>::iterator m_iterator;

	Camera* camera;

	bool m_isRunning;

	Framework(int, int);
	virtual void Init();
	void DoUpdate();
	void DoRender();
	void GLConfig();
	void Light();

public:
	virtual int Start();

};

#endif