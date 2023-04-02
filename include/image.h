#pragma once

#include "basetypes.h"

namespace GET
{

	/** Image.
	 *
	 * This template represents the basic implementation for all image classes.
	 * Various image types are created by passing a base data type of the image
	 * when instantiating the template. The base data type indicates the data type
	 * of an individual pixel of the image. See basetypes.h for a list of possible base data types.
	 *
	 * @author Holger T�ubig
	 *
	 * @todo Rename base data type to pixeltype?
	 *
	 * @bug Failed to test image sizes in some methods (add)
	 */
	template <typename Typ>
	class Image
	{
	protected:
		/** Width of the image */
		int m_width;
		/** Height of the image */
		int m_height;
		/** Number of pixels of the image (height*width) */
		int m_size;
		/** Pointer to the image data.
		 *
		 * The image data is stored pixel by pixel. The individual lines of the image
		 * are written one after the other without a gap. This pointer points to an array
		 * of size m_size that contains elements of the image's base data type.
		 */
		Typ *m_data;
		/** This flag indicates whether the memory for m_data is managed by this object (through the Image<> class).
		 *
		 * The flag is usually true. This means that the memory for m_data was allocated by
		 * the constructor of this object and is released again by the destructor of this object.
		 * If this flag is false, the memory for m_data was allocated outside of this object and
		 * passed to this object using the constructor Image(int width,int height,type* data).
		 * In this case, the memory area of m_data is NOT freed by the destructor of this object.
		 * This must be done outside of this object.
		 */
		const bool m_data_owner;

	public:
		/** Base data type of the image.
		 *
		 * The base data type indicates the data type of an individual pixel of the image.
		 */
		typedef Typ BaseType; // aliasing BaseType as Typ

		/** Constructor.
		 *
		 * Creates an image with Width width and Height height.
		 *
		 * @param width  Width of the image to be created
		 * @param height Height of the image to be created
		 */
		inline Image(int width = 0, int height = 0); // inline used to reduce compile time. The definition is copied at the smae place when the function is called.

		/** Destructor.
		 *
		 * The array with the saved image data is deleted
		 * (exception: see Image(int width,int height,Typ* data) or m_data_owner).
		 * This image data can then no longer be accessed. This also applies if
		 * the pointer to the image data was previously saved.
		 */
		inline ~Image();

		/** Copy-Constructor.
		 *
		 * Creates a copy of the passed image.
		 * The image data is copied. This constructor therefore does not create a
		 * reference to the passed image or the data of the passed image.
		 *
		 * @param image image to be copied
		 */
		inline Image(const Image<Typ> &image); // must be specified separately according to the C++ specification

		/** Copy constructor that creates a copy while converting the image type.
		 *
		 * Creates a copy of the passed image. The image data are converted from the color
		 * space of the transferred image into that of the image to be created.
		 *
		 * @param image image to be copied
		 *
		 * @see List of possible base data types in basetypes.h
		 */
		template <typename OriginalTyp>
		inline Image(const Image<OriginalTyp> &image);

		/** Copy constructor that creates a copy of an image section and
		 * can convert the image type in the process.
		 *
		 * Creates a copy of a section of the given image. The image data can be converted
		 * from the color space of the transferred image into that of the image to be created.
		 *
		 * @param image image to be copied
		 * @param x0     X coordinate of the upper left corner of the image section to be copied
		 * @param y0     Y coordinate of the top left corner of the image section to be copied
		 * @param width  Width of the image section to be copied
		 * @param height Height of the image section to be copied
		 *
		 * @see List of possible base data types in basetypes.h
		 */
		template <typename OriginalTyp>
		inline Image(const Image<OriginalTyp> &image, int x0, int y0, int width, int height);

		/** Returns the width of the image.
		 *
		 * @return Width of the image
		 * @see m_width
		 */
		inline int getWidth() const { return m_width; };

		/** Returns the Height of the image.
		 *
		 * @return Height of the image
		 * @see m_height
		 */
		inline int getHeight() const { return m_height; };

		/** Returns the pixel count of the image.
		 *
		 * @return Number of pixels in the image
		 * @see m_size
		 */
		inline int getSize() const { return m_size; };

		/** Resize image.
		 *
		 * The width and height of the image are changed. The image data will be lost!!!
		 * (The image data is only retained if the number of image pixels does not change,
		 * i.e. if the height*width remains constant).
		 *
		 * @param width  new width of the image
		 * @param height new height of the image
		 */
		inline void resize(int width, int height);

