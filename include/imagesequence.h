#ifndef __GET__IMAGE_SEQUENCE_H
#define __GET__IMAGE_SEQUENCE_H

#include "image.h"
#include <stdlib.h>

namespace GET 
{



/** Bildsequenz.
 * 
 * Dieses Template stellt die Basisimplementation für alle Bildarrays dar. 
 * Der Bildtyp der Sequenz wird durch Übergabe des Basisdatentyps der Bilder
 * bei der Instanzierung des Templates erzeugt. 
 * 
 * @author Holger Täubig
 * @version FUNKTIONSFÄHIG.
 * @see Image
 * 
 * @param TYP Basisdatentyp der in der Sequenz enthaltenen  Bilder
*/
template <typename TYP> 
class ImageSequence 
{
  protected:
	/** Länge der Bildsequenz (Anzahl der Bilder) */
  	int 		  m_size;
  	
  	/** maximale Größe auf die die Sequenz vergrößert werden kann, ohne dass 
  	 * neuer Speicher für das Array allokiert werden muss, in dem die Bilder 
  	 * verwaltet werden.
  	 * 
  	 * @see m_images
  	 */
	int 		  m_capacity;
	
	/** Array mit den Bildern der Sequenz*/
	Image<TYP> 	**m_images;
	
	/** Breite der Bilder der Sequenz.
	 * 
	 * Alle Bilder der Sequenz haben die gleiche Breite.
	 */
	int 		  m_images_width;
	
	/** Höhe der Bilder der Sequenz.
	 * 
	 * Alle Bilder der Sequenz haben die gleiche Höhe.
	 */
	int 		  m_images_height;


	/**
	 * Löscht alle Bilder der Sequenz. Dadurch wird der verwendete Speicherplatz 
	 * wieder freigegeben.
	 */
	virtual void clear();

	/** Konstruktor für abgeleitete Klassen.
	 * 
	 * Dieser Konstruktor darf nur von abgeleiteten Klassen verwendet werden.
	 */	
	ImageSequence( ) :
		m_size( 0 ),
		m_capacity( 0 ),
		m_images( NULL ),
		m_images_width( 0 ),
		m_images_height( 0 )
	{ };
	
	
  public:
	/** Konstruktor.
	 * 
	 * Erzeugt eine Bildsequenz aus size Bildern der Grösse width*height.
	 * 
	 * @param size Größe der zu erzeugenden Bildsequenz
	 * @param width Breite der Bilder der zu erzeugenden Sequenz.
	 * @param height Höhe der Bilder der zu erzeugenden Sequenz.
	 */
	ImageSequence( int size, int width, int height );
	
	/** Destruktor */
	virtual ~ImageSequence( );

	/** kopiert eine Bildsequenz inklusive Konvertierung des Bildtypes.
	 * 
	 * Kopiert die übergebene Bildsequenz. Die Bilddaten werden dabei aus 
	 * dem Farbraum der übergebenen Bildsequenz in den Typ dieser Bildsequenz 
	 * konvertiert.
	 * 
	 * @param imageseq zu kopierendes Bild
	 * @return dieses Objekt
	 * 
	 * @see Liste der möglichen Basisdatentypen in basetypes.h
	 */
	template <typename OriginalTyp> ImageSequence<TYP> & copy( const ImageSequence<OriginalTyp> &imageseq );
	
	
	
	/** liefert die Größe der Bildsequenz (Anzahl der Bilder)
	 * @return Anzahl der Bilder
	 * @see m_size
	 */
	inline 	int  getSize( ) const { return m_size; };
	
	/** The size of the allocated buffer of the Images array.
	 * @return the siye of the buffer, m_capacity
	 * @see m_capacity
	 */
	inline 	int  getCapacity( ) const { return m_capacity; };

	/** liefert die Breite der in der Sequenz enthaltenen Bilder 
	 * @return Breite der Bilder der Sequenz
	 * @see m_images_width
	 */
	inline 	int  getImageWidth( ) const { return m_images_width; };

	/** liefert die Höhe der in der Sequenz enthaltenen Bilder 
	 * @return Höhe der Bilder der Sequenz
	 * @see m_images_height
	 */
	inline 	int  getImageHeight( ) const { return m_images_height; };



