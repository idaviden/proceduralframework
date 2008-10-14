#include "stdafx.h"
#include "FileHeightmap.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
#include "FaultFormation.h"
#include "Random.h"
using namespace std;



FaultFormation::FaultFormation(int stepSize, Vector3<float> position, int width, int height, float minDelta, float maxDelta, int iterNumber, int filterStep, float filterValue) : StaticTerrain(stepSize, position, width, height){

	m_minDelta = minDelta;
	m_maxDelta = maxDelta;
	m_iterNumber = iterNumber;
	m_filterStep = filterStep;
	m_filterValue = filterValue;

	


}

void FaultFormation::FillHeightMap(){


	float delta;
	int x1, z1, x2, z2, dx1, dz1, dx2, dz2;

	for(int i=0; i<m_iterNumber; i++){
		delta = m_maxDelta - (((m_maxDelta - m_minDelta) * i) / m_iterNumber);

		x1 = Random::Next(0, m_width);
		z1 = Random::Next(0, m_height);

		do{
			x2 = Random::Next(0, m_width);
			z2 = Random::Next(0, m_height);

		}
		while(x1 == x2 || z1 == z2);

		dx1 = x2 - x1;
		dz1 = z2 - z1;
	

		for(x2 = 0; x2 < m_width; x2++){
			for(z2 = 0; z2 < m_height; z2++){
				dx2 = x2 - x1;
				dz2 = z2 - z1;

				if(dx2 * dz1 - dx1 * dz2 >= 0){

					m_heightMap[4 * x2 + 4 * z2 * m_width] += delta;


				}

			}

		}

		if(m_filterStep != 0 && (i % m_filterStep) == 0)
			FilterHeightMap();


	}


}

//Erosion

void FaultFormation::FilterHeightMap(){

    // Erode rows left to right.
    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 1; i < m_width; ++i)
        {
            m_heightMap[GetArrayPosition(i, j)] = m_filterValue * m_heightMap[GetArrayPosition(i-1, j)]
													+ (1 - m_filterValue) * m_heightMap[GetArrayPosition(i, j)];
        }
    }
 

    // Erode rows right to left.
    for (int j = 0; j < m_height; ++j)
    {
        for (int i = 0; i < m_width - 1; ++i)
        {
            m_heightMap[GetArrayPosition(i, j)] = m_filterValue * m_heightMap[i + 1 + j * m_width]
													+ (1 - m_filterValue) * m_heightMap[GetArrayPosition(i, j)];
        }
    }
 

    // Erode columns top to bottom.
    for (int j = 1; j < m_height; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            m_heightMap[GetArrayPosition(i, j)] = m_filterValue * m_heightMap[GetArrayPosition(i, j-1)]
											+ (1 - m_filterValue) * m_heightMap[GetArrayPosition(i, j)];
        }
    }

 

    // Erode columns bottom to top.
    for (int j = 0; j < m_height - 1; ++j)
    {
        for (int i = 0; i < m_width; ++i)
        {
            m_heightMap[GetArrayPosition(i, j)] = m_filterValue * m_heightMap[GetArrayPosition(i, j+1)]
												+ (1 - m_filterValue) * m_heightMap[GetArrayPosition(i, j)];
        }
    }



}
