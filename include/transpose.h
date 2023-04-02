#pragma once
#include "image.h"
#include "standardoutput.h"
#include "gexception.h"


namespace GET 
{


/**
 * Transposes an image (reflection about the main axis)
 * 
 * @author Holger Täubig
 * @version COMPLETE.
 */
class Transpose
{
  public:
  	/**
  	 * Transposes the given image.
  	 * Input image and transposed output image are in two different objects.
  	 * 
  	 * @param image Original image (Input)
  	 * @param transpose transposed image (Output)
  	 */
  	template<typename TYP> void doTranspose( const Image<TYP> &image, Image<TYP> &transpose );

  	/**
  	 * Transposes the given square image. 
  	 * The operation is performed within the transferred image. This means 
  	 * that the result is written back to the original image. 
  	 * 
  	 * This method can only be used for square images. 
  	 * An exception is thrown for non-square images.
  	 * 
  	 * @param image Original image when calling the function. When you exit the function, 
  	 * the transposed image is here. 
  	 */
  	template<typename TYP> void doTranspose( Image<TYP> &image );  	
};



/* **************************************** */
/* Transpose square images in an image*/
/* **************************************** */
template<typename TYP> 
void Transpose::doTranspose( Image<TYP> &image )
{
	int 	 width = image.getWidth();
	TYP 	*data  = image.getData();
	
	//
	// TEST: Transpose in an image for square images only
	//
	if ( width!=image.getHeight() )
	{
		// no ERROR CORRECTION possible
		throw GException(
			"Transpose::doTranspose( Image<TYP> &image )",
			"Image is not square"
			);
	};
	
	//
	// Transpose
	//
	TYP *x; 	// used as a pointer to pixels (x,nr)
	TYP *y; 	// used as a pointer to pixels (nr,y)
	for ( int nr=1; nr<width; ++nr )
	{
		x = data+1;
		y = data+width;
		data += width+1; 	// advance to the next diagonal element
		
		TYP tmp;
		for ( int i=nr; i<width; ++i )
		{
			// swap( *x,*y )
			tmp = *y;
			*y  = *x;
			*x  = tmp;
			
			++x;
			y += width;
		}
	}
}



/* ************************************************** */
/* Transpose any image into an output image */
/* ************************************************** */
template<typename TYP> 
void Transpose::doTranspose( const Image<TYP> &image, Image<TYP> &transpose )
{
	int width  = image.getWidth();
	int height = image.getHeight();
	
	//
	// Adjust size
	//
	if ( (height!=transpose.getWidth()) || (width!=transpose.getHeight()) )
	{	
		transpose.resize( height, width );
	}
	
	
	//
	// Transpose
	//
	TYP *src  = image.getData();
	TYP *dest = transpose.getData();
	
	for ( int y=0; y<height; ++y )
	for ( int x=0; x<width;  ++x )
	{
		dest[x*height+y] = *src;
		++src;
	}
}

} /* namespace GET */

