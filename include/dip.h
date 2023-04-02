#pragma once

#include <iostream>
#include <string>
#include <math.h>

#include "basetypes.h"
#include "image.h"

// STL use by default
using namespace std;

/**
 * grayscale image.
 *
 * Each pixel contains a gray value of type float from the range 0.0 ... 255.0
 */
class GrayImage : public GET::Image<float>
{
public:
	/**
	 * Constructor.
	 *
	 * Generates a grayscale image of Width width and Height height.
	 * After creating an image, the values of each pixel are undefined.
	 *
	 * @param width Height of the image to be created
	 * @param height Width of the image to be created
	 *
	 * @see fill
	 */
	GrayImage(int width = 1, int height = 1);

	/**
	 * Fills all pixels of the image with the value Value.
	 *
	 * @param value Value, to which all image pixels should be set
	 */
	void fill(float value);

	/**
	 * Loads the image from the file <filename> into this object.
	 *
	 * @param filename Name of the image file to be loaded.
	 */
	void loadFilterMaskload(string filename);

	/**
	 * Loads an image that can be selected in a file dialog.
	 */
	void load();

	/**
	 * Loads the image from the file <filename> into this object.
	 *
	 * @param filename Name of the image file to be loaded
	 */
	void load(string filename);

	/**
	 * NOT IMPLEMENTED (use save() instead).
	 *
	 * Saves the image (the image data of this object) in the file <filename>.
	 *
	 * @param filename Name of the file in which to save the image.
	 *
	 * @todo Implementation of the GrayImage::save() method
	 */
	void save(string filename);

	/**
	 *	Saves the image under a name that can be selected in a file dialog.
	 */
	void save();

	/**
	 * Displays the image on the screen.
	 */
	void show();

	/**
	 * Displays the image in the given size width x height on the screen.
	 * The image is simply scaled in size.
	 *
	 * @param width Width in which to display the image.
	 * @param height Height at which to display the image.
	 */
	void show(int width, int height);

	/* *********************************************** */
	/* Take over arithmetic operations from GET::Image<> */
	/* *********************************************** */
	GrayImage &add(const GrayImage &image)
	{
		GET::Image<float>::add((GET::Image<float>)image);
		return *this;
	};
	GrayImage &add(float val)
	{
		GET::Image<float>::add(val);
		return *this;
	};
	GrayImage &sub(const GrayImage &image)
	{
		GET::Image<float>::sub((GET::Image<float>)image);
		return *this;
	};
	GrayImage &sub(float val)
	{
		GET::Image<float>::sub(val);
		return *this;
	};
	GrayImage &mul(const GrayImage &image)
	{
		GET::Image<float>::mul((GET::Image<float>)image);
		return *this;
	};
	GrayImage &mul(float val)
	{
		GET::Image<float>::mul(val);
		return *this;
	};
	GrayImage &div(const GrayImage &image)
	{
		GET::Image<float>::div((GET::Image<float>)image);
		return *this;
	};
	GrayImage &div(float val)
	{
		GET::Image<float>::div(val);
		return *this;
	};
};

using GET::Complex;

/**
 * Complex image.
 *
 * Each pixel contains a complex number.
 */
class ComplexImage : public GET::Image<Complex>
{
public:
	/**
	 * Constructor.
	 *
	 * Creates a complex image of Width width and Height height.
	 * After creating an image, the values of each pixel are undefined.
	 *
	 * @param width Height of the image to be created
	 * @param height Width of the image to be created
	 *
	 * @see fill
	 */
	ComplexImage(int width = 1, int height = 1);

	/**
	 * Fills all pixels of the image with the Value value.
	 *
	 * @param value Value to which all image pixels should be set
	 */
	void fill(Complex value);

	/**
	 * Displays the image on the screen.
	 */
	void show();
};

using GET::Rgb;

/**
 * RGB image.
 *
 * Each pixel contains three numbers, the red, green and blue part.
 */
class RgbImage : public GET::Image<Rgb>
{
public:
	/**
	 * Constructor.
	 *
	 * Creates an RGB image of width width and height height. After creating an image, the values of each pixel are undefined.
	 *
	 * @param width Height of the image to be created
	 * @param height Width of the image to be created
	 *
	 * @see fill
	 */
	RgbImage(int width = 1, int height = 1);

	/**
	 * Fills all pixels of the image with the Value value.
	 *
	 * @param value Value to which all image pixels should be set
	 */
	void fill(Rgb value);

	/**
	 * Displays the image on the screen.
	 */
	void show();

	/**
	 * Loads the image from the file <filename> into this object.
	 *
	 * @param filename Name of the image file to be loaded
	 */
	void load(string filename);

	/**
	 * Loads an image that can be selected in a file dialog.
	 */
	void load();

	/**
	 * Saves the image under a name that can be selected in a file dialog.
	 */
	void save();
};

using GET::Hsv;

/**
 * HSV Image.
 *
 * Each pixel contains three numbers, the hue, saturation and value part.
 */
class HsvImage : public GET::Image<Hsv>
{
public:
	/**
	 * Constructor.
	 *
	 * Creates an HSV image of width width and height height. After creating an image, the values of each pixel are undefined.
	 *
	 * @param width Height of the image to be created
	 * @param height Width of the image to be created
	 *
	 * @see fill
	 */
	HsvImage(int width = 1, int height = 1);

	/**
	 * Fills all pixels of the image with the Value value.
	 *
	 * @param value Value to which all image pixels should be set
	 */
	void fill(Hsv value);

	/**
	 * Displays the image on the screen.
	 */
	void show();
};

/**
 * Calculation of the minimum of all shades of gray in the image
 *
 * @param image Image whose minimum gray value is sought
 * @return minimum gray value
 */
float min(GrayImage &image);

/**
 * Calculation of the maximum of all shades of gray in the image
 *
 * @param image Image whose maximum gray value is sought
 * @return maximum gray value
 */
float max(GrayImage &image);

/**
 * Loads a filter mask from a file.
 * In the absence of a separate matrix class,
 * the filter mask is written in an image of type GrayImage.
 *
 * @param filename Name of the file from which the filter mask is loaded
 * @param mask Object of type GrayImage into which the filter mask is loaded
 */
void loadFilterMask(string filename, GrayImage &mask);

/**
 * Saves a filter mask to a file.
 * In the absence of a separate matrix class,
 * the filter mask is passed in the form of an image of type GrayImage.
 *
 * @param mask Object of type GrayImage containing the filter mask
 * @param filename Name of the file in which the filter mask is written
 */
void saveFilterMask(GrayImage &mask, string filename);

/**
 * Computes the remainder of the integer division of a by b.
 *
 * In contrast to a % b, the result is always positive!
 */
int mod(int a, int b);

/* ********* Discrete Fourier Transform */
void fourier_transform(const ComplexImage &input, ComplexImage &output);
void inverse_fourier_transform(const ComplexImage &input, ComplexImage &output);
void fourier_transform(const GrayImage &input, ComplexImage &output);
void inverse_fourier_transform(const ComplexImage &input, GrayImage &output);

void real_part(const ComplexImage &input, GrayImage &output);
void imag_part(const ComplexImage &input, GrayImage &output);

void fourier_spectrum(const ComplexImage &input, GrayImage &output);
void log_transform(GrayImage &image, float alpha = 1.0);
void fourier_center(GrayImage &image);
void fourier_center(ComplexImage &image);
