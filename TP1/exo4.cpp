#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];
	int occurence[256];

	for(int i = 0; i < 256; i++)
	{
		occurence[i] = 0;
	}
  
	if(argc != 2) //si pas assez d'arguments
	{
		printf("Nombre de paramètre incorrecte Nb = %d \n", argc);
		printf("Usage: ImageIn.pgm \n"); 
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
			occurence[imIn[x][y]] += 1;
		}
	}

	for(int i = 0; i < 256; i++)
	{
		printf("%d %d\n", i, occurence[i]);
	}

	return 0;
}
