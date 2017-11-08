#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille, nR, nG, nB, S;

	if (argc != 3) {
		printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);

	OCTET *ImgIn, *ImgOut;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille3);

	cout << nTaille3;

	for (int i=3; i < nTaille3-3; i+=3){
		nR = ImgIn[i];
		nG = ImgIn[i+1];
		nB = ImgIn[i+2];
		if (nR == 255){
			ImgOut[i]=255;				//pixel central
			ImgOut[i+3]=255;			//pixel de droite
			ImgOut[i-3]=255;			//pixel de gauche
			if (i > (nW*3) && i < (nTaille3-(nW*3))){
				ImgOut[i+(nW*3)]=255;		//pixel du dessus
				ImgOut[i-(nW*3)]=255; //pixel du dessous
			}
		}
		if(nG==255){
			ImgOut[i+1]=255;				//pixel central
			ImgOut[i+4]=255;			//pixel de droite
			ImgOut[i-2]=255;			//pixel de gauche
			if (i > (nW*3) && i < (nTaille3-(nW*3))){
				ImgOut[i+1+(nW*3)]=255;		//pixel du dessus
				ImgOut[i+1-(nW*3)]=255; //pixel du dessous
			}
		}
		if(nB == 255){
			ImgOut[i+2]=255;				//pixel central
			ImgOut[i+5]=255;			//pixel de droite
			ImgOut[i-1]=255;			//pixel de gauche
			if (i > (nW*3) && i < (nTaille3-(nW*3))){
				ImgOut[i+2+(nW*3)]=255;		//pixel du dessus
				ImgOut[i+2-(nW*3)]=255; //pixel du dessous
			}
		}
	}

	ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
}
