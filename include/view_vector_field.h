#ifndef __GET__VIEW_VECTOR_FIELD_H
#define __GET__VIEW_VECTOR_FIELD_H

#include "vector_field.h"

#include "simple_io_qt_agent.h"

#include <Qt3Support>
#include <Q3Canvas>
#include <Q3PopupMenu>

 #include <Qt>
 
namespace GET
{



/**
 * Darstellung eines Vektorfeldes.
 * 
 * Das Vektorfeld muss zunächst als Objekt vom Typ VectorField 
 * erzeugt werden und danach können beliebig viele 
 * Ansichten (Objekte von ViewVectorField) dafür erzeugt werden.
 * 
 * @see Dokumentation zu QT 3.0 unter Q3Canvas und Q3CanvasView
 * 
 * @author Holger Täubig
 * @version FERTIG.
 * @note keine Quellen, aber Ideen/Hilfen aus der QT-Dokumentation verwendet
 */
class ViewVectorField : public Q3CanvasView {
    Q_OBJECT

  public:
  
	/**
	 * Konstruktor.
	 */
	ViewVectorField( VectorField& vector_field, QWidget* parent=0, const char* name=0, WFlags f=0 );
	
	/**
	 * Skaliert die Darstellung entsprechende der Faktoren in x- und y-Richtung.
	 * 
	 * @param sx Skalierung in x-Richtung
	 * @param sy Skalierung in y-Richtung
	 */
	void scale( double sx, double sy );

	/**
	 * Skaliert die Darstellung.
	 * 
	 * @param s Skalierungsfaktor
	 * 
	 * @see scale( double sx, double sy )
	 */
	inline void scale( double s )
	{
		scale( s, s );
	};
	
	
	
	/**
	 * Einfache Anzeige für Vektorfelder.
	 *
	 * @param vector_image Bild, das das Vektorfeld enthält.
	 * 
	 * @todo Vernünftig überarbeiten und SimpleIOQtBase strukturieren.
	 */
	static void simpleShow( const Image<Vector2D> &vector_image );
	
  
  
  private:
  
	/**
	 * Referenz auf das zugehörige Vektorfeld.
	 */
	VectorField& 	m_vector_field;

  protected:
  
	/**
	 * Komntextmenü für die rechte Maustaste.
	 */
	QPopupMenu menu;
	
	/**
	 * Verarbeitung des Mausevents.
	 */
	virtual void mousePressEvent ( QMouseEvent * e );
	
  private slots:

	/**
	 * Speichert den sichtbaren Bereich [SLOT]
	 */
	void save();
	
	/**
	 * Speichert das gesamt Bild (auch die nicht sichbaren Teile) [SLOT]
	 */
	void saveAll();
};



}



#endif /*__GET__VIEW_VECTOR_FIELD_H*/
