#include "stdafx.h"
#include "StaticTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include "PerlinNoise.h"
#include "math.h"
#include <IL/il.h>
#include <string>
#include <iostream>
using namespace std;



PerlinNoise::PerlinNoise(int renderStepSize, Vector3<float> position, int width, int height, int seed, int octaves, float persistence) : DynamicTerrain(renderStepSize, position, width, height){

	m_hasHeightmask = false;

	m_octaves = octaves;
	m_persistence = persistence;
	m_seed = seed;
	//m_heightmask = null;


}

float PerlinNoise::CosineInterpolation(float a, float b, float x){
	float ft = x * 3.1415927;
	float f = (1 - cos(ft)) * 0.5f;

	return a * (1 - f) + b * f;

}

float PerlinNoise::GetNoise(int i){
	i = (i << 13) ^ i;
	return (1.0f - ((i * (i * i * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0f);
}

void PerlinNoise::FillHeightMap(){


	
	int x_pixel, y_pixel;
	float freq, amp;
	float xf, tx, fracx;
	float zf, tz, fracz;

	float v1, v2, v3, v4;
	float i1, i2, total;
	
	
	for(int x_pixel = 0; x_pixel < m_width; x_pixel++){
		for(int y_pixel = 0; y_pixel < m_height; y_pixel++){
			
			total = 0.0f;

			//For each octave
			for(int i=0; i < m_octaves; i++){

				xf = ((float)x_pixel + m_position.GetX()) / (float)m_width;
				zf = ((float)y_pixel + m_position.GetZ()) / (float)m_height;


				//Calculate frequency and amplitude
				freq = pow(2.0, i);
				amp = pow(m_persistence, i);

				//Calculate x, z noise coordinates
				tx = xf * freq;
				tz = zf * freq;

				//Calculate the fractions of x and z
				fracx = tx - (int)tx;
				fracz = tz - (int)tz;

				//Get noise per octave for the four points
				v1 = GetNoise((int)tx + (int)tz * 57 + m_seed);
				v2 = GetNoise((int)tx + 1 + (int)tz * 57 + m_seed);
				v3 = GetNoise((int)tx + ((int)tz + 1) * 57 + m_seed);
				v4 = GetNoise((int)tx + 1 + ((int)tz + 1) * 57 + m_seed);

				//Smooth noise in the x axis
				i1 = CosineInterpolation(v1, v2, fracx);
				i2 = CosineInterpolation(v3, v4, fracx);

				//Smooth in the z axis
				total += CosineInterpolation(i1, i2, fracz) * amp;
			}

			//m_heightMap[GetArrayPosition(x_pixel, y_pixel)] += total * 50.0f;

			m_mesh->AddHeight(x_pixel, y_pixel, total * 50.0f);
		}
	}
}
