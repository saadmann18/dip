#include "dip.h"

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
void setPixel (GrayImage& input, int x, int y, float value)
{
	float* data      = input.getData();  // Zeiger auf Bilddaten
	int    width    = input.getWidth(); // Bildbreite zur Berechnung des Pixelindex

	data[y*width+x] = value;            // Grauwert des Pixels aendern
}

float getPixel (GrayImage& input, int x, int y)
{
	float* data      = input.getData();  // Zeiger auf Bilddaten
	int    width    = input.getWidth(); // Bildbreite zur Berechnung des Pixelindex

	return data[y*width+x];             // Wert des Pixel zurueckgeben
}
void zeros(GrayImage& f)
{
	int    width   = f.getWidth();
	int    height  = f.getHeight();
	float* data    = f.getData();
	for (int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			setPixel(f, x,y,0);
		}
	}
}
//5.1 c
void scale (GrayImage& input, GrayImage& output){
	int size = input.getSize();
	float* idata = input.getData();
	float* odata = output.getData();

	float mini = min(input);
	float maxi = max(input);

	for(int i=0; i<size; i++){
		odata[i] = 255*(idata[i]-mini)/(maxi-mini);
	}
}
//5.1

void gamma (GrayImage& input, GrayImage& output, float gamma){
	int size = input.getSize();
	float* idata = input.getData();
	float* odata = output.getData();

	for(int i=0;i<size;i++){
		odata[i] = 255.0*powf(idata[i]/255.0, gamma);
	}
}

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 04                            */
	/* ************************************ */


	/* ************************************ */
	/* Eingabe                              */
	/* ************************************ */
	string filename;
	cout<< "Filename: ";
	cin >> filename;

	GrayImage image;


	image.load();
	GrayImage result(image.getWidth(), image.getHeight());

	int input;
	cin >> input;

	switch (input) {
		case 1:
			scale (image, result);
			break;
		case 2:
			cout<<"Gamma: " <<endl;
			float g;
			cin>> g;
			gamma (image, result, g);
			break;
	}



	image.show();
	result.show();


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
