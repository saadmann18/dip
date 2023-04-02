#include "dip.h"

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------
void setPixel(GrayImage &input, int x, int y, float value)
{
	float *data = input.getData(); // Zeiger auf Bilddaten
	int width = input.getWidth();  // Bildbreite zur Berechnung des Pixelindex

	data[y * width + x] = value; // Grauwert des Pixels aendern
}

float getPixel(GrayImage &input, int x, int y)
{
	float *data = input.getData(); // Zeiger auf Bilddaten
	int width = input.getWidth();  // Bildbreite zur Berechnung des Pixelindex

	return data[y * width + x]; // Wert des Pixel zurueckgeben
}

void zeros(GrayImage &f)
{
	int width = f.getWidth();
	int height = f.getHeight();
	float *data = f.getData();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			setPixel(f, x, y, 0);
			// data[y * width + x] = 0;
		}
	}
}
/*
4.1

 */
void wavepattern(GrayImage &image, float kx, float ky, float phi)
{

	int width = image.getWidth();
	int height = image.getHeight();
	float *data = image.getData();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			data[y * width + x] = 127.5 + 127.5 * cos(2 * M_PI * (kx * x + ky * y) - phi);
		}
	}
}
/*
4.2

 */
void sample(GrayImage &input, GrayImage &output, int r)
{
	int iwidth = input.getWidth();	 // Width of the input image
	int iheight = input.getHeight(); // Height of the input image
	float *idata = input.getData();	 // File pointer of the input image

	int owidth = iwidth / r;		 // Width of the output image
	int oheight = iheight / r;		 // Height of the output image
	float *odata = output.getData(); // File pointer of the output image

	// for each position in the source image the corresponding pixel field
	// Determine input image
	for (int y = 0; y < oheight; y++)
	{
		for (int x = 0; x < owidth; x++)
		{
			//
			//
			//
			odata[y * owidth + x] = idata[y * r * iwidth + x * r];
		}
	}
}

int main(int argc, char **argv)
{
	/* ************************************ */
	/* Uebung 04                            */
	/* ************************************ */

	/* ************************************ */
	/* Eingabe                              */
	/* ************************************ */
	int w, h;
	cout << "Give a height and width : " << endl;
	cin >> w >> h;

	float kx, ky;
	cout << "Give wave number vectors [kx, ky] : " << endl;
	cin >> kx >> ky;

	int r;
	cout << "Give Sample rate r : " << endl;
	cin >> r;

	/* ************************************ */
	/* Datenverarbeitung / Funktionsaufruf  */
	/* ************************************ */

	/* ************************************ */
	/* Ausgabe                              */
	/* ************************************ */

	/* ************************************ */
	/* Programmende                         */
	/* ************************************ */
	GrayImage image(w, h);
	GrayImage result(w / r, w / r);

	wavepattern(image, kx, ky, 45);

	sample(image, result, r);

	image.show();

	result.show(image.getWidth(), image.getHeight());

	cout << "FINISHED.\n";
	return 0;
}
