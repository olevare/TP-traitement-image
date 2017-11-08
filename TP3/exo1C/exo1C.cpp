#include "ImageBase.h"
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];
	char cNomImgEcrite[250];

	int lvl_R[256];
	int lvl_G[256];
	int lvl_B[256];
  
	if(argc != 3) //si pas assez d'arguments
	{
		printf("Nombre de paramètre incorrecte Nb = %d \n", argc);
		printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//height == hauteur
	//width == largeur

	//initialisation des tableau
	for(int i = 0; i < 256; ++i)
	{
		lvl_R[i] = 0;
		lvl_G[i] = 0;
		lvl_B[i] = 0;
	}

	
	for(int h = 0; h < imIn.getHeight(); ++h)
	{
		for(int w = 0; w < imIn.getWidth(); ++w)
		{

			lvl_R[imIn[h*3][w*3+0]] ++;
			lvl_G[imIn[h*3][w*3+1]] ++;
			lvl_B[imIn[h*3][w*3+2]] ++;
		}
	}



	int minR;
	int maxR;
	int minG;
	int maxG;
	int minB;
	int maxB;

	int seuil = 1;

	for( minR =  0 ; lvl_R[minR] < seuil; minR++ ){}
	for( maxR = 255; lvl_R[maxR] < seuil; maxR-- ){}

	for( minG =  0 ; lvl_G[minG] < seuil; minG++ ){}
	for( maxG = 255; lvl_G[maxG] < seuil; maxG-- ){}

	for( minB =  0 ; lvl_B[minB] < seuil; minB++ ){}
	for( maxB = 255; lvl_B[maxB] < seuil; maxB-- ){}

	int alphaR;
	int betaR;
	int alphaG;
	int betaG;
	int alphaB;
	int betaB;

	for(int h = 0; h < imIn.getHeight(); h++)
	{
		for(int w = 0; w < imIn.getWidth(); w++)
		{
			imOut[h*3][w*3+0] = (255./double(maxR-minR)) * ( imIn[h*3][w*3+0] - minR );
			imOut[h*3][w*3+1] = (255./double(maxG-minG)) * ( imIn[h*3][w*3+1] - minG );
			imOut[h*3][w*3+2] = (255./double(maxB-minB)) * ( imIn[h*3][w*3+2] - minB );

		}
	}

	imOut.save(cNomImgEcrite);

	//calcul alpha
	alphaR = (-255 * minR) / (maxR - minR);
	betaR = 255 / (maxR - minR);
	alphaG = (-255 * minG) / (maxG - minG);
	betaG = 255 / (maxG - minG);
	alphaB = (-255 * minB) / (maxB - minB);
	betaB = 255 / (maxB - minB);

	printf("alphaR = %d\n", alphaR);
	printf("betaR = %d\n", betaR);
	printf("alphaG = %d\n", alphaG);
	printf("betaG = %d\n", betaG);
	printf("alphaB = %d\n", alphaB);
	printf("betaB = %d\n", betaB);
	return 0;
}
