#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	char cNomImgLue[250], cNomImgEcrite[250];
	int S[3];
	int lvl_R = 0;
	int lvl_G = 0;
	int lvl_B = 0;
  
	if (argc != 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
		return 1;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	for(int x = 0; x < imIn.getHeight(); ++x)
	{
		for(int y = 0; y < imIn.getWidth(); ++y)
		{
			lvl_R += imIn[x*3][y*3];
			lvl_G += imIn[x*3][y*3+1];
			lvl_B += imIn[x*3][y*3+2];
		}
	}

	int taille = imIn.getHeight() * imIn.getWidth();

	lvl_R = lvl_R / taille;
	lvl_G = lvl_G / taille;
	lvl_B = lvl_B / taille;

	S[0] = lvl_R;
	S[1] = lvl_G;
	S[2] = lvl_B;

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int h = 0; h < imIn.getHeight(); ++h)
		for(int w = 0; w < imIn.getWidth(); ++w)
			for(int i=0;i<3;i++)
				if(imIn[h*3][w*3+i] < S[i])
					imOut[h*3][w*3+i] = 0;
				else
					imOut[h*3][w*3+i] = 255;

	imOut.save(cNomImgEcrite);
		
	return 0;
}