	/** doReSize Change one or more of the three dimensions describing the 
	 * Images Sequence. Note that upon changes in parameters width or height
	 * the Images in the sequnce will be assigned new entry points in the 
	 * joint buffer and its the user's responsibility to prepare it accordingly
	 * before hand.
	 *  
	 * @param size Gr??e der zu erzeugenden Bildsequenz
	 * @param width Breite der Bilder der zu erzeugenden Sequenz.
	 * @param height H?he der Bilder der zu erzeugenden Sequenz.
	 * 
	 * @return Nothing, type void. Function allways succeed.
	 * 
	 * @see m_ImagesJointBuffer doAssignExternalBuffer
	 */
	virtual void doReSize(int size, int width, int height);

	
	
	/**
	 * Zugriff auf ein spezielles Bild des Sequenz.
	 * 
	 * @param index Nummer des Bildes, auf das zugegriffen werden soll
	 * @return Bild
	 */
	inline  Image<TYP>& operator[] (int index);
	
	/**
	 * konstanter Zugriff auf ein spezielles Bild des Sequenz (Bild kann nicht geändert werden).
	 * 
	 * @param index Nummer des Bildes, auf das zugegriffen werden soll
	 * @return Bild
	 */
	inline  const Image<TYP>& operator[] (int index) const;
	
	
	
	/** punktweise Addition einer Bildsequenz.
	 * 
	 * @param imageseq zu addierende Bildsequenz 
	 * @return diese Bildsequenz nach Addition von imageseq
	 */
	ImageSequence<TYP>& add( const ImageSequence<TYP> &imageseq );

	/** punktweise Subtraktion einer Bildsequenz.
	 * 
	 * @param imageseq zu subtrahierende Bildsequenz 
	 * @return diese Bildsequenz nach Subtraktion von imageseq
	 */
	ImageSequence<TYP>& sub( const ImageSequence<TYP> &imageseq );

	/** punktweise Multiplikation einer Bildsequenz.
	 * 
	 * @param imageseq zu multiplizierende Bildsequenz 
	 * @return diese Bildsequenz nach Multiplikation mit imageseq
	 */
	ImageSequence<TYP>& mul( const ImageSequence<TYP> &imageseq );

	/** punktweise Division durch eine Bildsequenz.
	 * 
	 * @param imageseq Bildsequenz durch die dividiert werden soll
	 * @return diese Bildsequenz nach Division durch imageseq
	 */
	ImageSequence<TYP>& div( const ImageSequence<TYP> &imageseq );



	/** punktweise Addition mit Skalar.
	 * 
	 * @param value zu addierender Wert
	 * @return diese Bildsequenz nach Addition von imageseq
	 */
	ImageSequence<TYP>& add( TYP value );

	/** punktweise Subtraktion mit Skalar.
	 * 
	 * @param value zu subtrahierender Wert
	 * @return diese Bildsequenz nach Subtraktion von imageseq
	 */
	ImageSequence<TYP>& sub( TYP value );

	/** punktweise Multiplikation mit Skalar.
	 * 
	 * @param value zu multiplizierender Wert
	 * @return diese Bildsequenz nach Multiplikation mit imageseq
	 */
	ImageSequence<TYP>& mul( TYP value );

	/** punktweise Division durch Skalar.
	 * 
	 * @param value Wert durch den dividiert werden soll
	 * @return diese Bildsequenz nach Division durch imageseq
	 */
	ImageSequence<TYP>& div( TYP value );



	/** punktweise Addition zweier Bildsequenzen wobei das Ergebnis in eine dritte Bildsequenz (dieses Objekt) geschrieben werden soll.
	 * 
	 * @param img1 Bildsequenz
	 * @param img2 zu addieerende Bildsequenz
	 * @return diese Bildsequenz (in die das Ergebnis geschrieben wird)
	 * 
	 * @todo Methode testen
	 */
	ImageSequence<TYP>& add( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 );

