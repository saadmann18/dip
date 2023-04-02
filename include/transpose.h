#ifndef __GET__TRANSPOSE_H
#define __GET__TRANSPOSE_H

#include "image.h"
#include "standardoutput.h"
#include "gexception.h"


namespace GET 
{


/**
 * Transponiert ein Bild (Spiegelung an der Hauptachse)
 * 
 * @author Holger Täubig
 * @version FERTIG.
 */
class Transpose
{
  public:
  	/**
  	 * Transponiert das übergebene Bild.
  	 * Eingabebild und transponiertes Ausgabebild befinden sich in zwei 
  	 * unterschiedlichen Objekten.
  	 * 
  	 * @param image Originalbild (Input)
  	 * @param transpose transponiertes Bild (Output)
  	 */
  	template<typename TYP> void doTranspose( const Image<TYP> &image, Image<TYP> &transpose );

  	/**
  	 * Transponiert das übergebene quadratische Bild. 
  	 * Die Operation wird innerhalb des übergebenen Bildes ausgeführt. D.h.
  	 * das Ergebnis wird in das Originalbild zurückgeschrieben. 
  	 * 
  	 * Diese Methode kann nur für quadratische Bilder verwendet werden. 
  	 * Für nicht quadratische Bilder wird eine Exception erzeugt.
  	 * 
  	 * @param image Originalbild bei Funktionsaufruf. Bei Verlassen der Funktion steht hier das transponierte Bild. 
  	 */
  	template<typename TYP> void doTranspose( Image<TYP> &image );  	
};



/* ************************************************ */
/* Transponieren quadratischer Bilder in einem Bild */
/* ************************************************ */
template<typename TYP> 
void Transpose::doTranspose( Image<TYP> &image )
{
	int 	 width = image.getWidth();
	TYP 	*data  = image.getData();
	
	//
	// TEST: Transponieren in einem Bild nur fuer quadratische Bilder
	//
	if ( width!=image.getHeight() )
	{
		// keine FEHLERKORREKTUR möglich
		throw GException(
			"Transpose::doTranspose( Image<TYP> &image )",
			"Bild ist nicht quadratisch"
			);
	};
	
	//
	// Transponieren
	//
	TYP *x; 	// genutzt als Zeiger auf Pixel (x,nr)
	TYP *y; 	// genutzt als Zeiger auf Pixel (nr,y)
	for ( int nr=1; nr<width; ++nr )
	{
		x = data+1;
		y = data+width;
		data += width+1; 	// zum naechsten Diagonalelement vorruecken
		
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
/* transponieren beliebiger Bilder in ein Ausgabebild */
/* ************************************************** */
template<typename TYP> 
void Transpose::doTranspose( const Image<TYP> &image, Image<TYP> &transpose )
{
	int width  = image.getWidth();
	int height = image.getHeight();
	
	//
	// Groesse anpassen
	//
	if ( (height!=transpose.getWidth()) || (width!=transpose.getHeight()) )
	{	
		transpose.resize( height, width );
	}
	
	
	//
	// Transponieren
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

#endif /* __IMAGE_H */
