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

	OCTET *ImgIn, *ImgOut, *ImgInt, *ImgInt2, *ImgInt3, *ImgInt4, *ImgInt5, *ImgInt6, *ImgInt7, *ImgInt8, *ImgInt9, *ImgInt10, *ImgInt11;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgInt, OCTET, nTaille);
	allocation_tableau(ImgInt2, OCTET, nTaille);
	allocation_tableau(ImgInt3, OCTET, nTaille);
	allocation_tableau(ImgInt4, OCTET, nTaille);
	allocation_tableau(ImgInt5, OCTET, nTaille);
	allocation_tableau(ImgInt6, OCTET, nTaille);
	allocation_tableau(ImgInt7, OCTET, nTaille);
	allocation_tableau(ImgInt8, OCTET, nTaille);
	allocation_tableau(ImgInt9, OCTET, nTaille);
	allocation_tableau(ImgInt10, OCTET, nTaille);
	allocation_tableau(ImgInt11, OCTET, nTaille);
	allocation_tableau(ImgOut, OCTET, nTaille);

	//FERMETURE = Dilatation puis erosion

	//dilatation
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			ImgInt[i*nW+j]=255;
		}
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgIn[i*nW+j] == 0){
				ImgInt[i*nW+j]=0;			//pixel central
				ImgInt[i*nW+j+1]=0;			//pixel de droite
				ImgInt[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt[(i-1)*nW+j]=0;	//pixel du dessus
					ImgInt[(i+1)*nW+j]=0; 	//pixel du dessous
				}
			}
		}
	}

	//dilatation
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			ImgInt2[i*nW+j]=255;
		}
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt[i*nW+j] == 0){
				ImgInt2[i*nW+j]=0;			//pixel central
				ImgInt2[i*nW+j+1]=0;			//pixel de droite
				ImgInt2[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt2[(i-1)*nW+j]=0;	//pixel du dessus
					ImgInt2[(i+1)*nW+j]=0; 	//pixel du dessous
				}
			}
		}
	}

	//dilatation
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			ImgInt3[i*nW+j]=255;
		}
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt2[i*nW+j] == 0){
				ImgInt3[i*nW+j]=0;			//pixel central
				ImgInt3[i*nW+j+1]=0;			//pixel de droite
				ImgInt3[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt3[(i-1)*nW+j]=0;	//pixel du dessus
					ImgInt3[(i+1)*nW+j]=0; 	//pixel du dessous
				}
			}
		}
	}

	//erosion
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt3[i*nW+j] == 255){
				ImgInt4[i*nW+j]=255;			//pixel central
				ImgInt4[i*nW+j+1]=255;		//pixel de droite
				ImgInt4[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt4[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt4[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//erosion
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt4[i*nW+j] == 255){
				ImgInt5[i*nW+j]=255;			//pixel central
				ImgInt5[i*nW+j+1]=255;		//pixel de droite
				ImgInt5[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt5[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt5[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//erosion
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt5[i*nW+j] == 255){
				ImgInt6[i*nW+j]=255;			//pixel central
				ImgInt6[i*nW+j+1]=255;		//pixel de droite
				ImgInt6[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt6[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt6[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//erosion
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt6[i*nW+j] == 255){
				ImgInt7[i*nW+j]=255;			//pixel central
				ImgInt7[i*nW+j+1]=255;		//pixel de droite
				ImgInt7[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt7[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt7[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//erosion
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt7[i*nW+j] == 255){
				ImgInt8[i*nW+j]=255;			//pixel central
				ImgInt8[i*nW+j+1]=255;		//pixel de droite
				ImgInt8[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt8[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt8[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//erosion
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt8[i*nW+j] == 255){
				ImgInt9[i*nW+j]=255;			//pixel central
				ImgInt9[i*nW+j+1]=255;		//pixel de droite
				ImgInt9[i*nW+j-1]=255;		//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt9[(i-1)*nW+j]=255;	//pixel du dessus
					ImgInt9[(i+1)*nW+j]=255; //pixel du dessous
				}
			}
		}
	}

	//dilatation
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			ImgInt10[i*nW+j]=255;
		}
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt9[i*nW+j] == 0){
				ImgInt10[i*nW+j]=0;			//pixel central
				ImgInt10[i*nW+j+1]=0;			//pixel de droite
				ImgInt10[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt10[(i-1)*nW+j]=0;	//pixel du dessus
					ImgInt10[(i+1)*nW+j]=0; 	//pixel du dessous
				}
			}
		}
	}

	//dilatation
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			ImgInt11[i*nW+j]=255;
		}
	}
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if (ImgInt10[i*nW+j] == 0){
				ImgInt11[i*nW+j]=0;			//pixel central
				ImgInt11[i*nW+j+1]=0;			//pixel de droite
				ImgInt11[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgInt11[(i-1)*nW+j]=0;	//pixel du dessus
					ImgInt11[(i+1)*nW+j]=0; 	//pixel du dessous
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
			if (ImgInt11[i*nW+j] == 0){
				ImgOut[i*nW+j]=0;			//pixel central
				ImgOut[i*nW+j+1]=0;			//pixel de droite
				ImgOut[i*nW+j-1]=0;			//pixel de gauche
				if (i != 0 && i != (nH-1)){
					ImgOut[(i-1)*nW+j]=0;	//pixel du dessus
					ImgOut[(i+1)*nW+j]=0; 	//pixel du dessous
				}
			}
		}
	}



	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	free(ImgInt);
	return 1;

}
