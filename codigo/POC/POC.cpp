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
	FileHeightmap* aux = new FileHeightmap(16, "../POC/Content/Heightmaps/3.bmp");
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);

	Heightmask* mask = new Heightmask("../POC/Content/Heightmaps/mascara.bmp");
	aux->SetHeightMask(*mask);
	*/
	/*
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

	aux = new FaultFormation(16, Vector3<float>(512,0,0), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	
	PerlinNoise* aux = new PerlinNoise(8, Vector3<float>(0,0,0), 1024, 1024, 1, 9, 0.75);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	


}


