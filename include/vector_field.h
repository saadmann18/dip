#ifndef __GET__VECTOR_FIELD_H
#define __GET__VECTOR_FIELD_H

#include "image.h"
#include "gvector.h"

#include <Qt3Support>
#include <Q3Canvas>


 
namespace GET
{



/**
 * Vector field.
 * 
 * Das Vektorfeld muss zun�chst als Objekt vom Typ VectorField 
 * erzeugt werden und danach k�nnen beliebig viele 
 * Ansichten (Objekte von ViewVectorField) daf�r erzeugt werden.
 * 
 * @see Dokumentation zu QT 3.0 unter Q3Canvas und Q3CanvasView
 * 
 * @author Holger T�ubig
 * @version FERTIG.
 * @note keine Quellen, aber Ideen/Hilfen aus der QT-Dokumentation verwendet
 */
class VectorField: public Q3Canvas 
{
    Q_OBJECT

  public:
	/**
	 * Konstruktor.
	 * 
	 * @param width Breite der Ausgabefl�che
	 * @param height H�he der Ausgabefl�che
	 * @param subpixel Anzahl der Subpixel die pro Einheitsl�nge f�r die 
	 * Darstellung der Pfeile genutzt werden sollen. #Achtung: Das Ausgabebild
	 * wird um den Faktor subpixel gr��er als width x height.#
	 */
	VectorField( int width, int height, int subpixel = 10 );
	
	
	/**
	 * Daten setzen.
	 * 
	 * Es werden nur an den Bildpunkten Pfeile eingezeichnet, an denen die 
	 * Vektorl�nge gr��er 0 ist.
	 * 
	 * Wird als Gr��e der Pfeilspitze 0 �bergeben, so wird diese f�r jeden einzelnen
	 * Pfeil relativ zur L�nge des Pfeils (25%) angepasst.
	 * 
	 * @param data Bild mit den Vektoren (jeder Pixel ist vom Typ Point)
	 * @param arrow_size Gr��e der Pfeilspitze in Subpixeln (0=an Pfeilgr��e angepasst)
	 */
	void setData( const Image<Vector2D> &data, int arrow_size = 0 );

	/**
	 * Daten mit Stift pen, F�llung brush und Tiefe z setzen.
	 * 
	 * Es werden nur an den Bildpunkten Pfeile eingezeichnet, an denen die 
	 * Vektorl�nge gr��er 0 ist.
	 * 
	 * Wird als Gr��e der Pfeilspitze 0 �bergeben, so wird diese f�r jeden einzelnen
	 * Pfeil relativ zur L�nge des Pfeils (25%) angepasst.
	 * 
	 * @param data   Bild mit den Vektoren (jeder Pixel ist vom Typ Point)
	 * @param pen    Stift (siehe QPen), mit dem die Daten gezeichnet werden
	 * @param brush  F�llung (siehe QBrush), mit der die Daten gezeichnet werden
	 * @param arrow_size Gr��e der Pfeilspitze in Subpixeln (0=an Pfeilgr��e angepasst)
	 * @param z      Tiefe (Dimension z) in der die Daten gezeichnet werden
	 */
	void setData( const Image<Vector2D> &data, QPen pen, QBrush brush = QBrush(Qt::SolidPattern), int arrow_size = 0, double z = 0.0 );



  private:
  
	/**	
	 * Anzahl der Subpixel die pro Einheitsl�nge f�r die Darstellung der Pfeile genutzt werden sollen. 
	 * 
	 * @see VectorField()
	 */
	int m_subpixel;
};



/**
 * Hilfsklasse: Q3CanvasItem zum zeichnen eines Pfeils.
 * 
 * Die Darstellung dieses Q3CanvasItem besteht aus einer Linie
 * (abgeleitet von Q3CanvasLine) und einem gef�llten Dreieck
 * als Pfeilspitze (Element: Q3CanvasPolygon arrow).
 * 
 * Die Gr��e der Pfeilspitze ist relativ zur L�nge des Pfeils (25%).
 * 	
 * @see Verwendet von VectorField bzw. ViewVectorField 
 * @see Dokumentation zu QT 3.0 unter Q3Canvas und Q3CanvasView
 * 
 * @author Holger T�ubig
 * @version FERTIG.
 * @note keine Quellen, aber Ideen/Hilfen aus der QT-Dokumentation verwendet
 */
class CanvasItemArrow : public Q3CanvasLine
{
  protected:
	/** Q3CanvasItem zum Zeichnen der Pfeilspitze */
	Q3CanvasPolygon* arrow;
	
