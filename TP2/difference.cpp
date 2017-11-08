#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]){
	char cNomImgS[250], cNomImgD[250], cNomImgEcrite[250];
	int nH, nW, nTaille;

	if (argc != 4) {
		printf("Usage: ImageSeuillee.pgm ImageDilate.pgm ImageOut.pgm \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgS) ;
	sscanf (argv[2],"%s",cNomImgD);
	sscanf (argv[3],"%s",cNomImgEcrite);

	OCTET *ImgS, *ImgD, *ImgOut;

	lire_nb_lignes_colonnes_image_pgm(cNomImgS, &nH, &nW);
	nTaille = nH * nW;

	allocation_tableau(ImgS, OCTET, nTaille);
	lire_image_pgm(cNomImgS, ImgS, nH * nW);
	allocation_tableau(ImgD, OCTET, nTaille);
	lire_image_pgm(cNomImgD, ImgD, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);


	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			//si le pixel de ImgS et ImgD est blanc -> blanc
			if ((ImgS[i*nW+j] == 255) && (ImgD[i*nW+j] == 255)){
				ImgOut[i*nW+j]=255;
			}
			//si le pixel de ImgS et ImgD est noir -> blanc
			else if ((ImgS[i*nW+j] == 0) && (ImgD[i*nW+j] == 0)){
				ImgOut[i*nW+j]=255;
			}
			//si le pixel de ImgS est blanc et ImgD est noir -> noir
			else if ((ImgS[i*nW+j] == 0) && (ImgD[i*nW+j] == 255)){
				ImgOut[i*nW+j]=0;
			}
		}
	}

	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgS);
	free(ImgD);
	return 1;
}