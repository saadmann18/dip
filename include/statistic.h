#ifndef __GET__STATISTIC_H
#define __GET__STATISTIC_H

#include "image.h"
#include "imagesequence.h"

namespace GET
{


/**
 * Ermittelt Statistiken wie Minimum, Maximum, usw.
 * 
 * @author Holger Täubig
 * @version FUNKTIONSFÄHIG.
 * 
 * @todo Anpassung der min und max Funktion für die Übung Kognitive Systeme.
 */
class Statistic
{
private:
	int m_index_last_maximum;
	int m_index_last_minimum;
public:
	/**
	 * Ermittelt das Maximum aller Bildpixel.
	 * 
	 * Diese Methode kann nur angewendet werden, wenn für den Basisdatentyp
	 * des Bildes(TYP) der Vergleichsoperator > deklariert ist. Für ein leeres
	 * Bild (keine Pixel) ist der Wert des Maximum unbestimmt.
	 * 
	 * @param image Bild 
	 * @return maximaler Pixelwert von image 
	 */
	template <typename TYP>
	TYP getMax( const Image<TYP> &image );
	
	/**
	 * Ermittelt das Minimum aller Bildpixel.
	 * 
	 * Diese Methode kann nur angewendet werden, wenn für den Basisdatentyp
	 * des Bildes(TYP) der Vergleichsoperator > deklariert ist. Für ein leeres
	 * Bild (keine Pixel) ist der Wert des Minimum unbestimmt.
	 * 
	 * @param image Bild 
	 * @return minimaler Pixelwert von image
	 */
	template <typename TYP>
	TYP getMin( const Image<TYP> &image );
	
	/**
	 * Ermittelt Minimum und Maximum aller Bildpixel.
	 * 
	 * Diese Methode kann nur angewendet werden, wenn für den Basisdatentyp
	 * des Bildes(TYP) der Vergleichsoperator > deklariert ist. Für ein leeres
	 * Bild (keine Pixel) ist der Wert von Maximum und Minimum unbestimmt.
	 * 
	 * @param image Bild (Input)
	 * @param maximum maximaler Pixelwert von image (Output)
	 * @param minimum minimaler Pixelwert von image (Output)
	 */
	template <typename TYP>
	void getMaxMin( const Image<TYP> &image, TYP &maximum, TYP &minimum );



	/**
	 * Ermittelt das Maximum aller Bildpixel einer Bildsequenz.
	 * 
	 * Diese Methode kann nur angewendet werden, wenn für den Basisdatentyp
	 * des Bildes(TYP) der Vergleichsoperator > deklariert ist. Für ein leeres
	 * Bild (keine Pixel) ist der Wert des Maximum unbestimmt.
	 * 
	 * Der Aufruf von getLastMaxIndex() liefert nach dieser Operation kein
	 * sinnvolles Ergebnis!
	 * 
	 * @param imageseq Bildsequenz
	 * @return maximaler Pixelwert von image 
	 */
	template <typename TYP>
	TYP getMax( const ImageSequence<TYP> &imageseq );
	
	/**
	 * Ermittelt das Minimum aller Bildpixel einer Bildsequenz.
	 * 
	 * Diese Methode kann nur angewendet werden, wenn für den Basisdatentyp
	 * des Bildes(TYP) der Vergleichsoperator > deklariert ist. Für ein leeres
	 * Bild (keine Pixel) ist der Wert des Minimum unbestimmt.
	 * 
	 * Der Aufruf von getLastMinIndex() liefert nach dieser Operation kein
	 * sinnvolles Ergebnis!
	 * 
	 * @param imageseq Bildsequenz 
	 * @return minimaler Pixelwert von image
	 */
	template <typename TYP>
	TYP getMin( const ImageSequence<TYP> &imageseq );
	
	/**
	 * Ermittelt Minimum und Maximum aller Bildpixel einer Bildsequenz.
	 * 
	 * Diese Methode kann nur angewendet werden, wenn für den Basisdatentyp
	 * des Bildes(TYP) der Vergleichsoperator > deklariert ist. Für ein leeres
	 * Bild (keine Pixel) ist der Wert von Maximum und Minimum unbestimmt.
	 * 
	 * Die Aufrufe von getLastMaxIndex() und getLastMinIndex() liefern nach 
	 * dieser Operation kein sinnvolles Ergebnis!
	 * 
	 * @param imageseq Bildsequenz (Input)
	 * @param maximum maximaler Pixelwert von image (Output)
	 * @param minimum minimaler Pixelwert von image (Output)
	 */
	template <typename TYP>
	void getMaxMin( const ImageSequence<TYP> &imageseq, TYP &maximum, TYP &minimum );



	/**
	 * liefert den Index des letzten durch getMax(...) oder getMaxMin(...)
	 * ermittelten Maximums.
	 * 
	 * @return Index des letzten Maximums	
	 */
	inline int getLastMaxIndex( ) { return m_index_last_maximum; };

	/**
	 * liefert den Index des letzten durch getMin(...) oder getMaxMin(...)
	 * ermittelten Minimums.
	 * 
	 * @return Index des letzten Minimums	
	 */
	inline int getLastMinIndex( ) { return m_index_last_minimum; };
	
