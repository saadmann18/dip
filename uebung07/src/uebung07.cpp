#include "dip.h"
enum SortType
{
	SELECTIONSORT = 1,
	BUBBLESORT = 2,
	QUICKSORT = 3
};

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
			data[y * width + x] = 0;
		}
	}
}

void filter(GrayImage &input, GrayImage &output, GrayImage &mask)
{
	int mwidth = mask.getWidth(); // Mask width
	int mheight = mask.getHeight();
	float *mdata = mask.getData();

	int mwidth2 = mwidth / 2;
	int mheight2 = mheight / 2;

	int iwidth = input.getWidth();
	int iheight = input.getHeight();
	float *idata = input.getData();
	float *odata = output.getData();

	float sum;

	for (int y = 0; y < iheight; y++)
	{
		for (int x = 0; x < iwidth; x++)
		{
			sum = 0.0;
			for (int t = 0; t < mheight; t++)
			{
				for (int s = 0; s < mwidth; s++)
				{
					int y2 = mod(y + (t - mheight2), iheight);
					int x2 = mod(x + (s - mwidth2), iwidth);

					sum += mdata[t * mwidth + s] * idata[y2 * iwidth + x2];
				}
			}
			odata[y * iwidth + x] = sum;
		}
	}
}

void filter2(GrayImage &input, GrayImage &output, GrayImage &mask)
{
	int mwidth = mask.getWidth();
	int mheight = mask.getHeight();
	float *mdata = mask.getData();

	int mwidth2 = mwidth / 2;
	int mheight2 = mheight / 2;

	int iwidth = input.getWidth();
	int iheight = input.getHeight();
	float *idata = input.getData();
	float *odata = output.getData();

	float sum;

	for (int y = mheight2; y < iheight - mheight2; y++)
	{
		for (int x = mwidth2; x < iwidth - mwidth2; x++)
		{
			sum = 0.0;
			for (int t = 0; t < mheight; t++)
			{
				for (int s = 0; s < mwidth; s++)
				{
					int y2 = y + (t - mheight2);
					int x2 = x + (s - mwidth2);

					sum += mdata[t * mwidth + s] * idata[y2 * iwidth + x2];
				}
			}
			odata[y * iwidth + x] = sum;
		}
	}
}
enum MaskType
{
	AVERAGING,
	GAUSS,
	GAUSS1D
};
void createMask(MaskType maskType, GrayImage &mask)
{
	int width = mask.getWidth();
	int height = mask.getHeight();
	float *data = mask.getData();

	switch (maskType)
	{
	case AVERAGING:
	{
		int size = mask.getSize();
		float value = 1.0 / size;

		for (int i = 0; i < size; i++)
		{
			data[i] = value;
		}
		break;
	}
	case GAUSS:
	{
		float sigma;
		cout << "Sigma: ";
		cin >> sigma;

		int x0 = width / 2;
		int y0 = height / 2;
		float factor1 = 1.0 / (2.0 * M_PI * sigma * sigma);
		float factor2 = -1.0 / (2.0 * sigma * sigma);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int x1 = x - x0;
				int y1 = y - y0;
				data[y * width + x] = factor1 * expf(factor2 * (x1 * x1 + y1 * y1));
			}
		}
		break;
	}
	case GAUSS1D:
	{
		float sigma;
		cout << "Sigma: ";
		cin >> sigma;

		int x0 = width / 2;
		int y0 = height / 2;
		float factor1 = 1.0 / (sqrtf(2.0 * M_PI) * sigma);
		float factor2 = -1.0 / (2.0 * sigma * sigma);

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int x1 = x - x0;
				int y1 = y - y0;
				data[y * width + x] = factor1 * expf(factor2 * (x1 * x1 + y1 * y1));
			}
		}
		break;
	}
	}
}

void exchange(float &value1, float &value2)
{
	float temp = value1;
	value1 = value2;
	value2 = temp;
}
int minIndex(float *data, int startIdx, int size)
{
	int minIdx = startIdx;
	for (int i = startIdx + 1; i < size; i++)
	{
		if (data[i] < data[minIdx])
			minIdx = i;
	}
	return minIdx;
}
void selectionsort(float *data, int size)
{
	int minIdx;
	for (int i = 0; i < size; i++)
	{
		minIdx = minIndex(data, i, size);
		exchange(data[i], data[minIdx]);
	}
}
void bubblesort(float *data, int size)
{
	bool sortiert = false;
	while (!sortiert)
	{
		bool getauscht = false;
		for (int i = 0; i < size - 1; i++)
		{
			if (data[i] > data[i + 1])
			{
				exchange(data[i], data[i + 1]);
				getauscht = true;
			}
		}
		if (!getauscht)
			sortiert = true;
	}
}

