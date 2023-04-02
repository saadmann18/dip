#include "dip.h"

// ------------------------------------------------------------------------------


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

// ------------------------------------------------------------------------------

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 13                           */
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
	cout << "FINISHED.\n";
	return 0;
}