	/** punktweise Subtraktion zweier Bildsequenzen wobei das Ergebnis in eine dritte Bildsequenz (dieses Objekt) geschrieben werden soll.
	 * 
	 * @param img1 Bildsequenz
	 * @param img2 zu subtrahierende Bildsequenz
	 * @return diese Bildsequenz (in die das Ergebnis geschrieben wird)
	 * 
	 * @todo Methode testen
	 */
	ImageSequence<TYP>& sub( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 );

	/** punktweise Multiplikation zweier Bildsequenzen wobei das Ergebnis in eine dritte Bildsequenz (dieses Objekt) geschrieben werden soll.
	 * 
	 * @param img1 Bildsequenz
	 * @param img2 zu multiplizierende Bildsequenz
	 * @return diese Bildsequenz (in die das Ergebnis geschrieben wird)
	 * 
	 * @todo Methode testen
	 */
	ImageSequence<TYP>& mul( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 );

	/** punktweise Division einer Bildsequenz durch eine andere Bildsequenz wobei das Ergebnis in eine dritte Bildsequenz (dieses Objekt) geschrieben werden soll.
	 * 
	 * @param img1 Bildsequenz
	 * @param img2 Bildsequenz durch die dividiert werden soll
	 * @return diese Bildsequenz (in die das Ergebnis geschrieben wird)
	 * 
	 * @todo Methode testen
	 */
	ImageSequence<TYP>& div( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 );
	
	
	
	/**
	 * Summe der Bilder dieser Sequenz.
	 * 
	 * Es entsteht ein Bild durch pixelweises Aufsummieren der Bilder dieser Sequenz.
	 * 
	 * @param sum Summenbild
	 */
	void sumSequence( Image<TYP>& sum );
};



/* ******************************************************************************* */
/* *** Implementation der Templates ********************************************** */
/* ******************************************************************************* */


 
/* ******************************************************************************* */
/* Konstruktor. Erzeugt eine Bildsequenz aus size Bildern der Grösse width*height. */
/* ******************************************************************************* */
template <typename TYP> 
ImageSequence<TYP>::ImageSequence( int size, int width, int height ) :
	m_size( size ),
	m_capacity( 2*size ),
	m_images( NULL ),
	m_images_width( width ),
	m_images_height( height )
{
	m_images = new Image<TYP>* [m_capacity];
	for ( int i=0; i<m_size; ++i)
	{	
		m_images[i] = new Image<TYP>(width, height);
	}
	for ( int i=m_size; i<m_capacity; ++i )
	{
		m_images[i] = NULL;
	}
}

/* ********** */
/* Destruktor */
/* ********** */
template <typename TYP> 
ImageSequence<TYP>::~ImageSequence( )
{
	clear( );
	if (m_images) delete[] m_images;
}

template<typename TYP> 
template<typename OriginalTyp> 
ImageSequence<TYP> & ImageSequence<TYP>::copy( const ImageSequence<OriginalTyp> &imageseq )
{
	int size = imageseq.getSize();
	
	if ( (m_size!=size) || 
	     (m_images_width!=imageseq.getImageWidth()) || 
	     (m_images_height!=imageseq.getImageHeight()) )
	{
		doReSize( size, imageseq.getImageWidth(), imageseq.getImageHeight() );
	}
	
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].copy(imageseq[i] );
	};
	
	return *this;
}



/* ******************************************** */
/* Größe der Sequenz oder Bildgrößen ändern     */
/* ******************************************** */
template <typename TYP> 
void ImageSequence<TYP>::doReSize(int size, int width, int height)
{
	//
	// resize vorhandener Bilder falls sich Breite oder Höhe
	// geändert haben
	//
	if ( (m_images_width!=width) || (m_images_height!=height) )
	{
		// neue Bildgroesse speichern
		m_images_width  = width;
		m_images_height = height;
		
		// alle vorhandenen Bilder (aber maximal soviele wie uebrig bleiben)
		// an die neue Bildgroesse anpassen
		int min = std::min(size,m_size);
		for ( int i=0; i<min; ++i )
		{
			m_images[i]->resize( width, height );
		};
	};
	
	//
	// Anzahl der Bilder anpassen
	//
	if ( size<m_size )
	{
		// zu viel vorhandene Bilder loeschen
		for ( int i=size; i<m_size; ++i )
		{
			delete m_images[i];
			m_images[i] = NULL;
		};
	}
	else if ( size>m_size )
	{
		// falls noetig die Kapazität des Arrays mit den Bildzeigern erweitern
		if ( size>m_capacity )
		{
			m_capacity = std::max( 2*m_capacity, 2*size );
			m_images = (GET::Image<TYP>**) realloc(m_images, m_capacity * sizeof(Image<TYP>*));
			
			for ( int i=size; i<m_capacity; ++i )
			{
				m_images[i] = NULL;
			};
		};
		
		// notwendige Bilder hinzufuegen
		for ( int i=m_size; i<size; ++i )
		{
			m_images[i] = new Image<TYP>(width, height);
		};
	};
	
	m_size = size;
}



