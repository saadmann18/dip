 
#ifndef IMAGE_DISPLAYER_H
#define IMAGE_DISPLAYER_H

#include <Qt3Support>
#include <QWidget>
#include <qimage.h>
#include <qcolor.h>
#include <qpen.h>
#include <QString>

#include <image.h>
#include <polygon.h>

#define SMOOTH_SCALE 0
#define NORMAL_SCALE 1

namespace GET 
{

class ImageDisplayer : public QWidget
{
  Q_OBJECT
  public:
	ImageDisplayer( QWidget *parent=0, const char *name=0, int wFlags=0 );
	~ImageDisplayer();
	
	void setImage(Image<Rgb>);
	void setImage(Image <uchar>);
	
	void setImage(QImage);
	void setPolygons(Polygon *poly, int count, int thickness, QColor color);
	void setTextStrings(QString *strings, Point *positions, int count);
	
	void setDisplayPosition(int x, int y);
	void setDisplaySize(int w, int h, int quality=SMOOTH_SCALE);
	void doDisplayImage();
	void doDisplayImagePortion(int x1, int y1, int x2, int y2);
	
    
  protected:
	void paintEvent( QPaintEvent * );

  private:
	QImage	m_image;                  // the loaded image
	QImage	m_image_portion;		// the portion of image
	QPixmap	m_pm;                     // the converted pixmap
	QPixmap	m_pmScaled;               // the scaled pixmap
	int m_image_width, m_image_height;
	int m_display_width, m_display_height;
	int m_position_x, m_position_y;
	int m_scale_quality;
	bool m_display_it;
	
	Polygon *m_polygons_ptr;
	int m_poly_border;
	QColor m_poly_color;
	int m_poly_count;
	bool m_show_polygon;
	
	QString *m_strings_ptr;
	Point *m_text_pos_ptr;
	bool m_show_text;
	int m_string_count;
	
	void scale();


//private slots:

};

}
#endif // IMAGE_DISPLAYER_H


