#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "ImageBase.h"

using namespace std;

struct point
{
	float x;
	float y;
	float z;
};

struct face
{
	point v1;
	point v2;
	point v3;
};

int tailleX;
int tailleY;
int tailleZ;

float sizeX;
float sizeY;
float sizeZ;

unsigned short inverserOctet(unsigned short octet)
{
	//merci google
	return (octet & 0xff) << 8 | ((octet & 0xff00) >> 8);
}

unsigned short getValue(unsigned short *buffer, int x, int y, int z)
{
	return inverserOctet(buffer[(z * tailleX * tailleY) + ((tailleY - y - 1) * tailleX) + x ]);
}

unsigned short getMin(unsigned short *buffer)
{
	unsigned short min = buffer[0];

	//on regarde tous les voxels de l'image
	for(int i = 0; i < (tailleX * tailleY * tailleZ); i++)
  	{
  		if(min > buffer[i])
  			min = buffer[i];
  	}

  	return min;
}

unsigned short getMax(unsigned short *buffer)
{
	unsigned short max = buffer[0];

	//on regarde tous les voxels de l'image
	for(int i = 0; i < (tailleX * tailleY * tailleZ); i++)
  	{
  		if(max < buffer[i])
  			max = buffer[i];
  	}

  	return max;
}

void MIP(unsigned short *buffer)
{
	int valeur;
	//height == hauteur
	//width == largeur
	ImageBase imOut(tailleX, tailleY, false);

	for(int i = 0; i < tailleX; i++)
	{
		for(int j = 0; j < tailleY; j++)
		{
			imOut[i][j] = 0;
			for(int k = 0; k < tailleZ; k++)
			{
				valeur = inverserOctet(getValue(buffer, i, j, k));
				if(valeur > imOut[i][j])
				{
					imOut[i][j] = valeur;
				}
			}
		}
	}
	imOut.save("MIP.pgm");
}

void AIP(unsigned short *buffer)
{
	int valeur;
	//height == hauteur
	//width == largeur
	ImageBase imOut(tailleX, tailleY, false);

	for(int i = 0; i < tailleX; i++)
	{
		for(int j = 0; j < tailleY; j++)
		{
			valeur = 0;
			for(int k = 0; k < tailleZ; k++)
			{
				valeur += inverserOctet(getValue(buffer, i, j, k));
			}

			imOut[i][j] = valeur / tailleZ;
		}
	}
	imOut.save("AIP.pgm");
}

void MinIP(unsigned short *buffer)
{
	int valeur;
	//height == hauteur
	//width == largeur
	ImageBase imOut(tailleX, tailleY, false);

	for(int i = 0; i < tailleX; i++)
	{
		for(int j = 0; j < tailleY; j++)
		{
			imOut[i][j] = 4000;
			for(int k = 0; k < tailleZ; k++)
			{
				valeur = inverserOctet(getValue(buffer, i, j, k));
				if((valeur < imOut[i][j]) && (valeur != 0))
				{
					imOut[i][j] = valeur;
				}
			}
		}
	}
	imOut.save("MinIP.pgm");
}











void ToString(ofstream &file, face &t)
{
	file << "facet normal 0 0 0" << endl;
	file << "outer loop"<< endl;
	file << "vertex " << t.v1.x << " " << t.v1.y << " " << t.v1.z << endl;
	file << "vertex " << t.v2.x << " " << t.v2.y << " " << t.v2.z << endl;
	file << "vertex " << t.v3.x << " " << t.v3.y << " " << t.v3.z << endl;
	file << "endloop " << endl;
	file << "endfacet " << endl;	
}

