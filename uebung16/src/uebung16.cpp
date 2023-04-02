#include "dip.h"

// ------------------------------------------------------------------------------

//
// (2.1b) Funktion zum Setzen eines Pixelwertes
//
void setPixel (RgbImage& input, int x, int y, Rgb value)
{
	Rgb* data   = input.getData();
	int  breite = input.getWidth();

	data[y*breite+x] = value;
}

// ------------------------------------------------------------------------------

//
// (2.1c) Funktion zum Zeichnen eines Rechteckes mit den Eckpunkten
//        (x1,y1)-links oben und (x2,y2)-rechts unten
//
void rectangle (RgbImage& input, int x1, int y1, int x2, int y2, Rgb color)
{
	int i;

	for (i=x1; i<=x2; i++)
	{
		setPixel(input, i, y1, color);
		setPixel(input, i, y2, color);
	}

	for (i=y1; i<=y2; i++)
	{
		setPixel(input, x1, i, color);
		setPixel(input, x2, i, color);
	}
}

// ------------------------------------------------------------------------------

//
// (5.1c) Skalierung des Wertebereiches der Grauwerte des Bildes <input>.
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
// (6.1d) Filtert das Eingangsbild <input> mit der Filtermaske <mask>. Das Ergebnis
//        wird in <output> geschrieben. Randbehandlung durch Kachelung des Bildes.
//
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
					// Modulo -> berechnet die Randbehandlung
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

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 15                            */
	/* ************************************ */

	Rgb red, blue, green, black;
	red.r   = 255; red.g   =   0; red.b   =   0;
	blue.r  = 128; blue.g  = 128; blue.b  = 255;
	green.r = 0;   green.g = 255; green.b =   0;
	black.r = 0;   black.g =   0; black.b =   0;

	// Eingabebild laden und anzeigen
	RgbImage input;
	//input.load();
	//input.show();

	int width  = input.getWidth();
	int height = input.getHeight();

	cout << "Option:\n";
	cout << "1 - RGB and HSV image filtering\n";
	cout << "2 - Red color segmmentation\n";
	cout << "3 - Black color segmmentation\n";

	int option;
	cin >> option;

	/* ************************************ */
	/* Datenverarbeitung                    */
	/* ************************************ */

	switch (option)
	{
		case 1:
		{
			break;
		}
		case 2:
		{
			break;
		}
		case 3:
		{
			break;
		}
		default:
		{
			//exit(0);
		}
	}

	/* ************************************ */
	/* Programmende                         */
	/* ************************************ */
	cout << "FINISHED.\n";
	return 0;
}
