#include "CubeSphere.h"


CubeSphere::CubeSphere(){
	
	//FillVertices();
	//BuildVBOs();
	

}

CubeSphere::~CubeSphere(){
	glDeleteBuffersARB(1, &m_vboVertices);
	m_vboVertices =0;

	glDeleteBuffersARB(1, &m_vboColors);
	m_vboColors =0;

}


void CubeSphere::Render(){
	

    float bigSquareSize = 1.0;
	int num_divisions = 25;
    
	float littleSquareSize = bigSquareSize / num_divisions;
	
	for(int i=0; i<num_divisions; i++){
		for(int j=0; j<num_divisions; j++){
			glBegin(GL_LINE_LOOP);
				glVertex3f(0 + i*littleSquareSize,					0 + j*littleSquareSize,						0.0f);
				glVertex3f(littleSquareSize + i*littleSquareSize,	0 + j*littleSquareSize,						0.0f);
				glVertex3f(littleSquareSize + i*littleSquareSize,	littleSquareSize + j*littleSquareSize,		0.0f);
				glVertex3f(0 + i*littleSquareSize,					littleSquareSize + j*littleSquareSize,		0.0f);
			glEnd();

		}
		

	}

	
	
	
	
}

/*
void CubeSphere::FillVertices(){

}

void CubeSphere::BuildVBOs(){
	m_vboVertices = 0;


	// Generate And Bind The Vertex Buffer
	glGenBuffersARB( 1, &m_vboVertices );					// Get A Valid Name
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, m_vboVertices );			// Bind The Buffer
	// Load The Data
	glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof(m_vertices)*sizeof(float), m_vertices, GL_STATIC_DRAW_ARB );

}


void CubeSphere::Render(){
	
	//Call the parent
	Node::Render();
	

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vboVertices); //vertices
	glVertexPointer( 3, GL_FLOAT, 0, (char *) NULL);

	
	glDrawArrays( GL_LINES, 0, sizeof(m_vertices));


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

}
*/