void MarchingCube(unsigned short *buffer, int threashold)
{
	std::ofstream file;
	file.open("out.stl");
	
	file << "solid test" << endl;
	
	//pour tous les voxels
	for(int i = 1; i < tailleX - 1; i++)
	{
		for(int j = 1; j < tailleY - 1; j++)
		{
			for(int k = 1; k < tailleZ - 1; k++)
			{
				//si le voxel est supérieur ou égal au seuil
				if(getValue(buffer, i, j, k) >= threashold)
				{
					//tableau des sommets du voxel
					vector<point> vertices;

					point v1;
					v1.x = (i - 0.5) * sizeX;
					v1.y = (j - 0.5) * sizeY;
					v1.z = (k - 0.5) * sizeZ;
					vertices.push_back(v1);

					point v2;
					v2.x = (i + 0.5) * sizeX;
					v2.y = (j - 0.5) * sizeY;
					v2.z = (k - 0.5) * sizeZ;
					vertices.push_back(v2);

					point v3;
					v3.x = (i + 0.5) * sizeX;
					v3.y = (j + 0.5) * sizeY;
					v3.z = (k - 0.5) * sizeZ;
					vertices.push_back(v3);

					point v4;
					v4.x = (i - 0.5) * sizeX;
					v4.y = (j + 0.5) * sizeY;
					v4.z = (k - 0.5) * sizeZ;
					vertices.push_back(v4);

					point v5;
					v5.x = (i - 0.5) * sizeX;
					v5.y = (j - 0.5) * sizeY;
					v5.z = (k + 0.5) * sizeZ;
					vertices.push_back(v5);

					point v6;
					v6.x = (i + 0.5) * sizeX;
					v6.y = (j - 0.5) * sizeY;
					v6.z = (k + 0.5) * sizeZ;
					vertices.push_back(v6);

					point v7;
					v7.x = (i + 0.5) * sizeX;
					v7.y = (j + 0.5) * sizeY;
					v7.z = (k + 0.5) * sizeZ;
					vertices.push_back(v7);

					point v8;
					v8.x = (i - 0.5) * sizeX;
					v8.y = (j + 0.5) * sizeY;
					v8.z = (k + 0.5) * sizeZ;
					vertices.push_back(v8);

					//on check les 6 voxels adjacent
					if(getValue(buffer, i - 1, j, k) < threashold)
					{			
						face t1;
						t1.v1 = vertices[0];
						t1.v2 = vertices[3];
						t1.v3 = vertices[7];

						face t2;
						t2.v1 = vertices[7];
						t2.v2 = vertices[4];
						t2.v3 = vertices[0];

						ToString(file, t1);
						ToString(file, t2);
					}

					if(getValue(buffer, i + 1, j, k) < threashold)
					{				
						face t1;
						t1.v1 = vertices[2];
						t1.v2 = vertices[6];
						t1.v3 = vertices[5];

						face t2;
						t2.v1 = vertices[5];
						t2.v2 = vertices[1];
						t2.v3 = vertices[2];

						ToString(file, t1);
						ToString(file, t2);
					}

					if(getValue(buffer, i, j - 1, k) < threashold)
					{					
						face t1;
						t1.v1 = vertices[0];
						t1.v2 = vertices[1];
						t1.v3 = vertices[5];

						face t2;
						t2.v1 = vertices[5];
						t2.v2 = vertices[4];
						t2.v3 = vertices[0];

						ToString(file, t1);
						ToString(file, t2);
					}

					if(getValue(buffer, i, j + 1, k) < threashold)
					{				
						face t1;
						t1.v1 = vertices[7];
						t1.v2 = vertices[6];
						t1.v3 = vertices[2];

						face t2;
						t2.v1 = vertices[2];
						t2.v2 = vertices[3];
						t2.v3 = vertices[7];

						ToString(file, t1);
						ToString(file, t2);	
					}

					if(getValue(buffer, i, j, k - 1) < threashold)
					{				
						face t1;
						t1.v1 = vertices[0];
						t1.v2 = vertices[1];
						t1.v3 = vertices[2];

						face t2;
						t2.v1 = vertices[2];
						t2.v2 = vertices[3];
						t2.v3 = vertices[0];

						ToString(file, t1);
						ToString(file, t2);
					}

					if(getValue(buffer, i, j, k + 1) < threashold)
					{				
						face t1;
						t1.v1 = vertices[4];
						t1.v2 = vertices[5];
						t1.v3 = vertices[6];

						face t2;
						t2.v1 = vertices[6];
						t2.v2 = vertices[7];
						t2.v3 = vertices[4];

						ToString(file, t1);
						ToString(file, t2);
					}
				}
			}
		}
	}
	
	file << "endsolid test";
	
	file.close();
}



int main(int argc, char const *argv[])
{
	tailleX = 512;
	tailleY = 512;
	tailleZ = 48;

	sizeX = 0.4570;
	sizeY = 0.4570;
	sizeZ = 3;

	int taille = tailleX * tailleY * tailleZ;

	unsigned short *buffer = new unsigned short[taille];

	//on ouvre le fichier
	//FILE *image = fopen("images/engine.256x256x128.1x1x1.img", "rb");
	FILE *image = fopen("images/manixSansIV.512x512x48.0.4570x0.4570x3.0.img", "rb");
	//FILE *image = fopen("images/statueLeg.341x341x93.1.0x1.0x4.0.img", "rb");
	//FILE *image = fopen("images/whatisit.208x208x123.1.0x1.0x1.0.img", "rb");


	//si on a bien ouvert l'image
 	if (image != NULL)
  	{
  		//on copie l'image
  		fread(buffer, sizeof(unsigned short), taille, image);

  		//on ferme le fichier
  		fclose (image);
  	}

  	MarchingCube(buffer, 1100);

	return 0;
}
