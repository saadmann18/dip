#ifndef __GET__SPATIALFILTERING_H
#define __GET__SPATIALFILTERING_H

#include "image.h"
#include "gexception.h"

#include <math.h>


namespace GET
{



/** Filterung im Ortsraum (Faltung).
 * 
 * Diese Klasse stellt Methoden zur Filterung im Ortsraum, also hauptsächlich
 * eine Faltung, zur Verfügung. (#Bemerkung:# Diese Klasse führt die Filterung in Form
 * einer Faltung durch. D.h. die Filtermaske wird vor der Anwendung noch gespiegelt.)
 * 
 * #Randbehanldlungsmethode:# Pixelwert aus Originalbild kopieren.
 * 
 * @author Holger Täubig
 * @version FUNKTIONSFÄHIG.
 * @note keine Quellen.
 * 
 * @bug 
 *       bei der Filterung wird #VOR DEM SUMMIEREN# jeder Pixel mit dem Gewicht multipliziert
 *       und wieder #DISKRETISIERT(NACH UCHAR UMGEWANDELT)#. Das führt zu dem Eindruck, dass 
 *       die Farbtiefe abnimmt (#siehe testSpatialFiltering für Image<uchar> und Image<Rgb>#). 
 *       Das heisst: #Filterung kann für Rgb und uchar so nicht verwendet werden#. Lösung: Es 
 *       muss in diesem Fall erst vollständig aufsummiert und abschliessend durch die Summe 
 *       der Maskenwerte dividiert werden. Frage: Evtl. kann der Fehler für float-Masken so
 *       gelassen werden. Image<uchar> werden üblicherweise vermutlich auch mit uchar-Masken 
 *       gefiltert und dort ist die andere Vorgehensweise ohnehin notwendig. (siehe auch Todo)
 * 
 * @todo Aufsatzpunkt ist bisher in der Mitte (Widerspruch zu Faltung)
 * @todo Erweiterung auf uchar-Filtermasken
 * @todo nach Einführung der Exceptions in GETGLOBAL: Exceptions erzeugen, wenn Eingabebild
 *       oder Filtermaske nicht gesetzt sind.
 */
template <typename PTYPE, typename MASKTYPE=float> class SpatialFiltering
{
  private:
	/** Filtermaske */
	Image<MASKTYPE> 	m_filter_mask; 
	
	/** true, wenn eine verwendbare Filtermaske vorhanden ist.*/
	bool 			m_filter_mask_available; 
	
	/** Zu filterndes Bild.
	 * 
	 * Dieser Zwischenspeicher des zu filternden Bildes wird genutzt, falls das Bild
	 * vor dem Aufruf von doConvolve() getrennt gestzt wird. Diese Vorgehensweise ist 
	 * nützlich, wenn ein Bild mehrfach mit unterschiedlichen Filtern gefiltert werden soll.
	 */
	Image<PTYPE> 	m_input_image;
	/** true, wenn ein verwendbares Eingabebild vorhanden ist. */
	bool 			m_input_image_available;
	
  public:
	/** Standardkonstruktor. */
	SpatialFiltering();
	
	/** Destruktor. */
	virtual ~SpatialFiltering();
	
	/** Setzt eine neue Filtermaske. 
	 * 
	 * @param filter_mask Image-Objekt in dem die neue Filtermaske übergeben wird 
	 */
	void setMask( const Image<MASKTYPE> &filter_mask );
	
	/** Liefert die derzeitige Filtermaske. 
	 * 
	 * @param filter_mask Image-Objekt in dem die akuell verwendete Filtermaske zurückgeliefert wird 
	 * 
	 * @todo konstante Referenz auf Maske zurückliefern spart Kopieraufwand
	 */
	void getMask( Image<MASKTYPE> &filter_mask );
	
	/** Setzt das zu filternde Eingabebild. 
	 * 
	 * @param image zu filterndes Bild
	 */
	void setImage( const Image<PTYPE> &image );
	
	
	
	/** Filterung(Faltung) ausführen.
	 * 
	 * Es wird das vorher gesetzte Eingabebild mit der vorher gesetzten Filtermaske 
	 * gefaltet.
	 * 
	 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll
	 * 
	 * @see setMask()
	 * @see setImage()
	 */
	inline void doConvolution( Image<PTYPE> &result );

	/** Filterung(Faltung) ausführen.
	 * 
	 * Es wird das vorher gesetzte Eingabebild mit der direkt übergebenen Filtermaske 
	 * gefaltet.
	 * 
	 * @param filter_mask Filtermaske, mit der gefaltet werden soll
	 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll
	 * 
	 * @see setImage()
	 */
	inline void doConvolutionWithMask( const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result );

	/** Filterung(Faltung) ausführen.
	 * 
	 * Es wird das direkt übergebene Eingabebild mit der vorher gesetzten Filtermaske 
	 * gefaltet.
	 * 
	 * @param input_image Eingabebild, das gefiltert werden soll
	 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll
	 * 
	 * @see setMask()
	 */
	inline void doConvolutionWithImage( const Image<PTYPE> &input_image, Image<PTYPE> &result );



	/** Erzeugt und setzt die Maske eines (quadratischen) Boxfilters/Mittelwertfilter.
	 * 
	 * @param size Maskengröße (Sollte ungerade sein!)
	 * 
	 * @see setMask()
	 */
	void setBoxFilterMask( int size );

	/** Erzeugt und setzt die Maske eines  Gauss-Filters.
	 * 
	 * Der Gauss-Filter hat in x- und y-Richtung die Standardabweichung sigma.
	 * Die Größe der Filtermaske quadratisch, ungerade und mindestens mit der
	 * Größe 6*sigma (Wertebereich [-3sigma,3sigma]) durch die Methode 
	 * selbst festgelegt.
	 * 
	 * @param sigma Standardabweichung des Gauss-Filters (in Pixeln)
	 * 
	 * @see setMask()
	 * 
	 * @todo Prüfen, ob 6 Sigma oder 3 Sigma benötigt werden.
	 * @todo Pr+fen ob die Normierung notwendig ist, oder bereits durch die Formel realisiert ist
	 */
	void setGaussFilterMask( float sigma );

  protected:
	/** Implementation der Faltung.
	 * 
	 * Alle vom Nutzer ausführbaren Aufrufe nutzen diese Methode, um das Ergebnis
	 * der Faltung von Filtermaske und Eingabebild zu berechnen.
	 * 
	 * @param input_image Eingabebild, das gerade gefiltert wird
	 * @param filter_mask Filtermaske, mit der gefaltet wird
	 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert wird
	 * 
	 * @see doConvolution(), doConvolutionWithMask() bzw. doConvolutionWithImage()
	 * @see doBoundaryCalculations()
	 */
	void doConvolution( const Image<PTYPE> &input_image, const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result );
	
	/** Randbehandlung durchführen 
	 * 
	 * Diese Methode wird von doConvolution(), doConvolutionWithMask() und
	 * doConvolutionWithImage() aufgerufen, um die Randbehandlung durch zu führen. \n
	 * In dieser Standardimplementierung werden die Pixelwerte aus dem Originalbild 
	 * in das Filterergebnis kopiert.
	 * 
	 * Diese Methode muss überladen werden, um einen Filteralgorithmus mit einer
	 * anderen Randbehandlungsmethode zu implementieren.
	 * 
	 * @param input_image Eingabebild, das gerade gefiltert wird
	 * @param filter_mask Filtermaske, mit der gefaltet wird
	 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert wird
	 */
	virtual void doBoundaryCalculations( const Image<PTYPE> &input_image, const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result );
};



/* *********************************************************************************** */
/* Faltung mit vorher gesetztem Eingabebild und vorher gesetzter Filtermaske ausführen. */
template <typename PTYPE, typename MASKTYPE> 
inline void SpatialFiltering<PTYPE,MASKTYPE>::doConvolution( Image<PTYPE> &result )
/* *********************************************************************************** */
{
	if ( m_filter_mask_available && m_input_image_available )
		doConvolution( m_input_image, m_filter_mask, result );
	else
	{
		gerr << "Fehler in SpatialFiltering<PTYPE>::doConvolution( Image<PTYPE> &result )" << endl;
		gerr << "Filtermaske oder Eingabebild existiert nicht." << endl;
	}
}

/* *********************************************************************************** */
/* Faltung mit Filtermaske ausführen. */
template <typename PTYPE, typename MASKTYPE> 
inline void SpatialFiltering<PTYPE,MASKTYPE>::doConvolutionWithMask( const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result )
/* *********************************************************************************** */
{
	if ( m_input_image_available )
		doConvolution( m_input_image, filter_mask, result );
	else
	{
		gerr << "Fehler in SpatialFiltering<PTYPE>::doConvolutionWithMask( const Image<PTYPE> &filter_mask, Image<PTYPE> &result )" << endl;
		gerr << "Eingabebild existiert nicht." << endl;
	}
}

/* *********************************************************************************** */
/* Faltung mit Eingabebild ausführen. */
template <typename PTYPE, typename MASKTYPE> 
inline void SpatialFiltering<PTYPE,MASKTYPE>::doConvolutionWithImage( const Image<PTYPE> &input_image, Image<PTYPE> &result )
/* *********************************************************************************** */
{
	if ( m_filter_mask_available )
		doConvolution( input_image, m_filter_mask, result );
	else
	{
		gerr << "Fehler in SpatialFiltering<PTYPE>::doConvolutionWithImage( const Image<PTYPE> &input_image, Image<PTYPE> &result )" << endl;
		gerr << "Filtermaske existiert nicht." << endl;
	}
}



/* *********************************************************************************** */
template <typename PTYPE, typename MASKTYPE> 
SpatialFiltering<PTYPE,MASKTYPE>::SpatialFiltering() :
/* *********************************************************************************** */
	m_filter_mask( ),
	m_filter_mask_available( false ),
	m_input_image( ),
	m_input_image_available( false )
{
}

/* *********************************************************************************** */
template <typename PTYPE, typename MASKTYPE> 
SpatialFiltering<PTYPE,MASKTYPE>::~SpatialFiltering()
/* *********************************************************************************** */
{
}



/* *********************************************************************************** */
/* Setzt eine neue Filtermaske. */
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::setMask( const Image<MASKTYPE> &filter_mask )
/* *********************************************************************************** */
{
	// Filtermaske kopieren
	m_filter_mask.copy( filter_mask );

	// Testen, ob die neue Maske genutzt werden kann
	if ( (m_filter_mask.getWidth()>0) && (m_filter_mask.getHeight()>0) )
		m_filter_mask_available = true;
	else
		m_filter_mask_available = false;
}
	
/* *********************************************************************************** */
/* Liefert die derzeitige Filtermaske. */
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::getMask( Image<MASKTYPE> &filter_mask )
/* *********************************************************************************** */
{
	filter_mask.copy( m_filter_mask );
}

/* *********************************************************************************** */
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::setImage( const Image<PTYPE> &image )
/* *********************************************************************************** */
{
	// Filtermaske kopieren
	m_input_image.copy( image );

	// Eingabebilder sind immer nutzbar (auch leere)
	m_input_image_available = true;
}


/* *********************************************************************************** */
/* Hilfsfunktionen für SpatialFiltering<PTYPE>::doConvolution( ). */
/* *********************************************************************************** */
template <typename PTYPE, typename MASKTYPE> 
inline PTYPE helpfunc_multiply( PTYPE & val1,MASKTYPE val2  )
{
	return val1 * val2;
}
template <> 
inline uchar helpfunc_multiply( uchar & val1,float val2  )
{
	return (uchar) (val1 * val2);
}
template <> 
inline Rgb helpfunc_multiply( Rgb & val1,float val2  )
{
	Rgb res;
	res.r = (uchar) (val1.r * val2);
	res.g = (uchar) (val1.g * val2);
	res.b = (uchar) (val1.b * val2); 
	return res;
}

/* *********************************************************************************** */
/* Implementation der Faltung. */
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::doConvolution( const Image<PTYPE> &input_image, const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result )
/* *********************************************************************************** */
{
	//
	// Groessen holen
	//
	int    mask_width  = filter_mask.getWidth();
	int    mask_height = filter_mask.getHeight();
	
	int    img_width  = input_image.getWidth();
	int    img_height = input_image.getHeight();
	
	//
	// Groessen testen 
	//
	if ( (img_width<mask_width) || (img_height<mask_height) )
	{
		throw GException(
				"SpatialFiltering<PTYPE>::doConvolution( const Image<PTYPE> &input_image, const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result )",
				"Filtermaske darf maximal so groß wie das Bild sein." );
	}
	if ( (img_width!=result.getWidth()) || (img_height!=result.getHeight()) )
	{
		result.resize( img_width, img_height );
	}

	//
	// Datenzeiger holen (um die Filtermaske (mask_data) zu spiegeln,
	// werden ihre Daten einfach rückwärts durchlaufen!)
	//
	MASKTYPE* mask_data   = filter_mask.getData() + filter_mask.getSize() - 1;
	PTYPE* inp_data   = input_image.getData();
	PTYPE* res_data  = result.getData();


	
	//
	// Aufsatzpunkt und Groesse des zu berechnenden Bereiches ermitteln
	//
	int start_posx = mask_width / 2;
	int start_posy = mask_height / 2;
	res_data += start_posy*img_width + start_posx;

	int width  = img_width - mask_width + 1;   // Breite des zu berechnenden Bereichs
	int height = img_height - mask_height + 1; // Hoehe des zu berechnenden Bereichs
	
	//
	// Maskenkoordinate (0,0) :
	//   Bildpixel mit Maskenwert multiplizieren und speichern
	//
	MASKTYPE mvalue = *mask_data;
	PTYPE* inp_line = inp_data;
	PTYPE* res_line = res_data;
	PTYPE* inp;
	PTYPE* res;
	
	for ( int y=0; y<height; ++y )
	{
		// Datenzeiger auf aktuellen Zeilenanfang initialisieren und 
		// Zeilenanfangszeiger auf nächste Zeile verschieben
		inp = inp_line;
		inp_line += img_width;
		
		res = res_line;
		res_line += img_width;
		
		// Zeile berechnen
		for ( int x=0; x<width; ++x )
		{
			//*(res++) = PTYPE( *(inp++) * mvalue);
			*(res++) = helpfunc_multiply( *(inp++), mvalue );
		}
	}

	//
	// Maskenkoordinaten (1,0)...(mask_width-1,0) :
	//   Bildpixel mit Maskenwert multiplizieren und zu res addieren
	//
	for ( int mask_x=1; mask_x<mask_width; ++mask_x )
	{
		// fuer Maskenspalte mask_x einstellen
		mvalue 		= *( mask_data - mask_x );
		inp_line 	=    inp_data + mask_x;
		res_line 	=    res_data;

		// Bildpixel bearbeiten
		for ( int y=0; y<height; ++y )
		{
			// Datenzeiger auf aktuellen Zeilenanfang initialisieren und 
			// Zeilenanfangszeiger auf nächste Zeile verschieben
			inp = inp_line;
			inp_line += img_width;
			
			res = res_line;
			res_line += img_width;
			
			// Zeile berechnen
			for ( int x=0; x<width; ++x )
			{
				//*(res++) += PTYPE( *(inp++) * mvalue );
				*(res++) += helpfunc_multiply( *(inp++), mvalue );
			}
		}
	}
	

	//
	// Maskenkoordinaten (0,1)...(mask_width-1,mask_height-1) :
	//   Bildpixel mit Maskenwert multiplizieren und zu res addieren
	//
	for ( int mask_y=1; mask_y<mask_height; ++mask_y )
	{
		// in Maske eine Zeile weiter gehen (wegen Spiegelung der Maske 
		// wird der Maskenzeiger eine Zeile rückwärts und der Bildzeiger eine
		// Zeile vorwärts gesetzt)
		mask_data -= mask_width;
		inp_data  += img_width;
		
		// komplette Maskenzeile berechnen
		for ( int mask_x=0; mask_x<mask_width; ++mask_x )
		{
			// fuer Maskenspalte mask_x einstellen
			mvalue 		= *( mask_data - mask_x );
			inp_line 	=    inp_data + mask_x;
			res_line 	=    res_data;
	
			// Bildpixel bearbeiten
			for ( int y=0; y<height; ++y )
			{
				// Datenzeiger auf aktuellen Zeilenanfang initialisieren und 
				// Zeilenanfangszeiger auf nächste Zeile verschieben
				inp = inp_line;
				inp_line += img_width;
				
				res = res_line;
				res_line += img_width;
				
				// Zeile berechnen
				for ( int x=0; x<width; ++x )
				{
					//*(res++) += PTYPE( *(inp++) * mvalue );
					*(res++) += helpfunc_multiply( *(inp++), mvalue );
				}
			}
		}
	}

	// 
	// Randbehandlung durchfuehren
	//
	doBoundaryCalculations( input_image, filter_mask, result );	
}

/* *********************************************************************************** */
/* Implementation der Randbehandlung (Kopieren der Pixel des Originalbildes)*/
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::doBoundaryCalculations( const Image<PTYPE> &input_image, const Image<MASKTYPE> &filter_mask, Image<PTYPE> &result )
/* *********************************************************************************** */
{
	//
	// Maskengroesse und Bildgroesse muessen nicht getestet werden, da diese Methode 
	// nur von SpatialFiltering<PTYPE>::doConvolution( input_image, filter_mask, result )
	// aufgerufen und entsprechende Tests breits dort durchgeführt werden
	
	//
	// Groessen und Datenzeiger holen
	//
	int    mask_width  = filter_mask.getWidth();
	int    mask_height = filter_mask.getHeight();
	
	int    img_width  	= input_image.getWidth();
	int    img_height 	= input_image.getHeight();
	PTYPE* inp 			= input_image.getData();
	PTYPE* res 	 		= result.getData();
	
	//
	// Randgroessen berechnen
	//
	int bsize_left  = mask_width / 2;
	int bsize_right = mask_width - bsize_left - 1;
	int bsize_up    = mask_height / 2;
	int bsize_down  = mask_height - bsize_up - 1;

	int width  = img_width - mask_width + 1;   // Breite des berechneten Bereichs
	int height = img_height - mask_height + 1; // Hoehe des berechneten Bereichs
	
	//
	// Pixelwerte des Eingabebildes in das Ergebnisbild kopieren
	//
	
	// oberer Rand
	int size = img_width * bsize_up;
	for ( int i=0; i<size; ++i)
	{
		*(res++) = *(inp++);
	}
	
	// linker Rand und rechter Rand 
	// (von Ende oberer Rand bis Ansatz unterer Rand)
	for ( int y=0; y<height; ++y )
	{
		//linker Rand dieser Zeile
		for ( int x=0; x<bsize_left; ++x )
		{
			*(res++) = *(inp++);
		}
		
		//berechneten Bereich ueberspringen
		inp += width;
		res += width;
		
		//rechter Rand dieser Zeile
		for ( int x=0; x<bsize_right; ++x )
		{
			*(res++) = *(inp++);
		}
	}
	
	//unterer Rand
	size = img_width * bsize_down;
	for ( int i=0; i<size; ++i)
	{
		*(res++) = *(inp++);
	}
}

/* *********************************************************************************** */
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::setBoxFilterMask( int size )
/* *********************************************************************************** */
{
	if (size>0)
	{
		// Maskengroesse anpassen
		m_filter_mask.resize( size, size );
		int size2 = size*size;
		
		MASKTYPE *data  = m_filter_mask.getData();
		float  value = 1.0f / size2;
	
		// jedes Maskenelementauf das vorberechnete Gewicht setzen
		for ( int i=0; i<size2; ++i )
		{
			*(data++) = value;
		}
		
		// Filtermaske vorbereitet
		m_filter_mask_available = true;
	}
	else
		m_filter_mask_available = false;
}

/* *********************************************************************************** */
template <typename PTYPE, typename MASKTYPE> 
void SpatialFiltering<PTYPE,MASKTYPE>::setGaussFilterMask( float sigma )
/* *********************************************************************************** */
{
	if (sigma>=0)
	{
		// Maskengroesse ermitteln
		// quadratisch, ungerade, mind. 3(6) sigma
		int sigma3 = (int) ceilf( 3*sigma );
		int size   = 2*sigma3 + 1;
		
		// Maskengroesse anpassen
		m_filter_mask.resize( size, size );
		
		// Gewichte berechnen
		MASKTYPE* data = m_filter_mask.getData();

		if (size==1)
		{
			*data = 1.0;
		}
		else
		{
			float f1  = 1.0f / (2.0f * M_PI * sigma*sigma);
			float f2  = - 1.0f / (2.0f * sigma*sigma);
			float sum = 0.0;
	 
	 		//
	 		// die Gewichte der Filtermaske werden in Speicherreihenfolge
	 		// durchlaufen, so dass der Index nicht berechnet werden muss
	 		//
			for ( int y= -sigma3; y<=sigma3; ++y )
			for ( int x= -sigma3; x<=sigma3; ++x )
			{
				sum += ( *(data++) = f1*expf(f2*(x*x+y*y)) );
			}
			
			// Summe der Gewichte auf 1.0 normieren
			m_filter_mask.mul( 1.0f / sum );
		}
		
		// Filtermaske vorbereitet
		m_filter_mask_available = true;
	}
	else
		m_filter_mask_available = false;
}



}

#endif /*__GET__SPATIALFILTERING_H*/
