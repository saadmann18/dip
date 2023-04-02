#pragma once
#include "image.h"
#include "gvector.h"

#include <Qt3Support>
#include <Q3Canvas>


 
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
 
class VectorField: public Q3Canvas 
{
    Q_OBJECT

  public:
	/**
	 * Constructor.
	 * 
	 * @param width Width of the output area
	 * @param height Height of the output area
	 * @param subpixel Number of subpixels per unit length to be used for displaying the arrows. 
	 * #Caution: The output image will be subpixel larger than width x height.#
	 */
	VectorField( int width, int height, int subpixel = 10 );
	
	
	/**
	 * Set data.
	 * 
	 * Arrows are only drawn at the pixels where the vector length is greater than 0.
	 * 
	 * If 0 is passed as the size of the arrowhead, it will be adjusted for each 
	 * individual arrow relative to the length of the arrow (25%).
	 * 
	 * @param data Image with the vectors (each pixel is of type Point)
	 * @param arrow_size Arrowhead size in subpixels (0=adapted to arrow size)
	 */
	void setData( const Image<Vector2D> &data, int arrow_size = 0 );

	/**
	 * Set data with pen, fill brush and depth z.
	 * 
	 * Arrows are only drawn at the pixels where the vector length is greater than 0.
	 * 
	 * If 0 is passed as the size of the arrowhead, it will be adjusted for each individual arrow 
	 * relative to the length of the arrow (25%).
	 * 
	 * @param data   Image with the vectors (each pixel is of type Point)
	 * @param pen    Pen (see QPen) used to draw the data
	 * @param brush  Fill (see QBrush) used to paint the data
	 * @param arrow_size Arrowhead size in subpixels (0=adapted to arrow size)
	 * @param z      Depth (z dimension) at which the data is plotted
	 */
	void setData( const Image<Vector2D> &data, QPen pen, QBrush brush = QBrush(Qt::SolidPattern), int arrow_size = 0, double z = 0.0 );

  private:
  
	/**	
	 * Number of subpixels to be used per unit length for displaying the arrows. 
	 * 
	 * @see VectorField()
	 */
	int m_subpixel;
};



/**
 * Helper class: Q3CanvasItem for drawing an arrow.
 * 
 * The representation of this Q3CanvasItem consists 
 * of a line (derived from Q3CanvasLine) and a filled 
 * triangle as an arrowhead (Element: Q3CanvasPolygon arrow).
 * 
 * The size of the arrowhead is relative to the length of the arrow (25%).
 * 	
 * @see Used by VectorField or ViewVectorField
 * @see Dokumentation zu QT 3.0 unter Q3Canvas und Q3CanvasView
 * 
 * @author Holger Täubig
 * @version COMPLETE.
 * @note No sources, but uses ideas/help from the QT documentation
 */
class CanvasItemArrow : public Q3CanvasLine
{
  protected:
	/** Q3CanvasItem zum Zeichnen der Pfeilspitze */
	Q3CanvasPolygon* arrow;
	
  public:
	/**
	 * Constructor.
	 * 
	 * Creates a new arrow whose start and end points still have to be set using setPoints().
	 * 
	 * @param canvas Q3Canvas object, to wrap this Q3CanvasItem in
	 */
	inline CanvasItemArrow( Q3Canvas *canvas ) :
		Q3CanvasLine( canvas )
	{
		arrow = new Q3CanvasPolygon( canvas );
		arrow->setBrush( Qt::SolidPattern );
	};

	/**
	 * Sets the start and end point of the arrow.
	 * All coordinates are specified in the coordinate system of the Q3 
	 * Canvas object (Vector Field) to which this element belongs.
	 *
	 * @param x1 x-Coordinate of the starting point
	 * @param y1 y-Coordinate of the starting point
	 * @param x2 x-Coordinate of the end point
	 * @param y2 y-Coordinate of the end point
	 */
	virtual void setPoints ( int x1, int y1, int x2, int y2 );	

	/**
	 * Overridden virtual method to apply the change to line and arrowhead.
	 */
	virtual void setBrush ( QBrush b );
	/**
	 * Overridden virtual method to apply the change to line and arrowhead.
	 */
	virtual void setPen ( QPen p );
	/**
	 * Overridden virtual method to apply the change to line and arrowhead.
	 */
	void setZ( double z );
}; 



/**
 * CanvasItemArrow with a fixed size arrowhead.
 * 
 * The size of the arrowhead is passed to the constructor. The tip is then this 
 * size (in pixels) regardless of the length of the arrow.
 * 
 * @see CanvasItemArrow
 * @see QT 3.0 documentation on Q3Canvas and Q3CanvasView
 * 
 * @author Holger Täubig
 * @version COMPLETE.
 * @note No sources, but uses ideas/help from the QT documentation
 */
class CanvasItemFixedArrow : public CanvasItemArrow
{
  private:
	/**
	 * Arrowhead size in pixels.
	 */
	float m_arrow_size;
	
  public:
	/**
	 * Constructor.
	 * 
	 * Creates a new arrow whose start and end points still have to be set using setPoints().
	 * 
	 * The size of the arrowhead is passed to the constructor. The tip is then this size (in pixels) 
	 * regardless of the length of the arrow.
	 * 
	 * @param canvas Q3Canvas-object, to wrap this Q3CanvasItem in
	 * @param arrow_size Arrowhead size in pixels
	 */
	inline CanvasItemFixedArrow( Q3Canvas *canvas, int arrow_size ) :
		CanvasItemArrow( canvas ),
		m_arrow_size( arrow_size )
	{
	};


	/**
	 * Sets the start and end point of the arrow.
	 * All coordinates are specified in the coordinate system of the Q3 Canvas 
	 * object (Vector Field) to which this element belongs.
	 *
	 * @param x1 x-Coordinate of the starting point
	 * @param y1 y-Coordinate of the starting point
	 * @param x2 x-Coordinate of the end point
	 * @param y2 y-Coordinate of the end point
	 */
	virtual void setPoints ( int x1, int y1, int x2, int y2 );	
};
	
}

