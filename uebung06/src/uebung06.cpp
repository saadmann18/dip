#include "dip.h"

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
			data[y*width+x] = 0;
		}
	}
}


void meanfilter(GrayImage& input, GrayImage& output, int N, int M)
{
	int size = input.getSize();
	float* idata = input.getData();
	float* odata = output.getData();

   for (int m = 1; m < M - 1; ++m)
      for (int n = 1; n < N - 1; ++n)

         odata[(m-1) * (N-2) + n-1] = (
            idata[(m-1)*N+n-1] + idata[(m-1)*N+n] + idata[(m-1)*N+n+1] +

						idata[m*N+n-1] + idata[m*N+n] + idata[m*N+n+1] +

						idata[(m+1)*N+n-1] + idata[(m+1)*N+n] + idata[(m+1)*N+n+1]) / 9;
}




// //
//
// odata(m,n)=idata(m,n)+idata(i+M,j+N);
//         idata(m,n)=idata(m,n)/9;
//
// //

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 05                            */
	/* ************************************ */


	/* ************************************ */
	/* Eingabe                              */
	/* ************************************ */


	/* ************************************ */
	/* Datenverarbeitung / Funktionsaufruf  */
	/* ************************************ */


	/* ************************************ */
	/* Ausgabe                              */
	/* ************************************ */


	/* ************************************ */
	/* Programmende                         */
	/* ************************************ */

	GrayImage image;

	cout << "Load an image: "<< endl;
	image.load();
	GrayImage result(image.getWidth(), image.getHeight());
	image.show();
	result.show();
	cout << "FINISHED.\n";
	return 0;
}
