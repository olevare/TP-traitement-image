#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250];
	char cNomImgEcrite[250];

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	int lvl[256];
	double densite_proba[256];
	double repartition[256];

	double Ta[256];
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for(int i = 0; i < 256; ++i)
	{
		lvl[i] = 0;
		repartition[i] = 0.;
		Ta[i] = 0;
	}

	for(int h = 0; h < imIn.getHeight(); ++h)
		for(int w = 0; w < imIn.getWidth(); ++w)
		{
			lvl[(int)imIn[h][w]] ++;
		}


	int lvl_som = 0;
	for(int i = 0; i < 256; ++i)
			lvl_som += lvl[i];

	for(int i = 0; i < 256; ++i)
		densite_proba[i] = (double)lvl[i] / (double)lvl_som;

	for(int i = 0; i < 256; ++i)
	{
		for(int j = i; j < 256; ++j)
			repartition[j] += densite_proba[i];
	}


	for(int h = 0; h < imIn.getHeight(); ++h)
		for(int w = 0; w < imIn.getWidth(); ++w)
		{
			imOut[h][w] = 255 * repartition[imIn[h][w]] ;
		}

	imOut.save(cNomImgEcrite);


	for(int i = 0; i < 256; ++i)
		cout << i << " " << densite_proba[i] << endl;

	return 0;
}
