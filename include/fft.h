#ifndef __GET__FFT_H
#define __GET__FFT_H

#include "image.h"
#include "dft.h"


namespace GET 
{



/**
 * Fast Fouriertransformation (Schnellere Implementation von DFT).
 * 
 * Der Fourierraum der durch diese Diskrete Fouriertransformation erzeugt
 * wird gibt die Frequenzen relativ zur Einheitsl�nge 1 an. D.h. er verwendet
 * keine Kreisfreuenzen (diese w�rden relativ zu einer Einheitsl�nge von 2*Pi
 * angegeben werden).
 * 
 * Der Code wurde von Zaheer Aziz �bernommen und an GETLib angepasst. Es k�nnen bisher
 * lediglich quadratische Bilder mit Seitl�ngen die einer Zweierpotenz entsprechen berechnet
 * werden. F�r alle anderen Bilder wird auf die langsame Berechnung durch die Klasse DFT
 * umgeschaltet.
 * 
 * @author Zaheer Aziz
 * @author Holger T�ubig
 * @version FUNKTIONSF�HIG.
 * 
 * @note: Quelle der Erstimplementation: Zaheer Aziz
 * 
 * @todo Zus�tzliche Transformationsmethoden float->Complex und float<-Complex einf�hren, um die
 * Zeitverschwendung durch Kopieren zu reduzieren, wenn im Ortsraum ein Image<float>
 * vorliegt bzw. ben�tigt wird.
 */
class FFT : public DFT
{
  private:
  	/** Gr��e der Sinustabelle */
	static int    cm_sintable_size;
	/** Sinustabelle */
	static float *cm_sintable;

	/** Erzeugt die Sinustabelle 
	 * 
	 * @param sintable_size Gr��e der zu erzeugenden Sinustabelle 
	 */
	static float *doComputeSintable( int sintable_size );
	
	       /**
	        * Implementation des Algorithmus zur Fast Fourier Transformation
	        */
	       int  doFFT (int dir,int n, Complex *data);
	       /** Hilfsfunktion zu doFFT (int dir,int n, Complex *data) */
	       void doBitReverseReorder (int n, Complex *data);
	       /** Hilfsfunktion zu doFFT (int dir,int n, Complex *data) */
	inline bool doCheckSize( int n );
	
  public:
 	/** Konstruktor */
	FFT( int size_max = 256, ScalingType scaling = SCALE_ON_TRANSFORMATION );
	/** Destruktor. */
	~FFT( ) { };
  
  	void doFourierTransform   ( const Image<Complex> &original_image, Image<Complex> &fourier_image );
  	void doFourierTransform2D ( const Image<Complex> &original_image, Image<Complex> &fourier_image );
	void doInvFourierTransform   ( const Image<Complex> &fourier_image,  Image<Complex> &original_image );
	void doInvFourierTransform2D ( const Image<Complex> &fourier_image,  Image<Complex> &original_image );
	void doInvFourierTransform   ( const Image<Complex> &fourier_image,  Image<float> &original_image );
	void doInvFourierTransform2D ( const Image<Complex> &fourier_image,  Image<float> &original_image );

	/** wie doFourierTransform( const Image<Complex> &original_image, Image<Complex> &fourier_image ) 
	 * aber mit einem Bild f�r Input und Output
	 */
	void doFourierTransform   ( Image<Complex> &image );
	/** wie doFourierTransform2D ( const Image<Complex> &original_image, Image<Complex> &fourier_image )
	 * aber mit einem Bild f�r Input und Output
	 */
  	void doFourierTransform2D ( Image<Complex> &image );
	/** wie doInvFourierTransform   ( const Image<Complex> &fourier_image,  Image<Complex> &original_image )
	 * aber mit einem Bild f�r Input und Output
	 */
	void doInvFourierTransform   ( Image<Complex> &image );
	/** wie doInvFourierTransform2D ( const Image<Complex> &fourier_image,  Image<Complex> &original_image )
	 * aber mit einem Bild f�r Input und Output
	 */
	void doInvFourierTransform2D ( Image<Complex> &image );
};





} /* namespace GET */

#endif /* __IMAGE_H */
