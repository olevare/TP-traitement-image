
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

	if (argc != 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgSeuil) ;
	sscanf (argv[3],"%s",cNomImgEcrite) ;

	
	//ImageBase imIn
	ImageBase imIn;
	imIn.load(cNomImgLue);


	ImageBase imSeuil(imIn.getWidth(), imIn.getHeight(), false);
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), false);

	//ouverture = erosion + dilatation

	//Erosion
	for(int x = 0; x < imIn.getHeight(); x++)
		for(int y = 0; y < imIn.getWidth(); y++){
			imSeuil[x][y] = 0;
		}


	for(int x = 0; x < imIn.getHeight(); x++)
		for(int y = 0; y < imIn.getWidth(); y++)
		{
			if(imIn[x][y] == 255){
				imSeuil[x][y] = 255;
				if(x > 0){
					imSeuil[x-1][y] = 255;
				}
				if(x < imIn.getHeight()-1){
					imSeuil[x+1][y] = 255;				
				}
				if(y > 0){
					imSeuil[x][y-1] = 255;
				}
				if(y < imIn.getWidth()-1){
					imSeuil[x][y+1] = 255;				
				}
			}
		}

	//dilatation
	for(int x = 0; x < imIn.getHeight(); x++)
		for(int y = 0; y < imIn.getWidth(); y++){
			imOut[x][y] = 255;
		}

	for(int x = 0; x < imSeuil.getHeight(); x++)
		for(int y = 0; y < imSeuil.getWidth(); y++)
		{
			if(imSeuil[x][y] == 0){
				imOut[x][y] = 0;
				if(x > 0){
					imOut[x-1][y] = 0;
				}
				if(x < imSeuil.getHeight()-1){
					imOut[x+1][y] = 0;				
				}
				if(y > 0){
					imOut[x][y-1] = 0;
				}
				if(y < imSeuil.getWidth()-1){
					imOut[x][y+1] = 0;				
				}
			}
		}

	imOut.save(cNomImgEcrite);

	return 0;
}
