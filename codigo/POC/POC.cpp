// POC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "POC.h"
#include "FileHeightmap.h"
#include "FaultFormation.h"
#include "Heightmask.h"
#include "Framework.h"
#include "Random.h"

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
	Random::Init();

	FaultFormation* aux = new FaultFormation(8, 1024, 1024, 0, 100, 10, 0, 0);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);

}


