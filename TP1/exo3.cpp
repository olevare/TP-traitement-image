#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], Endroit;
	int Indice;
  
	if(argc != 4) //si pas assez d'arguments
	{
		printf("Nombre de paramètre incorrecte Nb = %d \n", argc);
		printf("Usage: ImageIn.pgm L/C NumLigne/NumColonne \n"); 
		return 1;
	}
		sscanf (argv[1],"%s",cNomImgLue) ;
		sscanf (argv[2],"%s",&Endroit);
		sscanf (argv[3],"%d",&Indice);
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//height == hauteur
	//width == largeur

	if((Endroit == 'L') || (Endroit == 'l'))
	{
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			printf("%d %d\n", y, imIn[Indice][y]);
		}
	}
	else
	{
		if((Endroit == 'C') || (Endroit == 'c'))
		{
			for(int x = 0; x < imIn.getHeight(); ++x)
			{
				printf("%d %d\n", x, imIn[x][Indice]);
			}
		}
	}

	return 0;
}