/* ******************************************** */
/* Zugriff auf ein spezielles Bild des Sequenz. */
/* ******************************************** */
template <typename TYP> 
inline Image<TYP>& ImageSequence<TYP>::operator[] (int index)
{
	//
	// TEST: index < m_size
	//
	if ( index>=m_size )
	{
		//throw GException(
		//	"ImageSequence<TYP>::operator[] (int index)",
		//	"Index außerhalb des zulässigen Bereiches"
		//	);
		
		// keine FEHLERKORREKTUR
	}
	
	return *(m_images[index]);
}

/* ******************************************** */
/* Zugriff auf ein spezielles Bild des Sequenz. */
/* ******************************************** */
template <typename TYP> 
inline const Image<TYP>& ImageSequence<TYP>::operator[] (int index) const
{
	//
	// TEST: index < m_size
	//
	if ( index>=m_size )
	{
		//throw GException(
		//	"ImageSequence<TYP>::operator[] (int index)",
		//	"Index außerhalb des zulässigen Bereiches"
		//	);
		
		// keine FEHLERKORREKTUR
	}
	
	return *(m_images[index]);
}



template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imageseq )
{
	int size = m_size;
	
	if ( (size!=imageseq.getSize()) || 
	     (m_images_width!=imageseq.getImageWidth()) || 
	     (m_images_height!=imageseq.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imageseq )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].add( imageseq[i] );
	};

	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::sub( const ImageSequence<TYP> &imageseq )
{
	int size = m_size;
	
	if ( (size!=imageseq.getSize()) || 
	     (m_images_width!=imageseq.getImageWidth()) || 
	     (m_images_height!=imageseq.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::sub( const ImageSequence<TYP> &imageseq )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].sub( imageseq[i] );
	};

	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::mul( const ImageSequence<TYP> &imageseq )
{
	int size = m_size;
	
	if ( (size!=imageseq.getSize()) || 
	     (m_images_width!=imageseq.getImageWidth()) || 
	     (m_images_height!=imageseq.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::mul( const ImageSequence<TYP> &imageseq )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].mul( imageseq[i] );
	};

	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::div( const ImageSequence<TYP> &imageseq )
{
	int size = m_size;
	
	if ( (size!=imageseq.getSize()) || 
	     (m_images_width!=imageseq.getImageWidth()) || 
	     (m_images_height!=imageseq.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::div( const ImageSequence<TYP> &imageseq )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].div( imageseq[i] );
	};

	return *this;
}



template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::add( TYP value )
{
	int size = m_size;
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].add( value );
	};

	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::sub( TYP value )
{
	int size = m_size;
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].sub( value );
	};

	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::mul( TYP value )
{
	int size = m_size;
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].mul( value );
	};

	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::div( TYP value )
{
	int size = m_size;
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].div( value );
	};

	return *this;
}



