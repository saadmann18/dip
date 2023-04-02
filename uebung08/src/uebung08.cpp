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

void scale (GrayImage& input)
{
	int size = input.getSize();
	float*data = input.getData();

	float mini = min(input);
	float maxi = max(input);

	for (int i=0; i<size; i++)
	{
		data[i] = 255.0 * (data[i] - mini)/(maxi-mini);
	}
}

void abs (GrayImage& input)
{
	float* data = input.getData();
	int size = input.getSize();

	for (int i=0; i<size; i++)
	{
		if(data[i]<0) data[i] = -data[i];
	}
}

void clip (GrayImage& input)
{
	float* data = input.getData();
	int size = input.getSize();

	for (int i=0; i<size; i++)
	{
		if(data[i]>255) data[i] = 255;
		if(data[i]<0) 	data[i] = 0;
	}
}
// ------------------------------------------------------------------------------
enum maskType{
LAPLACE,
SOBEL_VERT,
SOBEL_HORI,
ROBERTS_VERT,
ROBERTS_HORI
};


int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 08                            */
	/* ************************************ */

	cout<< "Select the following functions: \n";
	cout<< "1 - Create Laplace filter \n";
	cout<< "2 - vert. Sobel filters\n";
	cout<< "3	-	hori. Sobel filters\n";
	cout<< "4 - vert. Roberts filters\n";
	cout<< "5 - hori. Roberts filters\n";
	cout<< "---------------------------\n";
	cout<< "6 - Apply filter to image and scale filter image\n";
	cout<< "7 - Apply filter to image and use absolute values for filter image\n";
	cout<< "8 - Apply filter to image, filter list on image Add and scale\n";

	int choice;
	cin>> choice;

	string filename;
	GrayImage image;

	if (choice>5)
	{
		cout<<"image file name: ";
		cin>> filename;
		image.load(filename);
	}
	string filtername;
	cout<<"Filtername: ";
	cin>>filtername;

	switch (choice) {
		case 1:
		{
			GrayImage mask = GrayImage(3,3);
			makeFilter(mask, LAPLACE);
			break;
		}
		case 2:
		{
			GrayImage mask = GrayImage(3,3);
			makeFilter(mask, SOBEL_VERT);
			break;
		}
		case 3:
		{
			GrayImage mask = GrayImage(3,3);
			makeFilter(mask, SOBEL_HORI);
			break;
		}
		case 4:
		{
			GrayImage mask = GrayImage(2,2);
			makeFilter(mask, ROBERTS_VERT);
			break;
		}
		case 5:
		{
			GrayImage mask = GrayImage(2,2);
			makeFilter(mask, ROBERTS_HORI);
			break;
		}
		case 6:
		{
			GrayImage mask;
			loadFilterMask(filtername, mask);
			GrayImage result = GrayImage(image.getWidth(), image.getHeight());
			filter(image, result, mask);
			scale(result);
			result.show();
			result.save();
			break;
		}
		case 7:
		{
			GrayImage mask;
			loadFilterMask(filtername, mask);

			GrayImage result = GrayImage(image.getWidth(), image.getHeight());
			filter(image, result, mask);
			abs(result);
			result.show();
			result.save();
			break;
		}
		case 8:
		{
			GrayImage mask;
			loadFilterMask(filtername, mask);

			GrayImage result = GrayImage(image.getWidth(), image.getHeight());
			filter(image, result, mask);
			image.add(result);
			scale(image);
			result.show();
			result.save();
			break;
		}
		case 9:
		{
			GrayImage mask;
			loadFilterMask(filtername, mask);

			GrayImage result = GrayImage(image.getWidth(), image.getHeight());
			filter(image, result, mask);
			image.add(result);
			clip(image);
			result.show();
			result.save();
			break;
		}

	}
	cout << "FINISHED.\n";
	return 0;
}
