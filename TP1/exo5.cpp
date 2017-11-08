#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];

	int lvl_R[256];
	int lvl_G[256];
	int lvl_B[256];

	for(int i = 0; i < 256; i++)
	{
		lvl_R[i] = 0;
		lvl_G[i] = 0;
		lvl_B[i] = 0;
	}
  
	if(argc != 2) //si pas assez d'arguments
	{
		printf("Nombre de paramètre incorrecte Nb = %d \n", argc);
		printf("Usage: ImageIn.ppm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//height == hauteur
	//width == largeur

	for(int x = 0; x < imIn.getHeight(); ++x)
	{
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			lvl_R[imIn[x*3][y*3+0]] += 1;
			lvl_G[imIn[x*3][y*3+1]] += 1;
			lvl_B[imIn[x*3][y*3+2]] += 1;
		}
	}

	for(int i = 0; i < 256; i++)
	{
		printf("%d %d %d %d\n", i, lvl_R[i], lvl_G[i], lvl_B[i]);
	}

	return 0;
}
