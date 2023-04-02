#pragma once
#include "standardoutput.h"


namespace GET 
{


/**
 * Base class for all exceptions within the GETLib
 * 
 * This exception prints the location and description of the 
 * error to the standard error output. There is also a protected 
 * parameterless constructor that can be used by derived exceptions 
 * to produce different behavior (e.g. without throwing an error)..
 * 
 * 
 * #application example:# Avoiding division by zero
 * 
 * @code
 * class Image
 * {
 *    ...
 *    Image& div(float value);
 * };
 * 
 * Image& Image::div(float value)
 * {
 *    if (value==0.0)
 *    {
 *       throw GException( 
 *                "Image& Image::div(float value)",     // Location
 *                "Division by 0 cannot be performed."  // Description
 *                );
 *    }
 *    else
 *    {
 *        // Division carry out
 *    }
 *    return *this;
 * };
 * @endcode
 * 
 * @author Holger Täubig
 * @version COMPLETE.
 * @see The commands #$throw$#, #$try$# and #$catch$# are used to generate and handle exceptions. 
 * Information on using these commands is available in most C++ books.
 * 
 */
class GException
{
protected:
	/**
	 * Parameterless constructor for derived classes.
	 */
	GException( );
	
public:
	/**
	 * Raise an exception and print out the location and description of the error.
	 * 
	 * @param location location of the error
	 * @param error Error Description
	 */
	GException( const char *location, const char *error);
	
	/**
	 * Destructor.
	 */
	virtual ~GException();
};

}	// namespace
