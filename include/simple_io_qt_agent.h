#ifndef __GET__SIMPLE_IO_QT_AGENT_H
#define __GET__SIMPLE_IO_QT_AGENT_H

#include "simple_io.h"

#include "imageio.h"
#include "imagedisplayer.h"


namespace GET
{



/**
 * Basisklasse f�r einfache Ausgaberoutinen mittel Qt.
 * Diese Klasse �bernimmt das Handling von QApplication.
 * 
 * Einfache Ausgaberoutinen (in KLassen, die von dieser Klasse abgeleitet sind,
 * m�ssen vor dem Erzeugen des Widgets die Methode checkApplication()
 * aufrufen. Nachdem Das Widget erzuegt ist, wird es mit simpleShowWidget( Widget ) angezeigt.
 */
class SimpleIOQtBase
{
  private:
	QApplication 	*m_qapp;
	int   			 m_qapp_argc;
	char 			*m_qapp_argv;
	
  public:
	SimpleIOQtBase( );
	
	/**
	 * Diese Methode muss vor dem Erzeugen des ersten Widgets aufgerufen werden.
	 */
	void checkQApplication( );
	
	/**
	 * Zeigt das �bergebene Widget an und wartet bis es geschlossen wurde.
	 */
	void simpleShowWidget( QWidget &widget );
};



/**
 * Objekte dieser Klasse k�nnen unter Verwendung von Qt Bilder laden (load()), speichern (save()) 
 * und anzeigen (show()). #Normalerweise# muss ein Nutzer #keine Objekte dieser Klasse erstellen#,
 * da alle Funktionen �ber SimpleIO angesprochen werden sollten (Vorteil: SimpleIO verwendet
 * automatisch SimpleIOQtAgent oder SimpleIOOpenCVAgent).
 * 
 * @author Holger T�ubig
 * @version VORL�UFIG FERTIG.
 * @note keine Quellen.
 */
class SimpleIOQtAgent : public GET::SimpleIO, private SimpleIOQtBase
{
  private:
	ImageIO 			*m_qt_imageio;
	ImageDisplayer 	*m_qt_imagedisplayer;
	
	
  public:
	/** Agenten-Interface: L�dt ein Bild aus einer Datei. Die Datei kann in einem Filedialog ausgew�hlt werden.
	 * 
	 * @param image Bildobjekt in dem das geladene Bild gespeichert werden soll (Die Gr��e wird automatisch angepa�t)
	 * @return true: wenn das Laden erfolgreich war; sonst false
	 */
	virtual bool load( Image<Rgb> &image );

	/** Agenten-Interface: Speichert ein Bild aus einer Datei. Die Datei kann in einem Filedialog ausgew�hlt werden.
	 * 
	 * @param image Bildobjekt, in dem das zu speicernde Bild steht
	 * @return true: wenn das Speichern erfolgreich war; sonst false
	 */
	virtual bool save( Image<Rgb> &image );

	/** Agenten-Interface: Zeigt das �bergebene Bild am Bildschirm an */
	virtual void show( Image<Rgb> &image );

	/** Konstruktor 
	 * 
	 * Der Parameter attach_to_SimpleIO sollte nicht auf true gesetzt werden, da das erzeugte
	 * Objekt dann absofort von SimpleIO verwendet wird. (Zu diesem Zweck existiert allerdings 
	 * bereits ein Objekt von SimpleIOQtAgent, so dass die Verwendung diese Parameters bzw. 
	 * das Ersetzen des von SimpleIO verwendeten Objektes nie notwendig sein sollte).
	 * 
	 * @param attach_to_SimpleIO immer auf false lassen*/
	SimpleIOQtAgent( bool attach_to_SimpleIO = false );

	/** Destruktor. */
	virtual ~SimpleIOQtAgent();
};



}

#endif /*__GET__SIMPLE_IO_QT_AGENT_H*/
