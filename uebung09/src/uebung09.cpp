#include "dip.h"

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
			data[y*width+x] = 0;
		}
	}
}
void filter (GrayImage& input, GrayImage& output, GrayImage& mask)
{
	int    mwidth   = mask.getWidth();
	int    mheight  = mask.getHeight();
	float* mdata    = mask.getData();

	int    mwidth2  = mwidth / 2;
	int    mheight2 = mheight / 2;

	int    iwidth   = input.getWidth();
	int    iheight  = input.getHeight();
	float* idata    = input.getData();
	float* odata    = output.getData();

	float  sum;

	for (int y=0; y<iheight; y++)
	{
		for (int x=0; x<iwidth; x++)
		{
			sum = 0.0;
			for (int t=0; t<mheight; t++)
			{
				for (int s=0; s<mwidth; s++)
				{
					int y2 = mod(y+(t-mheight2), iheight);
					int x2 = mod(x+(s-mwidth2), iwidth);

					sum += mdata[t*mwidth+s] * idata[y2*iwidth+x2];
				}
			}
			odata[y*iwidth+x] = sum;
		}
	}
}

// ------------------------------------------------------------------------------


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


void abs (GrayImage& input)
{
	float* data = input.getData();
	int    size = input.getSize();

	for (int i=0; i<size; i++) {
		if (data[i] < 0) data[i] = -data[i];
	}
}
void maskLoG (GrayImage& mask, float sigma)
{
	int width = mask.getWidth();
	int height = mask.getHeight();
	float* data = mask.getData();

	int x0 = width/2;
	int y0 = height/2;
	float s2 = sigma * sigma;
	float s4 = sigma * sigma * sigma * sigma;

	for(int y=0; y<height; y++)
	{
		for (int x=0; x<width; x++)
		{
			int x1 = x-x0;
			int y1 = y-y0;
			float exp = (float)(x1*x1 + y1*y1);

			data[y*width+x] = ((2*s2-exp)/s4) * expf(-exp/(2*s2));
		}
	}
}
// ------------------------------------------------------------------------------

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 09                            */
	/* ************************************ */


	/* ************************************ */
	/* Eingabe                              */
	/* ************************************ */


	/* ************************************ */
	/* Datenverarbeitung / Funktionsaufruf  */
	/* ************************************ */
	GrayImage gauss;
	GrayImage laplace;
	
	GrayImage img;

	string filename;
	cout<< "File name of the Gauss filter: ";
	cin>> filename;
	loadFilterMask(filename, gauss);

	cout<< "File name of the Laplace filter: ";
	cin>> filename;
	loadFilterMask(filename, laplace);

	cout<< "File name of the picture: ";
	cin>> filename;
	img.load(filename);

	GrayImage result_gauss(img.getWidth(), img.getHeight());
	GrayImage result_laplace(img.getWidth(), img.getHeight());

	scale(result_laplace);
	result_laplace.show();
	result_laplace.save();
	/* ************************************ */
	/* Ausgabe                              */
	/* ************************************ */


	/* ************************************ */
	/* Programmende                         */
	/* ************************************ */
	cout << "FINISHED.\n";
	return 0;
}