template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )
{
	//
  	// TEST: Bilder und Sequenzlaenge beider Sequenzen muessen gleich gross sein
	//
	int size   = imgseq1.getSize();
	int width  = imgseq1.getImageWidth();
	int height = imgseq1.getImageHeight();
	
	if ( (size   != imgseq2.getSize()) || 
	     (width  != imgseq2.getImageWidth()) || 
	     (height != imgseq2.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	//
	// Groesse der Ergebnissequenz (dieses Objekt) anpassen
	//
	if ( (size!=m_size) || (width!=m_images_width) || (height!=m_images_height) )
	{
		doReSize( size, width, height );
	};
	
	//
	// Operation ausführen
	//
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].add( imgseq1[i], imgseq2[i] );
	};

	//
	// fertig
	//
	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::sub( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )
{
	//
  	// TEST: Bilder und Sequenzlaenge beider Sequenzen muessen gleich gross sein
	//
	int size   = imgseq1.getSize();
	int width  = imgseq1.getImageWidth();
	int height = imgseq1.getImageHeight();
	
	if ( (size   != imgseq2.getSize()) || 
	     (width  != imgseq2.getImageWidth()) || 
	     (height != imgseq2.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	//
	// Groesse der Ergebnissequenz (dieses Objekt) anpassen
	//
	if ( (size!=m_size) || (width!=m_images_width) || (height!=m_images_height) )
	{
		doReSize( size, width, height );
	};
	
	//
	// Operation ausführen
	//
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].sub( imgseq1[i], imgseq2[i] );
	};

	//
	// fertig
	//
	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::mul( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )
{
	//
  	// TEST: Bilder und Sequenzlaenge beider Sequenzen muessen gleich gross sein
	//
	int size   = imgseq1.getSize();
	int width  = imgseq1.getImageWidth();
	int height = imgseq1.getImageHeight();
	
	if ( (size   != imgseq2.getSize()) || 
	     (width  != imgseq2.getImageWidth()) || 
	     (height != imgseq2.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	//
	// Groesse der Ergebnissequenz (dieses Objekt) anpassen
	//
	if ( (size!=m_size) || (width!=m_images_width) || (height!=m_images_height) )
	{
		doReSize( size, width, height );
	};
	
	//
	// Operation ausführen
	//
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].mul( imgseq1[i], imgseq2[i] );
	};

	//
	// fertig
	//
	return *this;
}

template <typename TYP> 
ImageSequence<TYP>& ImageSequence<TYP>::div( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )
{
	//
  	// TEST: Bilder und Sequenzlaenge beider Sequenzen muessen gleich gross sein
	//
	int size   = imgseq1.getSize();
	int width  = imgseq1.getImageWidth();
	int height = imgseq1.getImageHeight();
	
	if ( (size   != imgseq2.getSize()) || 
	     (width  != imgseq2.getImageWidth()) || 
	     (height != imgseq2.getImageHeight()) )
	{
		gerr << "Laufzeitfehler in ImageSequence<TYP>& ImageSequence<TYP>::add( const ImageSequence<TYP> &imgseq1, const ImageSequence<TYP> &imgseq2 )" << std::endl;
		gerr << "Die Bilder oder die Sequenzlänge sind nicht gleich groß" << std::endl;
		
		// KEINE FEHLERKORREKTUR moeglich -> Objekt nicht veraendern
		return *this;
	}
	
	//
	// Groesse der Ergebnissequenz (dieses Objekt) anpassen
	//
	if ( (size!=m_size) || (width!=m_images_width) || (height!=m_images_height) )
	{
		doReSize( size, width, height );
	};
	
	//
	// Operation ausführen
	//
	for ( int i=0; i<size; ++i )
	{
		(*this)[i].div( imgseq1[i], imgseq2[i] );
	};

	//
	// fertig
	//
	return *this;
}



template <typename TYP> 
void ImageSequence<TYP>::sumSequence( Image<TYP>& sum )
{
	if ( (m_images_width!=sum.getWidth()) || (m_images_height!=sum.getHeight()) )
	{
		sum.resize( m_images_width, m_images_height );
	}
	
	int size = m_size;
	if ( size>0 )
	{
		sum.copy( (*this)[0] );
		for ( int i=1; i<size; ++i )
		{
			sum.add( (*this)[i] );
		};
	}
	else
	{
		sum.fill( 0.0 );
	};
}



/* ******************************* */
/* Löscht alle Bilder der Sequenz. */
/* ******************************* */
template <typename TYP> 
void ImageSequence<TYP>::clear()
{
	for ( int i=0; i<m_size; ++i )
		delete m_images[i];
	
	m_size = 0;
}



} /* namespace GET */

#endif /* __IMAGE_H */
