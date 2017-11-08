#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];
	char cNomImgSeuil[250];
	char cNomImgEcrite[250];

	if (argc != 4) 
	{
		printf("Usage: ImageIn.ppm ImageSeuil.pgm ImageOut.ppm\n"); 
		return 1;
	}

	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgSeuil);
	sscanf (argv[3],"%s",cNomImgEcrite);
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imSeuil;
	imSeuil.load(cNomImgSeuil);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//height == hauteur
	//width == largeur
	
	for(int x = 1; x < imIn.getHeight() -1; x++)
	{
		for(int y = 1; y < imIn.getWidth() -1; y++)
		{
			if(imSeuil[x][y] == 255)
			{
			imOut[x*3][y*3] = (imIn[(x-1)*3][(y-1)*3] + imIn[(x-1)*3][y*3] + imIn[(x-1)*3][(y+1)*3] + imIn[x*3][(y-1)*3] + imIn[x*3][y*3] + imIn[x*3][(y+1)*3] + imIn[(x+1)*3][(y-1)*3] + imIn[(x+1)*3][y*3] + imIn[(x+1)*3][(y+1)*3])/9;
			imOut[x*3][y*3+1] = (imIn[(x-1)*3][(y-1)*3+1] + imIn[(x-1)*3][y*3+1] + imIn[(x-1)*3][(y+1)*3+1] + imIn[x*3][(y-1)*3+1] + imIn[x*3][y*3+1] + imIn[x*3][(y+1)*3+1] + imIn[(x+1)*3][(y-1)*3+1] + imIn[(x+1)*3][y*3+1] + imIn[(x+1)*3][(y+1)*3+1])/9;
			imOut[x*3][y*3+2] = (imIn[(x-1)*3][(y-1)*3+2] + imIn[(x-1)*3][y*3+2] + imIn[(x-1)*3][(y+1)*3+2] + imIn[x*3][(y-1)*3+2] + imIn[x*3][y*3+2] + imIn[x*3][(y+1)*3+2] + imIn[(x+1)*3][(y-1)*3+2] + imIn[(x+1)*3][y*3+2] + imIn[(x+1)*3][(y+1)*3+2])/9;
			}
			else
			{
				imOut[x*3][y*3] = imIn[x*3][y*3];
				imOut[x*3][y*3+1] = imIn[x*3][y*3+1];
				imOut[x*3][y*3+2] = imIn[x*3][y*3+2];
			}
		}
	}

	imOut.save(cNomImgEcrite);
	return 0;
}
