#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	int S1, S2, S3, S4;
  
	if(argc == 4) //si seuillage en 2
	{
		sscanf (argv[1],"%s",cNomImgLue) ;
		sscanf (argv[2],"%s",cNomImgEcrite);
		sscanf (argv[3],"%d",&S1);
	}
	else
	{
		if(argc == 5) //si seuillage en 3
		{
			sscanf (argv[1],"%s",cNomImgLue) ;
			sscanf (argv[2],"%s",cNomImgEcrite);
			sscanf (argv[3],"%d",&S1);
			sscanf (argv[4],"%d",&S2);
		}
		else
		{
			if(argc == 6) //si seuillage en 4
			{
				sscanf (argv[1],"%s",cNomImgLue) ;
				sscanf (argv[2],"%s",cNomImgEcrite);
				sscanf (argv[3],"%d",&S1);
				sscanf (argv[4],"%d",&S2);
				sscanf (argv[5],"%d",&S3);
			}
			else
			{
				printf("Nombre de paramètre incorrecte Nb = %d \n", argc);
				//printf("Usage: ImageIn.pgm ImageOut.pgm Seuil \n"); 
				return 1;
			}
		}
	}
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//height == hauteur
	//width == largeur

	for(int x = 0; x < imIn.getHeight(); ++x)
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			if(argc == 4)
			{
				if(imIn[x][y] < S1) 
					imOut[x][y] = 0;
				else 
					imOut[x][y] = 255;
			}
			if(argc == 5)
			{
				if(imIn[x][y] < S1) 
					imOut[x][y] = 0;
				if((imIn[x][y] >= S1) && (imIn[x][y] < S2))
					imOut[x][y] = 128;
				else 
					imOut[x][y] = 255;
			}
			if(argc == 6)
			{
				if(imIn[x][y] < S1) 
					imOut[x][y] = 0;
				if((imIn[x][y] >= S1) && (imIn[x][y] < S2))
					imOut[x][y] = 85;
				if((imIn[x][y] >= S2) && (imIn[x][y] < S3))
					imOut[x][y] = 170;
				else 
					imOut[x][y] = 255;
			}
		}
		
	imOut.save(cNomImgEcrite);
		

	
	
	///////////////////////////////////////// Exemple de création d'une image couleur
	ImageBase imC(50, 100, true);

	for(int y = 0; y < imC.getHeight(); ++y)
		for(int x = 0; x < imC.getWidth(); ++x)
		{
			imC[y*3][x*3+0] = 200; // R
			imC[y*3][x*3+1] = 0; // G
			imC[y*3][x*3+2] = 0; // B
		}
		
	imC.save("imC.ppm");
		



	///////////////////////////////////////// Exemple de création d'une image en niveau de gris
	ImageBase imG(50, 100, false);

	for(int y = 0; y < imG.getHeight(); ++y)
		for(int x = 0; x < imG.getWidth(); ++x)
			imG[y][x] = 50;

	imG.save("imG.pgm");




	ImageBase imC2, imG2;
	
	///////////////////////////////////////// Exemple lecture image couleur
	imC2.load("imC.ppm");
	///////////////////////////////////////// Exemple lecture image en niveau de gris
	imG2.load("imG.pgm");
	
	

	///////////////////////////////////////// Exemple de récupération d'un plan de l'image
	ImageBase *R = imC2.getPlan(ImageBase::PLAN_R);
	R->save("R.pgm");
	delete R;
	


	return 0;
}
