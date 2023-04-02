#include "dip.h"

// ------------------------------------------------------------------------------

int main(int argc, char **argv)
{
	/* ************************************ */
	/* Uebung 01                            */
	/* ************************************ */
	GrayImage image;

	cout << "Load an image: " << endl;
	image.load();

	cout << "Width: " << image.getHeight() << endl;
	cout << "Hight: " << image.getWidth() << endl;

	// Show the image
	image.show();

	cout << "FINISHED.\n";
	return 0;
}