	/** Konstruktor */
	Statistic( ) :
		m_index_last_maximum( -1 ),
		m_index_last_minimum( -1 )
	{ };
};



/* ****************************************************************************** */
/* **** Implementation der Templates ******************************************** */
/* ****************************************************************************** */

/* ****************************************************************************** */
template <typename TYP>
TYP Statistic::getMax( const Image<TYP> &image )
/* ****************************************************************************** */
{
	int  size = image.getSize();
	TYP* data = image.getData();
	TYP  max;
	int  index; 

	if (size>=1)
	{
		// Maximum auf 1. Pixelwert
		max   = data[0];
		index = 0;
		
		// alle weiteren Pixel nach dem Maximum durchsuchen
		for ( int i=1; i<size; ++i )
		{
			if (data[i]>max)
			{
				max   = data[i];
				index = i;
			}
		}
		
		// Index speichern und Maximum zurück liefern
		m_index_last_maximum = index;
	}
	else
	{
		// kein Pixel vorhanden, also auch kein Maximum (Wert unbestimmt)
		m_index_last_maximum = -1;
	}
		
	return max;
}

/* ****************************************************************************** */
template <typename TYP>
TYP Statistic::getMin( const Image<TYP> &image )
/* ****************************************************************************** */
{
	int  size = image.getSize();
	TYP* data = image.getData();
	TYP  min;
	int  index; 

	if (size>=1)
	{
		// Minimum auf 1. Pixelwert
		min   = data[0];
		index = 0;
		
		// alle weiteren Pixel nach dem Minimum durchsuchen
		for ( int i=1; i<size; ++i )
		{
			if (min>data[i])
			{
				min   = data[i];
				index = i;
			}
		}
		
		// Index speichern und Minimum zurück liefern
		m_index_last_minimum = index;
	}
	else
	{
		// kein Pixel vorhanden, also auch kein Minimum (Wert unbestimmt)
		m_index_last_minimum = -1;
	}
		
	return min;
}

/* ****************************************************************************** */
template <typename TYP>
void Statistic::getMaxMin( const Image<TYP> &image, TYP &max, TYP &min )
/* ****************************************************************************** */
{
	int  size = image.getSize();
	TYP* data = image.getData();
	int  index_max; 
	int  index_min; 

	if (size>=1)
	{
		// Maximum auf 1. Pixelwert
		max = min = data[0];
		index_max = index_min = 0;
		
		// alle weiteren Pixel nach dem Maximum durchsuchen
		for ( int i=1; i<size; ++i )
		{
			if (data[i]>max)
			{
				max       = data[i];
				index_max = i;
			}
			else if (min>data[i])
			{
				min       = data[i];
				index_min = i;
			}
		}
		
		// Index speichern
		m_index_last_maximum = index_max;
		m_index_last_minimum = index_min;
	}
	else
	{
		// kein Pixel vorhanden, also auch kein Maximum oder Minimum (Wert unbestimmt)
		m_index_last_maximum = -1;
		m_index_last_minimum = -1;
	}
}



/* ****************************************************************************** */
template <typename TYP>
TYP Statistic::getMax( const ImageSequence<TYP> &imageseq )
/* ****************************************************************************** */
{
	int  size = imageseq.getSize();
	TYP  max;

	if ( (size>=1) && (imageseq.getImageWidth()>0) && (imageseq.getImageHeight()>0) )
	{
		// Maximum des 1. Bildes
		max = getMax( imageseq[0] );
		
		// alle weiteren Bilder nach dem Maximum durchsuchen
		TYP tmp;
		for ( int i=1; i<size; ++i )
		{
			tmp = getMax( imageseq[i] );
			if ( tmp>max )
				max = tmp;
		}
	}
		
	return max;
}

/* ****************************************************************************** */
template <typename TYP>
TYP Statistic::getMin( const ImageSequence<TYP> &imageseq )
/* ****************************************************************************** */
{
	int  size = imageseq.getSize();
	TYP  min;

	if ( (size>=1) && (imageseq.getImageWidth()>0) && (imageseq.getImageHeight()>0) )
	{
		// Minimum des 1. Bildes
		min = getMin( imageseq[0] );
		
		// alle weiteren Bilder nach dem Minimum durchsuchen
		TYP tmp;
		for ( int i=1; i<size; ++i )
		{
			tmp = getMin( imageseq[i] );
			if ( min>tmp )
				min = tmp;
		}
	}
		
	return min;
}

/* ****************************************************************************** */
template <typename TYP>
void Statistic::getMaxMin( const ImageSequence<TYP> &imageseq, TYP &max, TYP &min )
/* ****************************************************************************** */
{
	int  size = imageseq.getSize();

	if ( (size>=1) && (imageseq.getImageWidth()>0) && (imageseq.getImageHeight()>0) )
	{
		// Maximum und Minimum des 1. Bildes
		getMaxMin( imageseq[0], max, min );
		
		// alle weiteren Bilder nach dem Maximum und Minimum durchsuchen
		TYP tmp_max;
		TYP tmp_min;
		for ( int i=1; i<size; ++i )
		{
			getMaxMin( imageseq[i], tmp_max, tmp_min );

			if ( tmp_max>max )
				max = tmp_max;

			if ( min>tmp_min )
				min = tmp_min;
		}
	}
}



}

#endif //__GET__STATISTIC_H
