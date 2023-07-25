#pragma once

#include "standardoutput.h"
#include "complex.h"

/**
 * Namespace of all classes of the GETLib - software library.
 */
namespace GET
{

	/**
	 * Basic data type for gray value images.
	 *
	 * Each pixel of an image of a grayscale image with
	 * this base data type (Image<uchar>) is of the uchar type.
	 *
	 * Gray value images exist with the basic data types uchar or float.
	 *
	 * @author Holger T�ubig
	 */
	typedef unsigned char uchar;
}



namespace GET
{

	struct Hsv;
	/**
	 * Basic data type for images in the RGB color space.
	 *
	 * Each pixel of an RGB image (Image<Rgb>) is of type Rgb.
	 * The class implements the most important operations for
	 * converting a pixel from and to the RGB color space.
	 *
	 * @author Holger T�ubig
	 *
	 * @todo Adding more conversions
	 */
	struct Rgb
	{
		/** Red value of the RGB pixel (value range 0..255). */
		uchar r;
		/** Green value of the RGB pixel (value range 0..255). */
		uchar g;
		/** Blue value of the RGB pixel (value range 0..255). */
		uchar b;

		/**
		 * Color space conversion gray value -> RGB.
		 *
		 * Operator to convert a pixel from gray value (float) to Rgb.
		 *
		 * @param src Pixels as gray value
		 * @return Pixels as RGB value
		 */
		inline Rgb &operator=(const float &src)
		{
			r = g = b = (uchar)src;
			return *this;
		}

		/**
		 * Color space conversion RGB -> gray value.
		 *
		 * Operator to convert a pixel from Rgb to gray value (uchar).
		 *
		 * @return Pixel as gray value (uchar)
		 */
		inline operator uchar()
		{
			return (uchar)(0.212671f * r + 0.715160f * g + 0.072169f * b); // Formula from the OpenCV documentation
																		   // return (uchar) (0.3f * r + 0.59f * g + 0.11f * b); //Formula from www.wikipedia.de -> gray value
		}

		/**
		 * Color space conversion RGB -> gray value.
		 *
		 * Operator to convert a pixel from Rgb to gray value (float).
		 *
		 * @return Pixel as gray value (float)
		 */
		inline operator float()
		{
			return (0.212671f * r + 0.715160f * g + 0.072169f * b); // Formula from the OpenCV documentation
																	// return (0.3f * r + 0.59f * g + 0.11f * b); 	//Formula from www.wikipedia.de -> gray value
		}

		/**
		 * Color space conversion HSV -> RGB.
		 *
		 * Operator to convert a pixel from hsv to rgb.
		 *
		 * @param src Pixels as HSV value
		 * @return Pixels as RGB value
		 */
		inline Rgb &operator=(const Hsv &hsv);

		/**
		 * Addition.
		 *
		 * @param add value to be added
		 * @return Value of the complex number after adding add
		 */
		inline Rgb &operator+=(const Rgb &add)
		{
			r += add.r;
			g += add.g;
			b += add.b;
			return *this;
		}
	};

	/**
	 * Basic data type for images in the HSV color space.
	 *
	 * Each pixel of an HSV image (Image<Hsv>) is of type Hsv.
	 * The class implements the most important operations for
	 * converting a pixel from and to the HSV color space.
	 *
	 * @author Holger T�ubig
	 *
	 * @todo Adding more conversions
	 */
	struct Hsv
	{
		/**
		 *  Hue (value range 0..180).
		 *
		 * The value of the hue corresponds to half the color angle.
		 * This specification was made so that the hue can be stored
		 * in a variable of type uchar.
		 */
		uchar h;
		/**
		 * Saturation (value range 0..255).
		 */
		uchar s; // 0..255
		/**
		 * Brightness (value range 0..255).
		 */
		uchar v; // 0..255

		/**
		 * Color space conversion gray value -> HSV.
		 *
		 * Operator to convert a pixel from gray value (uchar) to hsv.
		 *
		 * @param src Pixels as gray value
		 * @return Pixels as HSV value
		 */
		inline Hsv &operator=(const uchar &src)
		{
			v = src;
			s = 0;
			h = 0;
			return *this;
		}

		/**
		 * Color space conversion gray value -> HSV.
		 *
		 * Operator to convert a pixel from gray value (float) to Hsv.
		 *
		 * @param src Pixels as gray value
		 * @return Pixels as HSV value
		 */
		inline Hsv &operator=(const float &src)
		{
			v = (uchar)src;
			s = 0;
			h = 0;
			return *this;
		}

