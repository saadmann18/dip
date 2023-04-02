#include "dip.h"

// ------------------------------------------------------------------------------

//
// (11.1) Funktion zum Erzeugen eines periodischen Musters mit
//       Wellenzahlvektor [kx,ky] und Phasenverschiebung <phi>.
//
void wellenmuster (GrayImage& input, float kx, float ky, float phi)
{
	int    width  = input.getWidth();    // Breite des Bildes
	int    height = input.getHeight();   // Hoehe des Bildes
	float* data   = input.getData();     // Zeiger auf Bilddaten

	// Grauwert fuer jede Position (x,y) entsprechend Gleichung (2) ermitteln
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			data[y*width+x] = 127.5 + 127.5*cos(2*M_PI * (kx*x+ky*y) - phi);
		}
	}
}

// ------------------------------------------------------------------------------

//
//  Skalierung des Wertebereiches der Grauwerte des Bildes <input>.
//        In diesem Fall ist die Eingabe und die Ausgabe dasselbe Bild.
//
void scale (GrayImage& input)
{
	int    size = input.getSize();
	float* data = input.getData();

	float  mini = min(input);
	float  maxi = max(input);

	for (int i=0; i<size; i++)
	{
		data[i] = 255.0 * (data[i] - mini) / (maxi - mini);
	}
}

// ------------------------------------------------------------------------------

//
//  Fuehrt ein Clipping bei 0 und 255 durch, d.h. alle Werte kleiner 0
//        werden auf 0 und alle Werte groesser 255 werden auf 255 gesetzt.
//
void clip (GrayImage& input)
{
	float* data = input.getData();
	int    size = input.getSize();

	for (int i=0; i<size; i++)
	{
		if (data[i] > 255) data[i] = 255;
		if (data[i] < 0)   data[i] = 0;
	}
}

void viewFourierSpectrum(ComplexImage& input, GrayImage& output)
{
	int width = input.getWidth();
	int height = input.getHeight();

	float* odata = output.getData();
	Complex* idata = input.getData();

	for (int i = 0; i<width*height; i++)
	{
		odata[i] = sqrt(idata[i].re * idata[i].im*idata[i].im)*255.0;
	}
	clip(output);
}

void buildFilterTransferFunction (GrayImage& mask, int d0, int n, int u0, int v0)
{
	int width = mask.getWidth();
	int height = mask.getHeight();
	float* data = mask.getData();

	int m2 = width/2;
	int n2 = height/2;

	for (int v=0; v<height; v++){
		for (int u=0; u<width; u++)
		{
			float Duv1 = sqrt((double)((u-m2-u0)*(u-m2-u0) + (v-n2-v0)*(v-n2-v0)));
			float Duv2 = sqrt((double)((u-m2+u0)*(u-m2+u0) + (v-n2+v0)*(v-n2+v0)));
			data[v*width+u] = 1.0/(1.0+powf(((d0*d0)/(Duv1*Duv2)), n));
		}
	}
	saveFilterMask(mask, "filter.mask");

	scale(mask);
	mask.show();
	mask.save();
}

// ------------------------------------------------------------------------------

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 11                           */
	/* ************************************ */
	cout<<"Image recovery - please select function"<<endl;
	cout<<"1 - Defamiliarize the original image with a wave pattern (kx <1 & ky <1) and save it"<<endl;
	cout<<"2 - Fourier spectrum of images"<<endl;
	cout<<"3 - Create and save filters to match the Fourier spectrum"<<endl;
	cout<<"4 - Filtered image and display results"<<endl;
	/* ************************************ */
	/* Eingabe                              */
	/* ************************************ */
	int choice;
	cin>> choice;

	GrayImage image;
	image.load();

	int width = image.getWidth();
	int height = image.getHeight();

	GrayImage output(width, height);

	float* idata = image.getData();
	float* odata = output.getData();

	switch (choice)
	{
		case 1:
		{
			float kx, ky;

			cout<<"kx: ";
			cin>> kx;
			cout<<"ky: ";
			cin>> ky;

			wellenmuster(output, kx, ky, 0);
			output.show();

			for(int i=0; i<image.getSize(); i++)
			{
				idata[i] = idata[i]+idata[i]*((odata[i]-127.5)/512.0);
			}

			clip(image);
			image.show();
			image.save();

			break;
		}
		case 2:
		{
			ComplexImage fuv(width, height);
			ComplexImage tmp(width, height);
			ComplexImage output(width, height);

			fuv.copy(image);

			fourier_center(fuv);
			fourier_transform(fuv, tmp);

			viewFourierSpectrum(tmp, output);

			output.show();
			output.save();
			
			break;
		}
		case 3:
		{
			if(width == 0) width = 512;
			if(height == 0) height = 512;

			GrayImage filter(width, height);
			int d0, u0, v0, n;

			cout<<"Cut-Off Frequency d0: ";
			cin>> d0;
			cout<<"Order n: ";
			cin>> n;
			cout<<"Coordinate u0: ";
			cin>>u0;
			cout<<"Coordinate v0: ";
			cin>>v0;

			buildFilterTransferFunction(filter, d0, n,u0,v0);
			break;
		}
		case 4:
		{
			doFilteringInFrequencyDomain(image, output);
			scale(output);
			output.show();
			output.save();
			break;
		}
	}


	/* ************************************ */
	/* Datenverarbeitung / Funktionsaufruf  */
	/* ************************************ */


	/* ************************************ */
	/* Ausgabe                              */
	/* ************************************ */


	/* ************************************ */
	/* Programmende                         */
	/* ************************************ */
	cout << "FINISHED.\n";
	return 0;
}
