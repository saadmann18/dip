#ifndef __GET__GEXCEPTION_H
#define __GET__GEXCEPTION_H

#include "standardoutput.h"


namespace GET 
{


/**
 * Basisklasse für alle Exceptions innerhalb der GETLib
 * 
 * Diese Exception gibt Ort und Beschreibung des Fehlers
 * an der Standardfehlerausgabe aus. Außerdem ist ein geschützter
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
 *                "Division durch 0 kann nicht durchgeführt werden."  // Beschreibung
 *                );
 *    }
 *    else
 *    {
 *        // Division durchführen
 *    }
 *    return *this;
 * };
 * @endcode
 * 
 * @author Holger Täubig
 * @version FERTIG.
 * @see Zum Erzeugen und Verarbeiten von Exceptions werden die Befehle #$throw$#, #$try$# und #$catch$#
 * verwendet. Informationen zur Benutzung dieser Befehle sind in den meisten C++ Büchern vorhanden.
 * 
 */
class GException
{
protected:
	/**
	 * Parameterloser Konstruktor für abgeleitete Klassen.
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