		/** Change the width of the image.
		 *
		 * The image data will be lost!!!
		 *
		 * \see getSize
		 */
		inline void setWidth(int width) { resize(width, m_height); };

		/** Change the height of the image.
		 *
		 * The image data will be lost!!!
		 *
		 * \see getSize
		 */
		inline void setHeight(int height) { resize(m_width, height); };

		/** Returns the pointer to the image data.
		 *
		 * \see m_data
		 */
		inline BaseType *getData() const { return m_data; };

		/** Copies an image including conversion of the image type.
		 *
		 * Copies the passed image. The image data is converted from the
		 * color space of the transferred image into the type of this image.
		 *
		 * @param image image to be copied
		 * @return this object
		 *
		 * @see List of possible base data types in basetypes.h
		 */
		template <typename OriginalTyp> // template evaluates at compile time. Based on how we call it, it will create it's type.
		Image<Typ> &copy(const Image<OriginalTyp> &image);

		/** Copies a section of an image including conversion of the image type.
		 *
		 * Copies a section of the given image. The image data can be converted
		 * from the color space of the transferred image into the type of this image.
		 *
		 * @param image image to be copied
		 * @param x0     X coordinate of the upper left corner of the image section to be copied
		 * @param y0     Y coordinate of the top left corner of the image section to be copied
		 * @param width  Width of the image section to be copied
		 * @param height Height of the image section to be copied
		 * @return this object
		 *
		 * @see List of possible base data types in basetypes.h
		 */
		template <typename OriginalTyp>
		Image<Typ> &copy(const Image<OriginalTyp> &image, int x0, int y0, int width, int height);

		/** pointwise addition of an image.
		 *
		 * @param image image to add
		 * @return this image after adding image
		 */
		Image<Typ> &add(const Image<Typ> &image);

		/** pointwise subtraction of an image.
		 *
		 * @param image image to be subtracted
		 * @return this image after subtracting image
		 */
		Image<Typ> &sub(const Image<Typ> &image);

		/** pointwise multiplication of an image.
		 *
		 * @param image image to be multiplied
		 * @return this image after multiplication by image
		 */
		Image<Typ> &mul(const Image<Typ> &image);

		/** pointwise division by an image.
		 *
		 * @param image Image to divide by
		 * @return this image after dividing by image
		 */
		Image<Typ> &div(const Image<Typ> &image);

		template <typename ValueType>
		Image<Typ> &add(const ValueType &image);
		template <typename ValueType>
		Image<Typ> &sub(const ValueType &image);
		template <typename ValueType>
		Image<Typ> &mul(const ValueType &image);
		template <typename ValueType>
		Image<Typ> &div(const ValueType &image);

		/** Point by point addition of two images whereby the result is to be written in a third image (this object).
		 *
		 * @param img1 image
		 * @param img2 image to add
		 * @return the image (into which the result is written)
		 *
		 * @todo test method
		 * @todo Compare/test whether an implementation using copy(img1) and add(img2) is += faster.
		 */
		Image<Typ> &add(const Image<Typ> &img1, const Image<Typ> &img2);

		/** pointwise subtraction of two images where the result should be written in a third image (this object).
		 *
		 * @param img1 image
		 * @param img2 image to subtract
		 * @return the image (into which the result is written)
		 *
		 * @todo test method
		 * @todo Compare/test whether an implementation using copy(img1) and sub(img2) is -= faster.
		 */
		Image<Typ> &sub(const Image<Typ> &img1, const Image<Typ> &img2);

		/** pointwise multiplication of two images where the result should be written in a third image (this object).
		 *
		 * @param img1 image
		 * @param img2 image to multiply
		 * @return the image (into which the result is written)
		 *
		 * @todo test method
		 * @todo Compare/test whether an implementation using copy(img1) and mul(img2) is *= faster.
		 */
		Image<Typ> &mul(const Image<Typ> &img1, const Image<Typ> &img2);

		/** pointwise division of an image by another image where the result is to be written in a third image (this object).
		 *
		 * @param img1 image
		 * @param img2 Image to divide by
		 * @return the image (into which the result is written)
		 *
		 * @todo test method
		 * @todo Compare/test whether an implementation using copy(img1) and div(img2) i.e. /= is faster.
		 */
		Image<Typ> &div(const Image<Typ> &img1, const Image<Typ> &img2);

		/**
		 * Fills all pixels of the image with the given value.
		 *
		 * @param value Value to be written into each image pixel.
		 * @return this image after it has been filled
		 */
		template <typename ValueType>
		Image<Typ> &fill(const ValueType &value);

