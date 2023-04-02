#include "dip.h"

// ------------------------------------------------------------------------------
// ------------------------------------------------------------------------------

void setPixel(GrayImage &input, int x, int y, float value) // Passing the object of GrayImage as reference, so it modifies directly at the same location where the object is instantiated.
{
	float *data = input.getData(); // Pointer at the beginning of specified linear dimentional memory of image data.
	int width = input.getWidth();  // Image width for calculating the pixel index.

	data[y * width + x] = value; // Change the gray value of the pixel in the memory where the data pointer is pointing at.
}

float getPixel(GrayImage &input, int x, int y)
{
	float *data = input.getData(); // Pointer at the beginning of specified linear memory of image data.
	int width = input.getWidth();  // Image width for calculating the pixel index

	return data[y * width + x]; // Return the value of the pixel from the memory where the data pointer is pointing at
}

void zeros(GrayImage &input)
{
	int width = input.getWidth();
	int height = input.getHeight();
	float *data = input.getData(); // Pointer at the beginning of specified linear dimentional memory of image data.
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			data[y * width + x] = 0;
			// setPixel (input, x, y, 100);
		}
	}
}

void rectangle(GrayImage &input, int x1, int y1, int x2, int y2)
{
	int i;
	for (i = x1; i <= x2; i++)
	{
		setPixel(input, i, y1, 255.0);
		setPixel(input, i, y2, 255.0);
	}

	for (i = y1; i <= y2; i++)
	{
		setPixel(input, x1, i, 255.0);
		setPixel(input, x2, i, 255.0);
	}
}

void circle(GrayImage &input, int radius, int posx, int posy)
{
	int x, y1, y2;
	for (x = -radius; x <= radius; x++)
	{
		y1 = (int)sqrt(float(radius * radius - x * x));
		y2 = -y1;

		setPixel(input, posx + x, posy + y1, 255.0);
		setPixel(input, posx + x, posy + y2, 255.0);
	}
}

void circle2(GrayImage &input, int radius, int posx, int posy)
{
	double cercum = M_PI * (double)(2.0 * radius);
	double arc = 360.0 / cercum;

	double phi;
	for (phi = 0; phi < 360; phi += arc)
	{
		setPixel(input, posx + (int)floor(radius * cos(phi * M_PI / 180.0)),
				 posy + (int)floor(radius * sin(phi * M_PI / 180.0)),
				 255.0);
	}
}

int main(int argc, char *argv[])
{
	/* ************************************ */
	/* Uebung 02                            */
	/* ************************************ */

	/* ************************************ */
	/* input                              */
	/* ************************************ */

	/* ************************************ */
	/* data processing / function call  */
	/* ************************************ */

	/* ************************************ */
	/* output                              */
	/* ************************************ */

	/* ************************************ */
	/* end of program                        */
	/* ************************************ */

	// an example
	GrayImage I(500, 500); // instantiating I object from GrayImage class, Constructor is called when when the object is instantiated.
	zeros(I);
	rectangle(I, 0, 0, 50, 50);
	rectangle(I, 0, 0, 50, 50);
	circle(I, 60, 60, 60);
	circle2(I, 60, 60, 60);

	I.show();
	setPixel(I, 50, 50, 255.0);
	cout << getPixel(I, 50, 50) << endl;
	cout << "FINISHED.\n";
	return 0;
}