  public:
	/**
	 * Konstruktor.
	 * 
	 * Erzeugt einen  neuen Pfeil, dessen Anfangs- und Endpunkt aber noch
	 * mitttels setPoints() gesetzt werden muss.
	 * 
	 * @param canvas Q3Canvas-Objekt, in das dieses Q3CanvasItem eingebunden werden soll
	 */
	inline CanvasItemArrow( Q3Canvas *canvas ) :
		Q3CanvasLine( canvas )
	{
		arrow = new Q3CanvasPolygon( canvas );
		arrow->setBrush( Qt::SolidPattern );
	};

	/**
	 * Setzt Anfangs- und Endpunkt des Pfeils.
	 * Alle Koordinaten werden im Koordinatensystem des Q3Canvas-Objektes (VectorField)
	 * angegeben, zu dem dieses Element geh�rt.
	 *
	 * @param x1 x-Koordinate des Anfangspunktes
	 * @param y1 y-Koordinate des Anfangspunktes
	 * @param x2 x-Koordinate des Endpunktes
	 * @param y2 y-Koordinate des Endpunktes
	 */
	virtual void setPoints ( int x1, int y1, int x2, int y2 );	

	/**
	 * �berschriebene viruelle Methode, damit die �nderung f�r Linie und Pfeilspitze durchgef�hrt wird.
	 */
	virtual void setBrush ( QBrush b );
	/**
	 * �berschriebene viruelle Methode, damit die �nderung f�r Linie und Pfeilspitze durchgef�hrt wird.
	 */
	virtual void setPen ( QPen p );
	/**
	 * �berschriebene viruelle Methode, damit die �nderung f�r Linie und Pfeilspitze durchgef�hrt wird.
	 */
	void setZ( double z );
}; 



/**
 * CanvasItemArrow mit einer Pfeilspitze fester Gr��e.
 * 
 * Die Gr��e der Pfeilspitze wird dem Konstruktor �bergeben. Die Spitze
 * hat dann unabh�ngig von der L�nge des Pfeils diese Gr��e (in Pixeln).
 * 
 * @see CanvasItemArrow
 * @see Dokumentation zu QT 3.0 unter Q3Canvas und Q3CanvasView
 * 
 * @author Holger T�ubig
 * @version FERTIG.
 * @note keine Quellen, aber Ideen/Hilfen aus der QT-Dokumentation verwendet
 */
class CanvasItemFixedArrow : public CanvasItemArrow
{
  private:
	/**
	 * Gr��e der Pfeilspitze in Pixeln.
	 */
	float m_arrow_size;
	
  public:
	/**
	 * Konstruktor.
	 * 
	 * Erzeugt einen  neuen Pfeil, dessen Anfangs- und Endpunkt aber noch
	 * mitttels setPoints() gesetzt werden muss.
	 * 
	 * Die Gr��e der Pfeilspitze wird dem Konstruktor �bergeben. Die Spitze
	 * hat dann unabh�ngig von der L�nge des Pfeils diese Gr��e (in Pixeln).
	 * 
	 * @param canvas Q3Canvas-Objekt, in das dieses Q3CanvasItem eingebunden werden soll
	 * @param arrow_size Gr��e der Pfeilspitze in Pixeln
	 */
	inline CanvasItemFixedArrow( Q3Canvas *canvas, int arrow_size ) :
		CanvasItemArrow( canvas ),
		m_arrow_size( arrow_size )
	{
	};


	/**
	 * Setzt Anfangs- und Endpunkt des Pfeils.
	 * Alle Koordinaten werden im Koordinatensystem des Q3Canvas-Objektes (VectorField)
	 * angegeben, zu dem dieses Element geh�rt.
	 *
	 * @param x1 x-Koordinate des Anfangspunktes
	 * @param y1 y-Koordinate des Anfangspunktes
	 * @param x2 x-Koordinate des Endpunktes
	 * @param y2 y-Koordinate des Endpunktes
	 */
	virtual void setPoints ( int x1, int y1, int x2, int y2 );	
};
	
	
	
}



#endif /*__GET__VECTOR_FIELD_H*/
