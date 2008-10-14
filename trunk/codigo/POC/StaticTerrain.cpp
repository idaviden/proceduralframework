#include "stdafx.h"
#include "StaticTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
using namespace std;



StaticTerrain::StaticTerrain(int stepSize, Vector3<float> position, int width, int height) : Terrain(stepSize, position, width, height){

	


}

void StaticTerrain::Render(){

	Terrain::Render();
}

