#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];
	char cNomImgEcrite[250];

	if (argc != 3) 
	{
		printf("Usage: ImageIn.ppm ImageOut.pgm\n"); 
		return 1;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), false);

	//height == hauteur
	//width == largeur

	for(int h = 0; h < imIn.getHeight(); h++)
		for(int w = 0; w < imIn.getWidth(); w++)
		{
			imOut[h][w] = (int)(0.3*(double)imIn[h*3][w*3+0] + 0.6*(double)imIn[h*3][w*3+1] + 0.1*(double)imIn[h*3][w*3+2]);
		}

	imOut.save(cNomImgEcrite);
	return 0;
}
