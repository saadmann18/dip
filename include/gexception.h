#ifndef __GET__GEXCEPTION_H
#define __GET__GEXCEPTION_H

#include "standardoutput.h"


namespace GET 
{


/**
 * Basisklasse f�r alle Exceptions innerhalb der GETLib
 * 
 * Diese Exception gibt Ort und Beschreibung des Fehlers
 * an der Standardfehlerausgabe aus. Au�erdem ist ein gesch�tzter
 * parameterloser Konstruktor vorhanden, der von abgeleiteten Exceptions
 * verwendet werden kann, um ein anderes Verhalten (z.B. ohne Fehlerausgabe)
 * zu erzeugen.
 * 
 * 
 * #Anwendungsbeispiel:# Vermeiden von Division durch Null
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
 *                "Image& Image::div(float value)",                   // Ort
 *                "Division durch 0 kann nicht durchgef�hrt werden."  // Beschreibung
 *                );
 *    }
 *    else
 *    {
 *        // Division durchf�hren
 *    }
 *    return *this;
 * };
 * @endcode
 * 
 * @author Holger T�ubig
 * @version FERTIG.
 * @see Zum Erzeugen und Verarbeiten von Exceptions werden die Befehle #$throw$#, #$try$# und #$catch$#
 * verwendet. Informationen zur Benutzung dieser Befehle sind in den meisten C++ B�chern vorhanden.
 * 
 */
class GException
{
protected:
	/**
	 * Parameterloser Konstruktor f�r abgeleitete Klassen.
	 */
	GException( );
	
public:
	/**
	 * Erzeugt Exception und gibt Ort und Beschreibung des Fehlers aus.
	 * 
	 * @param location Ort des Fehlers
	 * @param error Fehlerbeschreibung
	 */
	GException( const char *location, const char *error);
	
	/**
	 * Destruktor.
	 */
	virtual ~GException();
};

	
}	// namespace

#endif // __GET__GEXCEPTION_H
