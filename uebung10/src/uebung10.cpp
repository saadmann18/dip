#include "dip.h"

// ------------------------------------------------------------------------------

void setPixel (GrayImage& input, int x, int y, float value)
{
	float* data      = input.getData();  // Zeiger auf Bilddaten
	int    width    = input.getWidth(); // Bildbreite zur Berechnung des Pixelindex

	data[y*width+x] = value;            // Grauwert des Pixels aendern
}

// ------------------------------------------------------------------------------

float getPixel (GrayImage& input, int x, int y)
{
	float* data      = input.getData();  // Zeiger auf Bilddaten
	int    width    = input.getWidth(); // Bildbreite zur Berechnung des Pixelindex

	return data[y*width+x];             // Wert des Pixel zurueckgeben
}

// ------------------------------------------------------------------------------

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

// ------------------------------------------------------------------------------



enum FilterType {ILPF = 1, IHPF = 2, BLPF = 3, BHPF = 4, GLPF = 5, GHPF = 6};

void buildFilterTransferFunction (ComplexImage& input, FilterType filter, int d0, int n)
{
	int width = input.getWidth();
	int height = input.getHeight();
	Complex* data = input.getData();

	int m2 = width/2;
	int n2 = height/2;

	for (int v=0; v<height; v++)
	{
		for (int u=0; u<width; u++)
		{
			float Duv = sqrt((double)((u-m2)*(u-m2)+(v-n2)*(v-n2)));

			if (filter == ILPF)
			{
				if (Duv <=d0) data[v*width+u].re = 1;
				else					data[v*width+u].re = 0;
			}
			if (filter == IHPF)
			{
				if (Duv <=d0) data[v*width+u].re = 0;
				else					data[v*width+u].re = 1;
			}
			if (filter == BLPF) data[v*width+u].re = 1.0/(1.0 + powf((Duv/d0), 2.0*n));
			if (filter == BHPF) data[v*width+u].re = 1.0/(1.0 + powf((d0/Duv), 2.0*n));

			if (filter == GLPF) data[v*width+u].re = expf(-(Duv*Duv)/(2.0 * d0*d0));
			if (filter == GHPF) data[v*width+u].re = 1-expf(-(Duv*Duv)/(2.0 * d0*d0));

			data[v*width+u].im = 0;
		}
	}
}

void spatialRepresentation (ComplexImage& input_frequency, ComplexImage& output_spatial)
{
	ComplexImage tmp(input_frequency);
	fourier_center(tmp);
	inverse_fourier_transform(tmp, output_spatial);
	fourier_center(output_spatial);
}
enum PreviewType {CLIP, SCALE};

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


void viewComplexImage (ComplexImage& input, PreviewType preview)
{
	int width = input.getWidth();
	int height = input.getHeight();

	GrayImage real_img(width, height);
	GrayImage imag_img(width, height);

	real_part(input, real_img);
	imag_part(input, imag_img);

	if (preview == SCALE) scale(real_img); //Scale or
	if (preview == CLIP) clip(real_img);	//Clip?

	real_img.show();
	real_img.save();

	if (preview == SCALE) scale(imag_img); //Scale or
	if (preview == CLIP) clip(imag_img);	//Clip?

	imag_img.show();
	imag_img.save();
}

void viewComplexImageMagnitude (ComplexImage& input, PreviewType preview)
{
	int width = input.getWidth();
	int height = input.getHeight();

	GrayImage real_img(width, height);
	GrayImage imag_img(width, height);
	GrayImage magnitude_img(width, height);

	real_part(input, real_img);
	imag_part(input, imag_img);
	fourier_spectrum(input, magnitude_img);

	if (preview == SCALE) scale(real_img);
	if (preview == CLIP) clip(real_img);

	real_img.show();
	real_img.save();

	if (preview == SCALE) scale(imag_img);
	if (preview == CLIP) clip(imag_img);

	imag_img.show();
	imag_img.save();

	float maxi = max(magnitude_img);
	magnitude_img.mul(255.0/maxi);

	magnitude_img.show();
	magnitude_img.save();
}

// ------------------------------------------------------------------------------

int main (int argc, char** argv)
{
	/* ************************************ */
	/* Uebung 10                            */
	/* ************************************ */
	int width = 128;
	int height = 128;
	ComplexImage transferFunction(width, height);
	ComplexImage spatialFilterMask(width, height);

	int input;
	cout<< "Filtertyp (1 (ILPF), 2 (IHPF), 3 (BLPF), 4 (BHPF), 5 (GLPF), 6 (GHPF)): ";
	cin>> input;

	//filter type selection
	FilterType filtertype = static_cast<FilterType>(input);

	//Query D0 and n
	int d0 = 1;
	int n = 1;

	cout<< "D0: ";
	cin>> d0;

	if (filtertype == BLPF || filtertype == BHPF)
	{
		cout<< "n: ";
		cin>>n;
	}
	buildFilterTransferFunction(transferFunction, filtertype, d0, n);
	spatialRepresentation(transferFunction, spatialFilterMask);
	viewComplexImage(spatialFilterMask, SCALE);

	cout<< "FINISHED.\n";
	return 0;
}
