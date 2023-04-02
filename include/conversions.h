#pragma once

#include "image.h"
#include "imagesequence.h"
#include "gvector.h"

namespace GET
{

	/**
	 * Conversions and other image adjustments such as generating phase or amplitude images from complex images or automatic scaling of the value range of an image.
	 *
	 * Auxiliary functions for converting different images (Image<TYPE>) that cannot be performed automatically.
	 *
	 * @author Holger T�ubig
	 * @version PRELIMINARY DONE.
	 */
	class Conversions
	{
	public:
		/**
		 * Determination of the magnitude image of a complex image.
		 *
		 * Among other things, this method can be used to determine the Fourier spectrum
		 * of a Fourier transform (the Fourier spectrum is the magnitude image of
		 * the complex Fourier transform).
		 *
		 * @param image complex image (input)
		 * @param magnitude_image Featured image by image (Output)
		 */
		static void doComplex2Magnitude(const Image<Complex> &image, Image<float> &magnitude_image);

		/**
		 * Determination of the phase image of a complex image.
		 *
		 * @param image complex image (input)
		 * @param phase_image phase image of image (output)
		 */
		static void doComplex2Phase(const Image<Complex> &image, Image<float> &phase_image);

		/**
		 * Determination of the real part of a complex image.
		 *
		 * @param image complex image (input)
		 * @param real_image real part of image (output)
		 */
		static void doComplex2Real(const Image<Complex> &image, Image<float> &real_image);

		/**
		 * Finding the imaginary part of a complex image.
		 *
		 * @param image complex image (input)
		 * @param imaginary_image imaginary part of image (output)
		 */
		static void doComplex2Imaginary(const Image<Complex> &image, Image<float> &imaginary_image);

		/**
		 * Determination of the amount images of all images of the transferred sequence.
		 *
		 * @param input complex images (input)
		 * @param output Amount screens (output)
		 */
		static void doComplex2Magnitude(const ImageSequence<Complex> &input, ImageSequence<float> &output);

		/**
		 * Determination of the phase images of all images of the transferred sequence.
		 *
		 * @param input complex images (input)
		 * @param output Phase Images (Output)
		 */
		static void doComplex2Phase(const ImageSequence<Complex> &input, ImageSequence<float> &output);

		/**
		 * Determination of the real part of all images of the transferred sequence.
		 *
		 * @param input complex images (input)
		 * @param output Real parts of the images (output)
		 */
		static void doComplex2Real(const ImageSequence<Complex> &input, ImageSequence<float> &output);

		/**
		 * Determination of the imaginary parts of all images of the given sequence.
		 *
		 * @param input complex images (input)
		 * @param output Imaginary parts of the images (output)
		 */
		static void doComplex2Imaginary(const ImageSequence<Complex> &input, ImageSequence<float> &output);

		/**
		 * Calculates the complex conjugate of the image pixels.
		 *
		 * @param input complex-valued image
		 * @param output Image in which each pixel contains the conjugate complex value of
		 * the corresponding pixel of the input image.
		 */
		static void doComputeComplexConjugate(const Image<Complex> &input, Image<Complex> &output);

		/**
		 * Absolute value of the picture.
		 *
		 * Each pixel value is replaced by the absolute value of its value (always positive).
		 */
		static void doAbsImage(Image<float> &image);

		/**
		 * Automatic scaling of an image
		 *
		 * The image is scaled to the range [0.255].
		 */
		static void doAutomaticScaling(Image<float> &image);

		/**
		 * Returns the x-components of the given vector field.
		 */
		static void doVector2X(const Image<Vector2D> &input, Image<float> &output);
		/**
		 * Returns the y-components of the given vector field.
		 */
		static void doVector2Y(const Image<Vector2D> &input, Image<float> &output);
		/**
		 * Creates a vector field from x and y components.
		 */
		static void doXY2Vector(const Image<float> &input_x, const Image<float> &input_y, Image<Vector2D> &output_vector);

		/**
		 * Determination of the x-components of all images of the given sequence.
		 *
		 * @param input Vector images (input)
		 * @param output x component images (output)
		 */
		static void doVector2X(const ImageSequence<Vector2D> &input, ImageSequence<float> &output);
		/**
		 * Determination of the y-components of all images of the given sequence.
		 *
		 * @param input Vector images (input)
		 * @param output y component images (output)
		 */
		static void doVector2Y(const ImageSequence<Vector2D> &input, ImageSequence<float> &output);
		/**
		 * Creates a vector field from x and y components for image sequences).
		 */
		static void doXY2Vector(const ImageSequence<float> &input_x, const ImageSequence<float> &input_y, ImageSequence<Vector2D> &output_vector);
	};

} //_CONVERSIONS_H_
