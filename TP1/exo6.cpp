#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	char cNomImgLue[250], cNomImgEcrite[250];
	int S[3];
  
	if (argc != 6) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm SeuilR SeuilG SeuilB \n"); 
		return 1;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	for(int i=0;i<3;i++)
	{sscanf (argv[i+3],"%d",&S[i]);}
	
	ImageBase imIn;
	imIn.load(cNomImgLue);

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
