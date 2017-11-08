#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
	int S;
  
	if (argc != 4) 
	{
		printf("Usage: i1.pgm ImageOut.pgm Seuil \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3],"%d",&S);

	ImageBase imIn;
	imIn.load(cNomImgLue);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	/*

		Utilisation de la moyenne des pixels pour reconstruite l'image d'origine

		Algo: (X,Y) point appartenant à la tache, imIn, maskTache, pxToChange

			contourtache: création du contour de la tache

			FillContour: on remplace les pixels de contours


		Arrêt quand pxToChange = 0.



	*/


	int w = imIn.getWidth();
	int h = imIn.getHeight();
	bool maskTache[h][w] = {0};
	cout << endl << "Image (" << w << ":"  << h << ")." << endl;
	bool contourTache[h][w] = {0};

	/*
		On récupère la tache.
	*/

	for(int x = 0; x < h ; ++x) // D'abord sur la height
		for(int y = 0; y < w ; ++y) // Puis la width
		{
			if (imIn[x][y] == 0 ) 
			{
				maskTache[x][y] = 1;
			}
		}


	/*
		On dilatate.
	*/
		/*
	for( int i=0;i<1;i++)
	{
		bool newMaskTache[w][h] = {0};
		for(int x = 1; x < h-1 ; ++x) // D'abord sur la height
		for(int y = 1; y < w-1 ; ++y) // Puis la width
		{
			if (maskTache[x][y] == 1 ) 
			{
				newMaskTache[x][y] = 1;
				newMaskTache[x-1][y] = 1;
				newMaskTache[x+1][y] = 1;
				newMaskTache[x][y-1] = 1;
				newMaskTache[x][y+1] = 1;
			}
		}

		for(int x = 0; x < h ; ++x) // D'abord sur la height
			for(int y = 0; y < w ; ++y) // Puis la width
			{
				maskTache[x][y] = newMaskTache[x][y];
			}
	}
	*/

	int minx = 0;
	int miny = 0;
	int maxx = 0;
	int maxy = 0;



	/*
		On élimine la tache
	*/
	int ptc = 1;
	while(ptc >0)
	{
		bool newMaskTache[w][h] = {0};
		ptc = 0;
		// Passe 1: On élimine le contour
		for(int x = 1; x < h-1 ; ++x) // D'abord sur la height
			for(int y = 120; y < w-1 ; ++y) // Puis la width
			{
				if (maskTache[x][y] == 1 && (maskTache[x-1][y] ==0 ||maskTache[x][y-1] ==0  || maskTache[x][y+1] ==0  || maskTache[x+1][y] ==0 )) // si appartient au mask,
				{
					contourTache[x][y] = 1;
					ptc++;
				}
				else
				{
					contourTache[x][y] = 0;
					if (maskTache[x][y] == 1) newMaskTache[x][y] = 1;
				}
			}
		for(int x = 0; x < h ; ++x) // D'abord sur la height
			for(int y = 0; y < w ; ++y) // Puis la width
			{
				if (contourTache[x][y] == 1) // si appartient au mask,
				{
						//maskTache[x][y] = 0;
						/*
							On récupère la direction
							On  remplace par le px 3x plus loin
						*/

						int dx = 0;
						int dy = 0;
						
						if (maskTache[x-1][y] ==0) dx=-1;
						if (maskTache[x+1][y] ==0) dx=1;
						if (maskTache[x][y-1] ==0) dy=-1;
						if (maskTache[x][y+1] ==0) dy=1;
						if (maskTache[x][y+1] ==0 && maskTache[x][y-1] ==0) dy = 0;
						if (maskTache[x-1][y] ==0 && maskTache[x+1][y] ==0) dx = 0;
					
						for(int a=-4;a<4;a++) for (int b=-4;b<4;b++)
							{
								if (maskTache[x-a][y-b] == 1)
								{
									imOut[x-a][y-b] = imIn[x+dx*5+a][y+dy*5+b];
									imIn[x-a][y-b] = imOut[x-a][y-b];

									contourTache[x-a][y-b] = 0;
									newMaskTache[x-a][y-b] = 0;
									// MODIFIED
									maskTache[x-a][y-b] = 0;

								}
								
							}
						
					
				}
				else // Si n'appartient pas au mask, on transparait
				{
					imOut[x][y] = imIn[x][y];
				}
			}

		for(int x = 0; x < h ; ++x) // D'abord sur la height
			for(int y = 0; y < w ; ++y) // Puis la width
			{
				maskTache[x][y] = 0;
			}

			for(int x = 3; x < h-3 ; ++x) // D'abord sur la height
			for(int y = 3; y < w-3 ; ++y) // Puis la width
			{
				maskTache[x][y] = newMaskTache[x][y];
			}

		cout << ptc << endl;
	}

	
	imOut.save(cNomImgEcrite);
		

	return 0;
}