		/**
		 * Color space conversion RGB -> HSV.
		 *
		 * Operator to convert a pixel from Rgb to Hsv.
		 *
		 * @param rgb Pixels as RGB value
		 * @return Pixels as HSV value
		 */
		inline Hsv &operator=(const Rgb &rgb)
		{
			// Determine max(r,g,b) and min(r,g,b).
			uchar max, min;
			uchar max_case;
			if (rgb.r > rgb.g)
			{
				max = rgb.r;
				min = rgb.g;

				max_case = 1;
			}
			else
			{
				max = rgb.g;
				min = rgb.r;

				max_case = 2;
			}
			if (rgb.b > max)
			{
				max = rgb.b;

				max_case = 3;
			}
			else if (rgb.b < min)
			{
				min = rgb.b;
			}

			// Calculation for h,s,v from the OpenCV documentation
			v = max;
			if (max != 0)
			{
				s = (uchar)(((max - min) * (unsigned int)255) / max);

				if (s != 0)
				{
					int h1;
					switch (max_case)
					{
					case 1:
						h1 = ((int)(rgb.g - rgb.b) * (int)60) / s;
						break;
					case 2:
						h1 = 120 + ((int)(rgb.b - rgb.r) * (int)60) / s;
						/* OpenCV documentation: 180 probably wrong!!! */
						break;
					case 3:
						h1 = 240 + ((int)(rgb.r - rgb.g) * (int)60) / s;
						break;
					default:
						h1 = 0; // this case cannot occur
								// only available to prevent a compiler warning
					};
					if (h1 < 0)
						h1 += 360;
					h = (uchar)(h1 / 2); // Adaptation since h is in the range 0..180
				}
				else
					h = 0;
			}
			else
			{
				s = 0;
				h = 0;
			}

			return *this;
		}
	};

	/**
	 * Color space conversion gray value -> RGB.
	 *
	 * Operator to convert a pixel from gray value (uchar) to Rgb.
	 *
	 * @param src Pixels as gray value
	 * @return Pixels as RGB value
	 */
	/*inline Rgb& operator=( const uchar &src )
	{
		r = g = b = src;
		return *this;
	}*/

	/**
	 * conversion Hsv -> Rgb.

	 * Inversion of RGB -> HSV in 6 cases; adapted to the value ranges
	 * h (0..180), s (0..255), v (0..255) [ Declaration of Hsv / OpenCV documentation]
	 */
	inline Rgb &Rgb::operator=(const Hsv &hsv)
	{
		if (hsv.s == 0)
		{
			/*
			 * gray values
			 */
			r = g = b = hsv.v;
		}
		else
		{
			/*
			copy values
			 */
			uchar v = hsv.v;
			unsigned int s = hsv.s;
			unsigned int h1 = 2 * hsv.h; // Adaptation since h is in the range 0..180
			/*
			determine the minimum
			 */
			unsigned int min = v - (v * s) / 255;

			/*
			TEST: range of values hsv.h
			 */
			if (h1 > 360)
			{
				gerr << "Runtime error in Rgb& Rgb::operator=( const Hsv &hsv )" << std::endl;
				gerr << "hsv.h out of range" << std::endl;

				// ERROR CORRECTION
				h1 -= 360;
			}

			/*
			calculate depending on the color sector
			 */
			if (h1 >= 300)
			{
				r = v;
				g = (uchar)min;
				b = (uchar)(g + ((360 - h1) * s) / 60);
			}
			else if (h1 >= 240)
			{
				b = v;
				g = (uchar)min;
				r = (uchar)(g + ((h1 - 240) * s) / 60);
			}
			else if (h1 >= 180)
			{
				b = v;
				r = (uchar)min;
				g = (uchar)(r + ((240 - h1) * s) / 60);
			}
			else if (h1 >= 120)
			{
				g = v;
				r = (uchar)min;
				b = (uchar)(r + ((h1 - 120) * s) / 60);
			}
			else if (h1 >= 60)
			{
				g = v;
				b = (uchar)min;
				r = (uchar)(b + ((120 - h1) * s) / 60);
			}
			else
			{
				r = v;
				b = (uchar)min;
				g = (uchar)(b + (h1 * s) / 60);
			}
		}

		return *this;
	}

} /* namespace GET */