	private:
		/** Assignment operator is NOT APPLICABLE.
		 *
		 * Assignment operator is private and can no longer be used.
		 * This was introduced to prevent false object copies from being created.
		 *
		 * Copying an object is possible with the copy constructors or the copy method.
		 *
		 * @see Image()
		 * @see copy()
		 * */
		Image<Typ> &operator=(const Image<Typ> &);

	protected:
		/** Special constructor that can only be used by derived classes.
		 *
		 *  This constructor allocates #no memory# for m_data.
		 *  However, if the data_owner flag is set to true,
		 *  the Image<> class still takes care of freeing the memory.
		 *
		 *  This constructor is used, for example, to create the ImageReference class,
		 * which creates image objects with a different data management.
		 *
		 * @param width  Width of the image to be created
		 * @param height Height of the image to be created
		 * @param data_owner This flag indicates whether the memory for m_data is managed by the Image<> class.
		 */
		inline Image(int width, int height, bool data_owner);
	};

	template <typename Typ>
	inline Image<Typ>::Image(int width, int height) : m_width(width),
													  m_height(height),
													  m_size(width * height),
													  m_data(NULL),
													  m_data_owner(true)
	{
		m_data = new Typ[m_size];
	}

	template <typename Typ>
	template <typename OriginalTyp>
	inline Image<Typ>::Image(const Image<OriginalTyp> &image) : m_width(image.getWidth()),
																m_height(image.getHeight()),
																m_size(image.getSize()),
																m_data(NULL),
																m_data_owner(true)
	{
		m_data = new Typ[m_size];
		copy(image);
	}

	// According to the C++ specification, OriginalTyp=Typ must be specified separately
	template <typename Typ>
	inline Image<Typ>::Image(const Image<Typ> &image) : m_width(image.getWidth()),
														m_height(image.getHeight()),
														m_size(image.getSize()),
														m_data(NULL),
														m_data_owner(true)
	{
		m_data = new Typ[m_size];
		copy(image);
	}

	template <typename Typ>
	template <typename OriginalTyp>
	inline Image<Typ>::Image(const Image<OriginalTyp> &image, int x0, int y0, int width, int height) : m_width(width),
																									   m_height(height),
																									   m_size(width * height),
																									   m_data(NULL),
																									   m_data_owner(true)
	{
		m_data = new Typ[m_size];
		copy(image, x0, y0, width, height);
	}

	template <typename Typ>
	inline Image<Typ>::Image(int width, int height, bool data_owner) : m_width(width),
																	   m_height(height),
																	   m_size(width * height),
																	   m_data(NULL),
																	   m_data_owner(data_owner)
	{
	}

	template <typename Typ>
	inline Image<Typ>::~Image()
	{
		if (m_data_owner && m_data)
			delete[] m_data;
	}

	template <typename Typ>
	inline void Image<Typ>::resize(int width, int height)
	{
		if (m_size == width * height)
		{
			m_width = width;
			m_height = height;
		}
		else if (m_data_owner)
		{
			if (m_data)
				delete m_data;

			m_width = width;
			m_height = height;
			m_size = width * height;

			m_data = new Typ[m_size];
		}
		else
		{
			// Resize is not allowed if image data storage is not managed by this object
			gerr << "Runtime error in Image<Typ>::resize( int width, int height )" << std::endl;
			gerr << "This object must not manage the image data storage itself (m_data_owner==false). ";
			gerr << "It is probably an ImageReference type object. ";
			gerr << "For this reason, any resize() call that leads to a reallocation of memory is forbidden." << std::endl;
		}
	}

	/* Template copy 1 */
	template <typename Typ>
	template <typename OriginalTyp>
	Image<Typ> &Image<Typ>::copy(const Image<OriginalTyp> &image)
	{
		resize(image.getWidth(), image.getHeight());

		Typ *destination = m_data;
		OriginalTyp *source = image.getData();

		int size = m_size;
		for (int i = 0; i < size; ++i)
		{
			//		destination[i] = (Typ) source[i];
			destination[i] = source[i];
		}

		return *this;
	}
	/* specialization copy 1 */
	template <>
	template <>
	Image<uchar> &Image<uchar>::copy(const Image<float> &image);

