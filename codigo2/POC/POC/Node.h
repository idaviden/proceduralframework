#ifndef NODE_H
#define NODE_H


#include <vector>
using namespace::std;
#include "Vector3.h"



class Node{
public:
	vector<Node*> m_children;
	vector<Node*>::iterator m_iterator;

	Vector3<float> m_position;
	
public:
	Node();
	virtual void Render();
	virtual void AddNode(Node*);

};

#endif