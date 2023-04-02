#pragma once

#include "vector_field.h"

#include "simple_io_qt_agent.h"

#include <Qt3Support>
#include <Q3Canvas>
#include <Q3PopupMenu>

 #include <Qt>
 
namespace GET
{

/**
 * Representation of a vector field.
 * 
 * The vector field must first be created as an object of the VectorField type 
 * and then any number of views (objects of ViewVectorField) can be created for it.
 * 
 * @see QT 3.0 documentation on Q3Canvas and Q3CanvasView
 * 
 * @author Holger Täubig
 * @version COMPLETE.
 * @note no sources, but uses ideas/help from the QT documentation
 */
class ViewVectorField : public Q3CanvasView {
    Q_OBJECT

  public:
  
	// Constructor.

	ViewVectorField( VectorField& vector_field, QWidget* parent=0, const char* name=0, WFlags f=0 );
	
	/**
	 * Scales the display according to the factors in the x and y directions.
	 * 
	 * @param sx Scaling in x-direction
	 * @param sy Scaling in y-direction
	 */
	void scale( double sx, double sy );

	/**
	 * Scales the display.
	 * 
	 * @param s scaling factor
	 * 
	 * @see scale( double sx, double sy )
	 */
	inline void scale( double s )
	{
		scale( s, s );
	};
	
	
	
	/**
	 * Simple indicator for vector fields.
	 *
	 * @param vector_image Image, containing the vector field.
	 * 
	 * @todo Revise sensibly and structure SimpleIOQtBase.
	 */
	static void simpleShow( const Image<Vector2D> &vector_image );
	
  
  
  private:
  
	// Reference to the associated vector field.

	VectorField& 	m_vector_field;

  protected:
  
	// Right mouse button context menu.

	QPopupMenu menu;
	
	//Processing of the mouse event.

	virtual void mousePressEvent ( QMouseEvent * e );
	
  private slots:

	// Saves the visible area [SLOT]

	void save();
	
	// Saves the entire image (including the non-visible parts) [SLOT]

	void saveAll();
};

}