	/* Template copy 2 */
	template <typename Typ>
	template <typename OriginalTyp>
	Image<Typ> &Image<Typ>::copy(const Image<OriginalTyp> &image, int x0, int y0, int width, int height)
	{
		//
		// Determine the size of the original image
		//
		int source_width = image.getWidth();
		int source_height = image.getHeight();

		//
		// TEST: size of the subarea
		//
		if (x0 + width > source_width)
		{
			// Warning(
			//	"Image<Typ>::copy( const Image<OriginalTyp> &image, int x0, int y0, int width, int height )",
			//	"Specified portion outside of the image (x0+width > image.getWidth())"
			//	);
			gerr << "runtime error in Image<Typ>::copy( const Image<OriginalTyp> &image, int x0, int y0, int width, int height )\n";
			gerr << "Specified portion outside of the image (x0+width > image.getWidth())\n";

			// FEHLERKORREKTUR
			width = source_width - x0;
		}
		if (y0 + height > source_height)
		{
			// Warning(
			//	"Image<Typ>::copy( const Image<OriginalTyp> &image, int x0, int y0, int width, int height )",
			//	"Specified portion outside of the image (y0+height > image.getHeight())"
			//	);
			gerr << "runtime error in Image<Typ>::copy( const Image<OriginalTyp> &image, int x0, int y0, int width, int height )\n";
			gerr << "Specified portion outside of the image (y0+height > image.getHeight())\n";

			// ERROR CORRECTION
			height = source_height - y0;
		}

		//
		// Copy sub-image
		//
		resize(width, height);

		Typ *destination = m_data;
		OriginalTyp *source = image.getData();
		OriginalTyp *source_p;

		source += y0 * source_width + x0; // Set source to position x0 of line y0
		for (int y = 0; y < height; ++y)
		{
			source_p = source;				// Set source_p to position x0 of the current line
			for (int x = 0; x < width; ++x) // copy width elements
			{
				//			*destination = (Typ) (*source_p);
				*destination = *source_p;

				++destination; // Increment destination after each copied element
				++source_p;
			}
			source += source_width; // move source by one line
		}

		return *this;
	}

	/* specialization copy2 */
	template <>
	template <>
	Image<uchar> &Image<uchar>::copy(const Image<float> &image, int x0, int y0, int width, int height);

