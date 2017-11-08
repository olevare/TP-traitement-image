#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille;

	if (argc != 3) {
		printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	OCTET *ImgIn, *ImgOut, *ImgInt;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgInt, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);

	//OUVERTURE = Erosion puis Dilatation


	//erosion
	/*for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgIn[i*nW+j] == 255){
				ImgInt[i*nW+j]=255;			//pixel central
				ImgInt[i*nW+j+1]=255;		//pixel de droite
				ImgInt[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//dilatation
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			ImgOut[i*nW+j]=255;
		}
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt[i*nW+j] == 0){
				ImgOut[i*nW+j]=0;			//pixel central
				ImgOut[i*nW+j+1]=0;			//pixel de droite
				ImgOut[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgOut[(i-1)*nW+j]=0;	//pixel du dessus
					ImgOut[(i+1)*nW+j]=0; 	//pixel du dessous
				}
			}
		}
	}*/

		//erosion Image 256 niveaux de gris
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgIn[i*nW+j] > 128){
				ImgInt[i*nW+j]=ImgIn[i*nW+j];			//pixel central
				ImgInt[i*nW+j+1]=ImgIn[i*nW+j];		//pixel de droite
				ImgInt[i*nW+j-1]=ImgIn[i*nW+j];		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt[(i-1)*nW+j]=ImgIn[i*nW+j];	//pixel du dessus
					ImgInt[(i+1)*nW+j]=ImgIn[i*nW+j]; //pixel du dessous
				}
			}
			else {
				ImgInt[i*nW+j]=ImgIn[i*nW+j];
			}
		}
	}
	//dilatation Image 256 niveaux de gris
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt[i*nW+j] < 128){
				ImgOut[i*nW+j]=ImgInt[i*nW+j];			//pixel central
				ImgOut[i*nW+j+1]=ImgInt[i*nW+j];			//pixel de droite
				ImgOut[i*nW+j-1]=ImgInt[i*nW+j];			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgOut[(i-1)*nW+j]=ImgInt[i*nW+j];	//pixel du dessus
					ImgOut[(i+1)*nW+j]=ImgInt[i*nW+j];	//pixel du dessous
				}
			}
			else {
				ImgOut[i*nW+j]=ImgInt[i*nW+j];
			}
		}
	}
	



	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	free(ImgInt);
	return 1;

}
