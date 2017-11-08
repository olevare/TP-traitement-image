#include "ImageBase.h"
#include <stdio.h>
#include <vector>
#include <math.h>

using namespace std;

//exercice 1
/*void subdivise(ImageBase& imIn,ImageBase& imOut)
{
	int moyenne = 0;
	int nombre = 0;

	//haut gauche
	for(int x = 0; x < imIn.getHeight()/2; x++) //hauteur
	{
		for(int y = 0; y < imIn.getWidth()/2; y++) //largeur
		{
			moyenne += imIn[x][y];
			nombre++;
		}
	}

	moyenne = moyenne / nombre;

	for(int x = 0; x < imIn.getHeight()/2; x++) //hauteur
	{
		for(int y = 0; y < imIn.getWidth()/2; y++) //largeur
			imOut[x][y] = moyenne;
	}

	//haut droite

	moyenne = 0;
	nombre = 0;

	for(int x = 0; x < imIn.getHeight()/2; x++) //hauteur
	{
		for(int y = imIn.getWidth()/2; y < imIn.getWidth(); y++) //largeur
		{
			moyenne += imIn[x][y];
			nombre++;
		}
	}

	moyenne = moyenne / nombre;

	for(int x = 0; x < imIn.getHeight()/2; x++) //hauteur
	{
		for(int y = imIn.getWidth()/2; y < imIn.getWidth(); y++) //largeur
			imOut[x][y] = moyenne;
	}

	//bas gauche

	moyenne = 0;
	nombre = 0;

	for(int x = imIn.getHeight()/2; x < imIn.getHeight(); x++) //hauteur
	{
		for(int y = 0; y < imIn.getWidth()/2; y++) //largeur
		{
			moyenne += imIn[x][y];
			nombre++;
		}
	}

	moyenne = moyenne / nombre;

	for(int x = imIn.getHeight()/2; x < imIn.getHeight(); x++) //hauteur
	{
		for(int y = 0; y < imIn.getWidth()/2; y++) //largeur
			imOut[x][y] = moyenne;
	}

	//bas droite

	moyenne = 0;
	nombre = 0;

	for(int x = imIn.getHeight()/2; x < imIn.getHeight(); x++) //hauteur
	{
		for(int y = imIn.getWidth()/2; y < imIn.getWidth(); y++) //largeur
		{
			moyenne += imIn[x][y];
			nombre++;
		}
	}

	moyenne = moyenne / nombre;

	for(int x = imIn.getHeight()/2; x < imIn.getHeight(); x++) //hauteur
	{
		for(int y = imIn.getWidth()/2; y < imIn.getWidth(); y++) //largeur
			imOut[x][y] = moyenne;
	}
}*/

class Carre
{
	public:
		
		int x,y,w,h;
		Carre *fils;
		int moyenne;

		Carre(int X,int Y,int W,int H)
		{
			x = X;
			w = W;
			y = Y;
			h = H;
		}
		Carre()
		{}

		void Subdivise()
		{
			fils = new Carre[4];

			for(int i=0;i<4;i++)
			{
				int X = x + (i%2) * w/2;
				int Y = y + (i/2) * h/2;
				int W = w/2;
				int H = h/2;

				fils[i] = Carre(X,Y,W,H);
			}
		}

		int getMoyenne(ImageBase& imIn)
		{
			int som = 0;
			for(int H = y; H < y+h; ++H)
				for(int W = x; W < x+w; ++W)
				{
					som += imIn[H][W];
				}

			moyenne = som / (h*w);
			return moyenne;
		}

		double getVariance(ImageBase& imIn)
		{
			int moyenne = getMoyenne(imIn);

			int som = 0;
			for(int H = y; H < y+h; ++H)
				for(int W = x; W < x+w; ++W)
				{
					som += pow(imIn[H][W] - moyenne,2);
				}

			return 1.0/(h*w) * som;
		}

		double getEcartType(ImageBase& imIn)
		{
			return sqrt(getVariance(imIn));
		}

		void Color(ImageBase& imOut,int value)
		{
			for(int H = y; H < y+h; ++H)
				for(int W = x; W < x+w; ++W)
				{
					imOut[H][W] = value;
				}
		}
};

vector<Carre> ensemble;

void Subdivision(ImageBase& imIn,ImageBase& imOut,Carre& carre,int seuil,int size_min)
{
	if( carre.getEcartType(imIn) > seuil && carre.w > size_min && carre.h > size_min)
	{
		carre.Subdivise();

		for(int i=0;i<4;i++)
		{
			Subdivision(imIn,imOut,carre.fils[i],seuil,size_min);
		}
	}
	else
	{
		carre.Color(imOut,carre.getMoyenne(imIn));
		ensemble.push_back(carre);

	}
}

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250];
  
	if (argc != 6) 
	{
		printf("Usage: ImageIn.pgm ImageOut.pgm seuil taille fusion\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	int seuil = atoi(argv[3]);
	int size_min = atoi(argv[4]);
	int fusion = atoi(argv[5]);
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	//exercice 1
	//subdivise(imIn, imOut);
	
	Carre image(0,0,imIn.getWidth(), imIn.getHeight());
	Subdivision(imIn,imOut,image,seuil,size_min);

	for(int i = 0; i < ensemble.size(); i++)
	{
		for(int j = i+1; j < ensemble.size(); j++)
		{
			if(abs(ensemble[i].moyenne - ensemble[j].moyenne) <= fusion)
			{
				if((ensemble[i].x + ensemble[i].w == ensemble[j].x && ensemble[i].y < ensemble[j].y + ensemble[j].w && ensemble[j].y < ensemble[i].y + ensemble[i].w)
				|| (ensemble[j].x + ensemble[j].w == ensemble[i].x && ensemble[j].y < ensemble[i].y + ensemble[i].w && ensemble[i].y < ensemble[j].y + ensemble[j].w)
				|| (ensemble[i].y + ensemble[i].h == ensemble[j].y && ensemble[i].x < ensemble[j].x + ensemble[j].h && ensemble[j].x < ensemble[i].x + ensemble[i].h)
				|| (ensemble[j].y + ensemble[j].h == ensemble[i].y && ensemble[j].x < ensemble[i].x + ensemble[i].h && ensemble[i].x < ensemble[j].x + ensemble[j].h))
				{
					ensemble[j].Color(imOut, ensemble[i].moyenne);
				}
			}
		}
	}

	imOut.save(cNomImgEcrite);


	
	return 0;
}