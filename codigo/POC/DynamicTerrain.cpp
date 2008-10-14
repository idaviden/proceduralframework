#include "stdafx.h"
#include "DynamicTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
using namespace std;



DynamicTerrain::DynamicTerrain(int stepSize, Vector3<float> position, int width, int height) : Terrain(stepSize, m_position, width, height){


}

void DynamicTerrain::Render(){

	Terrain::Render();
}


