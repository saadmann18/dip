#ifndef __GET__QT_IMAGE_IO_H
#define __GET__QT_IMAGE_IO_H

#include <Qt3Support>	
#include <QImage>
#include <qcolor.h> 
#include <qfiledialog.h> 
#include <image.h>


namespace GET
{
	
		

#define JPG 0
#define jpg 0

#define JPEG 1
#define jpeg 1

#define BMP 2
#define bmp 2

#define PBM 3
#define pbm 3

#define PGM 4
#define pgm 4

#define PNG 5
#define png 5

#define PPM 6
#define ppm 6

#define XPM 7
#define xpm 7

#define XBM 8
#define xbm 8



/**
 * Laden und Speicher von Bilder mittels Qt
 * 
 * @todo vermutlich fehlt bei einigen saveImage Methoden:   io_name = io_name2;
 * @todo imageio.h von QTHEADER zu normalen Headern verschieben (Makefile.am)
 */
class ImageIO
 
{
    public:
       ImageIO();
     ~ImageIO();
  
       bool    saveImage(const QString&, Image<QRgb>&, int);
       bool    saveImage(const QString&, Image<QRgb>&, const QString&);
       bool    saveImage(Image<QRgb>&, int);
       bool    saveImage(Image<QRgb>&);
       bool    openImage(const QString&, Image<QRgb>&);
       bool    openImage(Image<QRgb>&);
       
       
       bool    saveImage(const QString&, Image<Rgb>&, int);
       bool    saveImage(const QString&, Image<Rgb>&, const QString&);
       bool    saveImage(Image<Rgb>&, int);
       bool    saveImage(Image<Rgb>&);
       bool    openImage(const QString&, Image<Rgb>&);
       bool    openImage(Image<Rgb>&);
       
       
       bool    saveImage(const QString&, Image<uchar>&, int);
       bool    saveImage(const QString&, Image<uchar>&, const QString&);
       bool    saveImage(Image<uchar>&, int);
       bool    saveImage(Image<uchar>&);
       bool    openImage(const QString&, Image<uchar>&);
       bool    openImage(Image<uchar>&);
       
       
       
       void    set_image(const QImage&);
       void    set_image(const QImage&, Image<QRgb>&);
       void    set_image(const QImage&, Image<Rgb>&);
       void    set_image(const QImage&, Image<uchar>&);
 
       QString  get_file_name(){ return io_name;};
       QString  get_file_format(){return io_format;};
       QImage get_image(){ return io_image;};
       
      
       
       
    private:
       void                 switch_format(const QString&, int);
       void                 do_save_w_format(int);
       void                 do_save();
       void                 do_open();
       void                 add_format(const QString&, const QString&);
       
       void                 setData_qrgb(Image<QRgb>&);  
       void                 getData_qrgb(Image<QRgb>&);
       
       void                 setData_rgb(Image<Rgb>&);  
       void                 getData_rgb(Image<Rgb>&);
       
       void                 setData_uch(Image<uchar>&);  
       void                 getData_uch(Image<uchar>&);
       
       
       
       
       QString           detectFormat(const QString&);
              
       QRgb              PixColor ;
       QColor            Pcolor;
        
       int                    W;
       int                    H;
       int*                  data1;
       bool                ok;
   
       QString           types;
       QString           io_types ;
       QString           io_format ;
       QString           io_name ;  
       QImage          io_image;
      
       
};

} /* namespace GET */

#endif // __GET__QT_IMAGE_IO_H

