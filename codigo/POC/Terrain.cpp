#include "stdafx.h"
#include "StaticTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
#include "GL/glfw.h"
using namespace std;



Terrain::Terrain(int stepSize, Vector3<float> position, int width, int height){

	m_stepSize = stepSize;
	m_hasHeightmask = false;
	m_position = position;
	//m_heightmask = null;
	m_width = width;
	m_height = height;
	m_heightMap = new unsigned char[m_width * m_height * 4];


}

void Terrain::Render(){

	Node::Render();


	glBegin( GL_QUADS );
	
	int x_pixel, y_pixel;
	
	

	for(int x_pixel = 0; x_pixel < m_width - m_stepSize; x_pixel+= m_stepSize){
		for(int y_pixel = 0; y_pixel < m_height - m_stepSize; y_pixel+= m_stepSize){
			
			if(m_hasHeightmask){
				if(m_heightmask.GetBoolValue(x_pixel, y_pixel))
					RenderQuad(x_pixel, y_pixel);
			}
			else{
				RenderQuad(x_pixel, y_pixel);
			}
				
		}

	}



	glEnd();

}

int Terrain::GetHeight(int x, int y){

	int r = m_heightMap[(4*x + (4*y * m_height))];

	return r;

}

Vector3<float> Terrain::GetColor(int x, int y){

	float height = (GetHeight(x,y))/255.0f;

	return Vector3<float>(height, height, height);

}

int Terrain::GetArrayPosition(int x, int y){

	return 4 * x + 4 * y * m_width;

}

void Terrain::SetHeightMask(Heightmask heightmask){
	m_hasHeightmask = true;

	m_heightmask = heightmask;

}

void Terrain::RenderQuad(int x_pixel, int y_pixel){

	int x, y, z;
	Vector3<float> color;

	//Bottom left vertex
	x = x_pixel;
	y = GetHeight(x_pixel, y_pixel);
	z = y_pixel;
	
	color = GetColor(x, z);
	glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
	glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);

	//Top left vertex
	x = x_pixel;
	y = GetHeight(x_pixel, y_pixel + m_stepSize);
	z = y_pixel + m_stepSize;

	color = GetColor(x, z);
	glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
	glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);

	//Top right vertex
	x = x_pixel + m_stepSize;
	y = GetHeight(x_pixel + m_stepSize, y_pixel + m_stepSize);
	z = y_pixel + m_stepSize;

	color = GetColor(x, z);
	glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
	glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);

	//Bottom right
	x = x_pixel + m_stepSize; 
	y = GetHeight(x_pixel + m_stepSize, y_pixel ); 
	z = y_pixel;

	color = GetColor(x, z);
	glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
	glVertex3i(m_position.GetX() + x,m_position.GetY() +  y,m_position.GetZ() +  z);

}

