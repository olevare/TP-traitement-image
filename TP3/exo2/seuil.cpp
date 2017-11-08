#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	char cNomImgLue[250], cNomImgEcrite[250];
	int S[3];
  
	if (argc != 3) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm\n"); 
		return 1;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int h = 0; h < imIn.getHeight(); ++h)
	{
		for(int w = 0; w < imIn.getWidth(); ++w)
		{
			for(int i=0;i<3;i++)
			{
				if(imIn[h*3][w*3+i] < 80)
					imOut[h*3][w*3+i] = 80;
				else
				{
					if(imIn[h*3][w*3+i] > 180)
						imOut[h*3][w*3+i] = 180;
					else
						imOut[h*3][w*3+i] = imIn[h*3][w*3+i];
				}
			}
		}
	}


	imOut.save(cNomImgEcrite);
		
	return 0;
}
