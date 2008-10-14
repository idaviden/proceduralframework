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
	
	//Shaders
	if(m_shader){
		m_shader->begin();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture0);
		m_shader->setUniform1ui("tex0", m_texture0, 0);
		glDisable(GL_TEXTURE_2D);
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_texture1);
		m_shader->setUniform1ui("tex1", m_texture1, 1);
		glDisable(GL_TEXTURE_2D);
		
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_texture2);
		m_shader->setUniform1ui("tex2", m_texture2, 2);
		glDisable(GL_TEXTURE_2D);
		
		
		
		


	}	

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

	if (m_shader) m_shader->end();

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

void Terrain::SetShader(){
	
	cwc::glShaderManager SM;


	m_shader = SM.loadfromFile("multiTexture.vert","multiTexture.frag"); // load (and compile, link) from file

	

	if (m_shader==0) 
         std::cout << "Error Loading, compiling or linking shader\n";

	m_programObj = m_shader->GetProgramObject();

	LoadTexture("../POC/Content/Textures/dirt.png", m_texture0);
	LoadTexture("../POC/Content/Textures/grass.png", m_texture1);
	LoadTexture("../POC/Content/Textures/snow.png", m_texture2);


}


void Terrain::LoadTexture(char* end, GLuint& texture){
	//Load textures
	ILuint image_name;

	ilInit(); /* Initialization of DevIL */
	ilGenImages(1, &image_name); /* Generation of one image name */
	ilBindImage(image_name); /* Binding of image name */
	if(!ilLoadImage(end)){ /* Loading of image "image.jpg" */
		glfwTerminate();

	}
	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texture); /* Texture name generation */
    glBindTexture(GL_TEXTURE_2D, texture); /* Binding of texture name */
	
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), 
					ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	ilDeleteImages(1, &image_name); /* Because we have already copied image data into texture data
    we can release memory used by image. */

}

