#ifndef __GET__SIMPLE_IO_H
#define __GET__SIMPLE_IO_H

#include "image.h"

namespace GET
{



/**
 * Interface Laden und Speichern  von Bildern aus Dateien sowie zum Anzeigen auf dem Bildschirm.
 * 
 * Es handelt sich hierbei lediglich um eine Interface Klasse über die auf entsprechende 
 * Funktionen zugegriffen wird. Diese Klasse ist unabhängig von Qt und OpenCV. Sie benötigt 
 * allerdings zum Ausführen der Aufgaben eine Agentenklasse, die dann auf Qt oder die OpenCV 
 * zugreift.
 * 
 * D.h. dieses Interface ist unabhängig von Fremdbibliotheken. Die entsprechenden Aufgaben
 * können allerdings nur dann ausgeführt werden, wenn mindestens eine der Fremdbibliotheken
 * Qt oder OpenCV verwendet wird.
 * 
 * @author Holger Täubig
 * @version VORLÄUFIG FERTIG.
 * @note keine Quellen
 * 
 * @todo const images verwenden, wo dies möglich ist (vorher: ImageIO.saveImage korrigieren)
 */
class SimpleIO
{
  /* ****************************************************************************** */
  /* *** Interface für einfaches Laden/Speichern/Anzeigen von Bildern ************* */
  /* ****************************************************************************** */
	
  public:

	/** Lädt ein Bild aus einer Datei. Die Datei kann in einem Filedialog ausgewählt werden.
	 * 
	 * @param image Bildobjekt in dem das geladene Bild gespeichert werden soll (Die Größe wird automatisch angepaßt)
	 * @return true: wenn das Laden erfolgreich war; sonst false
	 */
	template <typename TYP> 
	inline static bool loadImage( Image<TYP> &image );

	/** Lädt ein Bild aus einer Datei. Die Datei kann in einem Filedialog ausgewählt werden.
	 * 
	 * @param image Bildobjekt in dem das geladene Bild gespeichert werden soll (Die Größe wird automatisch angepaßt)
	 * @return true: wenn das Laden erfolgreich war; sonst false
	 */
	static bool loadImage( Image<Rgb> &image );



	/** Speichert ein Bild in einer Datei. Die Datei kann in einem Filedialog ausgewählt werden.
	 * 
	 * @param image Bildobjekt, in dem das zu speicernde Bild steht
	 * @return true: wenn das Speichern erfolgreich war; sonst false
	 */
	template <typename TYP>
	inline static bool saveImage( Image<TYP> &image );

	/** Speichert ein Bild in einer Datei. Die Datei kann in einem Filedialog ausgewählt werden.
	 * 
	 * @param image Bildobjekt, in dem das zu speicernde Bild steht
	 * @return true: wenn das Speichern erfolgreich war; sonst false
	 */
	static bool saveImage( Image<Rgb> &image );



	/** Zeigt das übergebene Bild am Bildschirm an */
	template <typename TYP>
	inline static void showImage( Image<TYP> &image );

	/** Zeigt das übergebene Bild am Bildschirm an */
	static void showImage( Image<Rgb> &image );
	
	
	
	/** Initialisiert den Agenten (Das übergebene Objekt wird von SimpleIO absofort zu Laden/Speichern/Anzeigen von Bilder verwendet).
	 * 
	 * @param agent Zeiger auf das Objekt, das zum Ausführen der IO-Funktionen von SimpleIO verwendet werden soll
	 * @param reset Überschreiben eines bereits vorhanden Agenten (true:immer initialisieren, false:nur dann initialisieren, wenn noch kein Agent vorhanden ist)
	 */
	static void initialize( SimpleIO *agent, bool reset = true );


	
  private:
	/** Zeiger auf das Objekt, das zum Ausführen der IO-Funktionen von SimpleIO verwendet wird */
	static SimpleIO *m_agent;



  /* ****************************************************************************** */
  /* *** Interface des Agentenobjektes und Implementation eines Dummies *********** */
  /* ****************************************************************************** */

  public:
	/** Agenten-Interface: Lädt ein Bild aus einer Datei. Die Datei kann in einem Filedialog ausgewählt werden.
	 * 
	 * @param image Bildobjekt in dem das geladene Bild gespeichert werden soll (Die Größe wird automatisch angepaßt)
	 * @return true: wenn das Laden erfolgreich war; sonst false
	 */
	virtual bool load( Image<Rgb> &image );

	/** Agenten-Interface: Speichert ein Bild aus einer Datei. Die Datei kann in einem Filedialog ausgewählt werden.
	 * 
	 * @param image Bildobjekt, in dem das zu speicernde Bild steht
	 * @return true: wenn das Speichern erfolgreich war; sonst false
	 */
	virtual bool save( Image<Rgb> &image );

	/** Agenten-Interface: Zeigt das übergebene Bild am Bildschirm an */
	virtual void show( Image<Rgb> &image );
  
  	/** Konstruktor. */
	SimpleIO();
	
	/** Destruktor */
	virtual ~SimpleIO();
};



/* ****************************************************************************** */
/* *** Implementation der Templates                                   *********** */
/* ****************************************************************************** */

/* ****************************************************************************** */
template <typename TYP>
inline bool SimpleIO::loadImage( Image<TYP> &image ) 
/* ****************************************************************************** */
{ 
	Image<Rgb> tmp( 0, 0 );

	bool result = loadImage( tmp );
	image.copy( tmp );
	
	return result; 
}

template <typename TYP>
inline bool SimpleIO::saveImage( Image<TYP> &image ) 
{ 
	Image<Rgb> tmp( image );
	return saveImage( tmp );
}

template <typename TYP>
inline void SimpleIO::showImage( Image<TYP> &image ) 
{ 
	Image<Rgb> tmp( image );
	showImage( tmp );
}



}

#endif /*__GET__SIMPLE_IO_H*/
