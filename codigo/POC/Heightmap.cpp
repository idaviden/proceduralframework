#include "stdafx.h"
#include "Heightmap.h"
#include "Vector3.h"
#include "GL/glfw.h"
#include <IL/il.h>
#include <string>
#include <iostream>
using namespace std;



Heightmap::Heightmap(char* image_adress, int stepSize){

	m_stepSize = stepSize;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	// Generate a new image Id and bind it with the
	// current image.
	ILuint imgId;
	ilGenImages(1,&imgId);
	ilBindImage(imgId);

	if(!ilLoadImage(image_adress))
    {
        glfwTerminate();
		exit(GL_FALSE);
    }

	m_width = ilGetInteger(IL_IMAGE_WIDTH);
	m_height = ilGetInteger(IL_IMAGE_HEIGHT);
	
	m_imageData = new unsigned char[m_width * m_height * 4];
	ilCopyPixels(0, 0, 0, m_width, m_height, 1, IL_RGBA, IL_UNSIGNED_BYTE, m_imageData);
	
	// Finally, delete the DevIL image data.
	ilDeleteImage(imgId);
	
	/*
	for(int i=0; i<m_width * m_height * 4; i+=4){
		if(m_imageData[i+3]==255){
			int a = 0;
		}
	}
	*/


}

void Heightmap::Render(){

	Node::Render();
	/*
	glBegin( GL_TRIANGLES );          // Tell OpenGL that we want to draw a triangle
	glVertex3f( -5.0f, -4.0f, 0.0f ); // First corner of the triangle
	glVertex3f(  5.0f, -4.0f, 0.0f ); // Second corner of the triangle
	glVertex3f(  0.0f,  4.5f, 0.0f ); // Third corner of the triangle
	glEnd();
	*/


	glBegin( GL_QUADS );
	
	int x, y, z, x_pixel, y_pixel;
	Vector3<float> color;

	for(int x_pixel = 0; x_pixel < m_width - m_stepSize; x_pixel+= m_stepSize){
		for(int y_pixel = 0; y_pixel < m_height - m_stepSize; y_pixel+= m_stepSize){
			//Bottom left vertex
			x = x_pixel;
			y = GetHeight(x_pixel, y_pixel);
			z = y_pixel;
			
			color = GetColor(x, z);
			glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			glVertex3i(x, y, z);

			//Top left vertex
			x = x_pixel;
			y = GetHeight(x_pixel, y_pixel + m_stepSize);
			z = y_pixel + m_stepSize;

			color = GetColor(x, z);
			glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			glVertex3i(x, y, z);

			//Top right vertex
			x = x_pixel + m_stepSize;
			y = GetHeight(x_pixel + m_stepSize, y_pixel + m_stepSize);
			z = y_pixel + m_stepSize;

			color = GetColor(x, z);
			glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			glVertex3i(x, y, z);

			//Bottom right
			x = x_pixel + m_stepSize; 
			y = GetHeight(x_pixel + m_stepSize, y_pixel ); 
			z = y_pixel;

			color = GetColor(x, z);
			glColor4f(color.GetX(), color.GetY(), color.GetZ(), 1.0f );
			glVertex3i(x, y, z);

		}

	}



	glEnd();

}

int Heightmap::GetHeight(int x, int y){
	
	//x = (x % m_width);
	//y = (y % m_height);

	int r = m_imageData[(4*x + (4*y * m_height))];
	//int g = m_imageData[((x+1) + ((y+1) * m_height))*4];
	//int b  = m_imageData[((x+2) + ((y+2) * m_height))*4];

	return r;

}

Vector3<float> Heightmap::GetColor(int x, int y){

	int height = (GetHeight(x,y))/255.0f;

	return Vector3<float>(height, height, height);

}