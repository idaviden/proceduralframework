// POC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "POC.h"
#include "FileHeightmap.h"
#include "FaultFormation.h"
#include "PerlinNoise.h"
#include "Heightmask.h"
#include "Framework.h"
#include "Random.h"
#include "Vector3.h"

POC::POC(int p_width, int p_height) : Framework(p_width, p_height)
{

}


void POC::Init(){
	Framework::Init();

	//Temp
	/*
	FileHeightmap* aux = new FileHeightmap(1, Vector3<float>(0,0,0), 257, 257, "../POC/Content/Heightmaps/3.bmp");
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	/*
	Heightmask* mask = new Heightmask("../POC/Content/Heightmaps/mascara.bmp");
	aux->SetHeightMask(*mask);
	
	
	Random::Init();

	FaultFormation* aux = new FaultFormation(16, Vector3<float>(0,0,0), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/

	/*
	aux = new FaultFormation(16, Vector3<float>(512,0,512), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);

	aux = new FaultFormation(16, Vector3<float>(0,0,512), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	/*
	Random::Init();
	FaultFormation* aux = new FaultFormation(16, Vector3<float>(0,0,0), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	aux->m_mesh->CopyVertexFromHeightMap();
	aux->m_mesh->BuildVBOs();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	
	/*
	PerlinNoise* aux = new PerlinNoise(1, Vector3<float>(0,0,0), 100, 100, 31, 8, 0.5);
	aux->FillHeightMap();
	//aux->Normalize(255, 0);
	aux->m_mesh->CopyVertexFromHeightMap();
	aux->m_mesh->BuildVBOs();
	//aux->SetShader();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	

	PerlinNoise* aux;
	int tamanho_terreno = 100;

	for(int i=0; i<500; i+=tamanho_terreno){
		for(int j=0; j<500; j+=tamanho_terreno){
			aux = new PerlinNoise(1, Vector3<float>(i,0,j), tamanho_terreno, tamanho_terreno, 13, 1, 0.5);
			aux->FillHeightMap();
			aux->m_mesh->CopyVertexFromHeightMap();
			aux->m_mesh->BuildVBOs();
			aux->SetShader();
			m_sceneGraph.insert(m_sceneGraph.end(), aux);

		}


		

	}
	


}



