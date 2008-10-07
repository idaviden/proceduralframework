#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace::std;


class Node{
private:
	vector<Node*> m_children;
	vector<Node*>::iterator m_iterator;
	
public:
	Node();
	virtual void Render();

};

#endif