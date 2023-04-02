#include "dip.h"

// ------------------------------------------------------------------------------

//
// Diese Funktion liefert das Minimum der angegebenen Werte.
//
float min (float r, float g, float b)
{
	if (r <= g and r <= b) return r;
	if (g <= r and g <= b) return g;
	if (b <= r and b <= g) return b;
	return 0.0;
}

// ------------------------------------------------------------------------------

//
// Diese Funktion liefert das Maximum der angegebenen Werte.
//
float max (float r, float g, float b)
{
	if (r >= g and r >= b) return r;
	if (g >= r and g >= b) return g;
	if (b >= r and b >= g) return b;
	return 0.0;
}

// ------------------------------------------------------------------------------

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 13                            */
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
