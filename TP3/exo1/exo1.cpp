#include "ImageBase.h"
#include <stdio.h>

using namespace std;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];
	char cNomImgEcrite[250];
	int lvl_temp[256];
	int lvl[256];
  
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
		lvl_temp[i] = 0;
		lvl[i] = 0;
	}

	
	for(int c = 0; c < imIn.getWidth(); ++c)
	{
		for(int l = 0; l < imIn.getHeight(); ++l)
		{
			lvl_temp[(int)imIn[l][c]] ++;
		}
	}


	int min;
	int max;

	int seuil = 1;

	for( min =  0 ; lvl_temp[min] < seuil; min++ ){}
	for( max = 255; lvl_temp[max] < seuil; max-- ){}

	int alpha;
	int beta;

	for(int x = 0; x < imIn.getHeight(); x++)
	{
		for(int y = 0; y < imIn.getWidth(); y++)
		{
			imOut[x][y] = (255. / double(max - min)) * (imIn[x][y] - min);
		}
	}

	imOut.save(cNomImgEcrite);

	//calcul alpha
	alpha = (-255 * min) / (max - min);
	beta = 255 / (max - min);

	double test = alpha + (beta * min);
	double test2 = alpha + (beta * max);


	printf("min = %d\n", min);
	printf("max = %d\n", max);
	printf("alpha = %d\n", alpha);
	printf("beta = %d\n", beta);
	return 0;
}
