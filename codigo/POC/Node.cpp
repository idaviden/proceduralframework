#include "stdafx.h"
#include "Node.h"
#include "GL/glew.h"
#include "gl/glfw.h"
#include <IL/il.h>
#include "glsl.h"


Node::Node(){


}

void Node::Render(){
	for (m_iterator = m_children.begin(); m_iterator != m_children.end(); m_iterator++ )
	{
		Node& node = **m_iterator;
		
		
		node.Render();
		
	}
}