	template <typename Typ>
	Image<Typ> &Image<Typ>::add(const Image<Typ> &image)
	{
		//
		// TEST: Images must be the same size
		//
		if ((m_width != image.getWidth()) && (m_height != image.getHeight()))
		{
			gerr << "runtime error in Image<Typ>::add( const Image<typ> &image )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		Typ *destination = m_data;
		Typ *destination_end = destination + m_size;
		Typ *source = image.getData();

		while (destination != destination_end)
		{
			*destination += *source;

			++destination;
			++source;
		}

		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::sub(const Image<Typ> &image)
	{
		//
		// TEST: Images must be the same size
		//
		if ((m_width != image.getWidth()) && (m_height != image.getHeight()))
		{
			gerr << "runtime error in Image<Typ>::sub( const Image<typ> &image )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		Typ *destination = m_data;
		Typ *destination_end = destination + m_size;
		Typ *source = image.getData();

		while (destination != destination_end)
		{
			*destination -= *source;

			++destination;
			++source;
		}

		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::mul(const Image<Typ> &image)
	{
		//
		// TEST: Bilder muessen gleich gross sein
		//
		if ((m_width != image.getWidth()) && (m_height != image.getHeight()))
		{
			gerr << "runtime error in Image<Typ>::mul( const Image<typ> &image )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		Typ *destination = m_data;
		Typ *destination_end = destination + m_size;
		Typ *source = image.getData();

		while (destination != destination_end)
		{
			*destination *= *source;

			++destination;
			++source;
		}

		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::div(const Image<Typ> &image)
	{
		//
		// TEST: Images must be the same size
		//
		if ((m_width != image.getWidth()) && (m_height != image.getHeight()))
		{
			gerr << "runtime error in Image<Typ>::div( const Image<typ> &image )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		Typ *destination = m_data;
		Typ *destination_end = destination + m_size;
		Typ *source = image.getData();

		while (destination != destination_end)
		{
			*destination /= *source;

			++destination;
			++source;
		}

		return *this;
	}

	template <typename Typ>
	template <typename ValueType>
	Image<Typ> &Image<Typ>::add(const ValueType &value)
	{

		Typ *data = m_data;
		Typ *data_end = data + m_size;

		while (data != data_end)
		{
			*data += value;
			++data;
		}

		return *this;
	}

	template <typename Typ>
	template <typename ValueType>
	Image<Typ> &Image<Typ>::sub(const ValueType &value)
	{

		Typ *data = m_data;
		Typ *data_end = data + m_size;

		while (data != data_end)
		{
			*data -= value;
			++data;
		}

		return *this;
	}

	template <typename Typ>
	template <typename ValueType>
	Image<Typ> &Image<Typ>::mul(const ValueType &value)
	{

		Typ *data = m_data;
		Typ *data_end = data + m_size;

		while (data != data_end)
		{
			*data *= value;
			++data;
		}

		return *this;
	}

	template <typename Typ>
	template <typename ValueType>
	Image<Typ> &Image<Typ>::div(const ValueType &value)
	{

		Typ *data = m_data;
		Typ *data_end = data + m_size;

		while (data != data_end)
		{
			*data /= value;
			++data;
		}

		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::add(const Image<Typ> &img1, const Image<Typ> &img2)
	{
		//
		// TEST: Images must be the same size
		//
		int width = img1.getWidth();
		int height = img1.getHeight();

		if ((width != img2.getWidth()) || (height != img2.getHeight()))
		{
			gerr << "runtime error in Image<Typ>& Image<Typ>::add( const Image<Typ> &img1, const Image<Typ> &img2 )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		//
		// Resize the resulting image (this object).
		//
		if ((width != m_width) || (height != m_height))
		{
			resize(width, height);
		}

		//
		// Perform operation
		//
		Typ *res = m_data;
		Typ *data1 = img1.getData();
		Typ *data2 = img2.getData();

		int size = m_size;

		for (int i = 0; i < size; ++i)
		{
			res[i] = data1[i] + data2[i];
		}

		//
		// finished
		//
		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::sub(const Image<Typ> &img1, const Image<Typ> &img2)
	{
		//
		// TEST: Images must be the same size
		//
		int width = img1.getWidth();
		int height = img1.getHeight();

		if ((width != img2.getWidth()) || (height != img2.getHeight()))
		{
			gerr << "runtime error in Image<Typ>& Image<Typ>::add( const Image<Typ> &img1, const Image<Typ> &img2 )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		//
		// Resize the resulting image (this object)
		//
		if ((width != m_width) || (height != m_height))
		{
			resize(width, height);
		}

		//
		// Perform operation
		//
		Typ *res = m_data;
		Typ *data1 = img1.getData();
		Typ *data2 = img2.getData();

		int size = m_size;

		for (int i = 0; i < size; ++i)
		{
			res[i] = data1[i] - data2[i];
		}

		//
		// finished
		//
		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::mul(const Image<Typ> &img1, const Image<Typ> &img2)
	{
		//
		// TEST: Images must be the same size
		//
		int width = img1.getWidth();
		int height = img1.getHeight();

		if ((width != img2.getWidth()) || (height != img2.getHeight()))
		{
			gerr << "runtime error in Image<Typ>& Image<Typ>::add( const Image<Typ> &img1, const Image<Typ> &img2 )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		//
		// Resize the resulting image (this object)
		//
		if ((width != m_width) || (height != m_height))
		{
			resize(width, height);
		}

		//
		// Perform operation
		//
		Typ *res = m_data;
		Typ *data1 = img1.getData();
		Typ *data2 = img2.getData();

		int size = m_size;

		for (int i = 0; i < size; ++i)
		{
			res[i] = data1[i] * data2[i];
		}

		//
		// finished
		//
		return *this;
	}

	template <typename Typ>
	Image<Typ> &Image<Typ>::div(const Image<Typ> &img1, const Image<Typ> &img2)
	{
		//
		// TEST: Images must be the same size
		//
		int width = img1.getWidth();
		int height = img1.getHeight();

		if ((width != img2.getWidth()) || (height != img2.getHeight()))
		{
			gerr << "runtime error in Image<Typ>& Image<Typ>::add( const Image<Typ> &img1, const Image<Typ> &img2 )" << std::endl;
			gerr << "The images are not the same size" << std::endl;

			// NO ERROR CORRECTION possible -> do not change object
			return *this;
		}

		//
		// Resize the resulting image (this object)
		//
		if ((width != m_width) || (height != m_height))
		{
			resize(width, height);
		}

		//
		// Perform operation
		//
		Typ *res = m_data;
		Typ *data1 = img1.getData();
		Typ *data2 = img2.getData();

		int size = m_size;

		for (int i = 0; i < size; ++i)
		{
			res[i] = data1[i] / data2[i];
		}

		//
		// finished
		//
		return *this;
	}

	template <typename Typ>
	template <typename ValueType>
	Image<Typ> &Image<Typ>::fill(const ValueType &value)
	{

		Typ *data = m_data;
		Typ *data_end = data + m_size;

		while (data != data_end)
		{
			*data = value;
			++data;
		}

		return *this;
	}

} /* namespace GET */