void quicksort(float *data, int leftIdx, int rightIdx)
{
	int l = leftIdx;
	int r = rightIdx;
	float pivot = data[rightIdx];

	if (l < r)
	{
		while (l <= r)
		{
			while (data[l] < pivot)
				l++;
			while (data[r] > pivot)
				r--;
			if (l <= r)
			{
				exchange(data[l], data[r]);
				l++;
				r--;
			}
		}
		quicksort(data, leftIdx, r);
		quicksort(data, l, rightIdx);
	}
}

void sort(GrayImage &input, GrayImage &output, int xpos, int ypos, const int xsize, const int ysize, SortType sortType)
{
	int width = input.getWidth();
	float *idata = input.getData();
	float *odata = output.getData();

	int links = xpos - xsize / 2;
	int oben = ypos - ysize / 2;
	int rechts = xpos + xsize / 2;

	int unten = ypos + ysize / 2;
	float *sortdata = new float[xsize * ysize];

	int count = 0;
	for (int y = oben; y <= unten; y++)
	{
		for (int x = links; x <= rechts; x++)
		{
			sortdata[count] = idata[y * width + x];
		}
	}
	switch (sortType)
	{
	case SELECTIONSORT:
		selectionsort(sortdata, count);
		break;
	case BUBBLESORT:
		bubblesort(sortdata, count);
		break;
	case QUICKSORT:
		quicksort(sortdata, 0, count - 1);
		break;
	}
	odata[ypos * width + xpos] = sortdata[count / 2];
	delete[] sortdata;
}
void filter(GrayImage &input, GrayImage &output, int xsize, int ysize, SortType sortType)
{
	int width = input.getWidth();
	int height = input.getHeight();

	for (int y = ysize / 2; y < height - ysize / 2; y++)
	{
		for (int x = xsize / 2; x < width - xsize / 2; x++)
		{
			sort(input, output, x, y, xsize, ysize, sortType);
		}
	}
}
int main(int argc, char **argv)
{
	/* ************************************ */
	/* Uebung 06                           */
	/* ************************************ */

	/* ************************************ */
	/* Eingabe                              */
	/* ************************************ */
	cout << "Select the following functions: \n";
	cout << "1 - Apply Selectionsort \n";
	cout << "2 - Apply Bubblesort \n";
	cout << "3 - Apply Quicksort \n";

	int choice;
	cin >> choice;

	string filename;
	cout << "Imagename: ";
	cin >> filename;

	int xsize, ysize;
	cout << "Filter size in x (odd): ";
	cin >> xsize;
	cout << "Filter size in y (odd): ";
	cin >> ysize;

	if (xsize % 2 == 0 || ysize % 2 == 0)
	{
		cout << "Filter size not odd!\n";
		cout << "FINISHED.\n";
		return 0;
	}

	GrayImage input;
	input.load();

	/* ************************************ */
	/* Datenverarbeitung / Funktionsaufruf  */
	/* ************************************ */
	GrayImage result = GrayImage(input.getWidth(), input.getHeight());

	switch (choice)
	{
	case 1:
		cout << "Selectionsort started -";
		filter(input, result, xsize, ysize, SELECTIONSORT);
		cout << "finished" << endl;
		break;

	case 2:
		cout << "Bubblesort started - ";
		filter(input, result, xsize, ysize, BUBBLESORT);
		cout << "finished" << endl;
		break;

	case 3:
		cout << "Quick started - ";
		filter(input, result, xsize, ysize, QUICKSORT);
		cout << "finished" << endl;
		break;
	}

	/* ************************************ */
	/* Ausgabe                              */
	/* ************************************ */
	input.show();
	result.show();
	result.save();

	/* ************************************ */
	/* Programmende                         */
	/* ************************************ */

	cout << "FINISHED.\n";
	return 1;
}
