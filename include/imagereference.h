#ifndef __GET_IMAGE_REFERENCE_H
#define __GET_IMAGE_REFERENCE_H

#include "image.h"

namespace GET
{



/**
 * Bildobjekt, das sich wie Image<TYP> verhält und aber keinen eigenen Speicher allokiert.
 * 
 * Der Speicher für die Bilddaten wird nicht von diesem Objekt allokiert.
 * Statt dessen muss der Speicher für m_data außerhalb dieses Objektes
 * allokiert und als Parameter data an den Konstruktor dieses Objektes übergeben werden.
 * 
 * @author Holger Täubig
 * @author  Roi Chobodi
 * @version VORLÄUFIG FERTIG.
 * 
 * @param TYP Basisdatentyp der in der Sequenz enthaltenen  Bilder
 */
template <typename Typ> class ImageReference : public Image<Typ>
{
  public:
	/** Spezieller Konstruktor (Nutze diesen Konstruktor nur, wenn du weisst, was du tust!!!).
	 * 
	 * Dieser Konstruktor erzeugt ein Bildobjekt, dass einen bereits vorhandenen Speicherbereich
	 * für die Bilddaten verwendet. \n
	 * D.h. der Speicher für die Bilddaten wird nicht von diesem Objekt allokiert.
	 * Statt dessen wurde der Speicher für m_data außerhalb dieses Objektes
	 * allokiert und wird als Parameter data an dieses Objekt übergeben. \n
	 * Wird ein Objekt mit diesem Konstruktor erzeugt, so 
	 * wird der Speicherbereich von m_data bei Aufruf des Destruktor dieses 
	 * Objektes NICHT freigegeben. Dies muss dann genau wie das Allokieren des
	 * Speicherbereiches außerhalb dieses Objektes geschehen.
	 * 
	 * Der übergebene Speicherbereich wird als Bild mit Basisdatentyp Typ und Grösse
	 * width x height interpretiert.
	 * 
	 * @param width  Breite des zu erzeugenden Bildes
	 * @param height Höhe des zu erzeugenden Bildes
	 * @param data Zeiger auf die Bilddaten
	 */
	inline ImageReference( int width, int height, Typ* data ); 
	
	/** 
	 * Setzt den Bilddatenzeiger.
	 * 
	 * @param data neuer Zeiger auf die Bilddaten
	 */
	 inline void setData( Typ* data ) { m_data = data; };
	
	/** 
	 * Setzt den Bilddatenzeiger und ändert zusätzlich Höhe und Breite des Bildes.
	 * 
	 * @param data neuer Zeiger auf die Bilddaten
	 */
	 inline void setData( Typ* data, int width, int height );
};



template <typename Typ> 
inline ImageReference<Typ>::ImageReference( int width, int height, Typ* data ) :
	Image<Typ>( width, height, false )
{
	setData( data );
};

template <typename Typ> 
inline void ImageReference<Typ>::setData( Typ* data, int width, int height ) 
{ 
	m_width  = width;
	m_height = height;
	m_size   = m_width * m_height;
	
	m_data = data; 
};




}

#endif /*__GET_IMAGE_REFERENCE_H*/
