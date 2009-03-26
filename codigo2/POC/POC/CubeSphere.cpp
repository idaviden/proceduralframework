#include "CubeSphere.h"
#include <iostream>


CubeSphere::CubeSphere(Vector3<float> position, float size, int num_divisions){
	
	m_size = size;
	//m_numDivisions = 1;

	m_vboMesh = new VBO();
	
	for(int i=0; i<1; i++){
		m_faces[i] = new Square(m_vboMesh, position, size);
	}

	

	m_faces[0]->SplitSquareIn4(m_vboMesh);
	//m_faces[0]->m_squares[0]->SplitSquareIn4(m_numDivisions);

	

	//Fill the arrays with the new data
	/*
	for(int i=0; i<1; i++){
		m_faces[i]->FillArray(m_vboMesh);
	}
	*/

	m_vboMesh->FillBuffer();

	
	

}

CubeSphere::~CubeSphere(){
	m_vboMesh->DeleteBuffer();

	//glDeleteBuffersARB(1, &m_vboColors);
	//m_vboColors =0;

}




void CubeSphere::Render(){
	
	//Call the parent
	Node::Render();

	m_vboMesh->Render();



	
	

}
