#ifndef __GET__GABOR_FILTER_H
#define __GET__GABOR_FILTER_H

#include "image.h"
#include "imagesequence.h"
#include "gvector.h"  // 2-dimensionale Vektoren der GETLIB (Vector2d)
#include "frequencydomainfiltering.h"

#include <vector>  // Vektoren der STL im Sinne von dynamischen Arrays (std::vector)


namespace GET 
{



/**
 * Gaborfilter.
 * 
 * Diese Klasse erzeugt und verwaltet eine Gabor-Filterbank, die in
 * Bildgr��e(Filtermaskengr��e), Anzahl der Orientierungen und Zentralfrequenz
 * parametrisiert werden kann. \n
 * Mittels doGaborFiltering() kann das Ergebnis der Gaborfilterung (Liste mit
 * Filterergebnissen der einzelnen Orientierungen) bestimmt werden.
 * 
 * Diese Klasse arbeitet nur mit quadratischen Filtermasken (siehe m_width)
 * 
 * @author Holger T�ubig
 * @version VORL�UFIG FERTIG.
 * @note Erstimplementation von Zaheer Aziz �bernommen und umgeschrieben
 * 
 * @todo Zus�tzliche Methode einf�hren, die auf Image<float> arbeitet und daf�r
 * optimiert wurde (haupts�chlich Implementation dieser Methode f�r aufgerufene
 * FilterKlasse).
 */
class GaborFilter
{
  private:
	/** Anzahl der Orientierungen der Gabor-Filterbank */
	int m_orientations;

	/** Filtergr��e (Breite,H�he).
	 * 
	 * Breite und H�he des Gaborfilters. Diese Klasse arbeitet nur mit
	 * quadratischen Filtermasken. Dies bedeutet gleichzeitig, dass auch 
	 * die zu filternden Bilder eine Gr��e von m_width*m_width besitzen m�ssen.
	 */
	int m_width;               

	/** Zentralfrequenz der Gaborfilterbank */
	float m_k0;
	
	/** �berlappungsgrad der einzelnen Orientierungen */
	float m_overlapping;

	/**
	 * Neuberechnung der Filterbank.
	 *  
	 * Dieses Flag zeigt an (wenn true), dass die Filterbank vor der 
	 * n�chsten Benutzung neuberechnet werden muss.
	 */
	bool m_create_filter; 

	/** Filterbank.
	 * 
	 * Hier sind die Filtermasken f�r die einzelnen Orientierungen gespeichert.
	 */
	ImageSequence<float> m_filterbank;                                       
	
	/**
	 * Algorithmus zur Filterung im Frequenzraum.
	 */
	FastFrequencyDomainFiltering a_filtering;



	/**
	 * Speichert die Frequenzvektoren aller Orientierungen f�r die letzte durchgef�hrte Grabortansformation.
	 */
	std::vector<Vector2D> m_frequency_vectors;


  public:

	/** 
	 * Erzeugt eine Gaborfilterbank mit Zentralfrequenz 1/8 * Pi und 4 Orientierungen.
	 * 
	 * @see setOrientations()
	 * @see setCentroidFrequency()
	 */
  	GaborFilter( );

	/**
	 * Erzeugt eine Gaborfilterbank mit den angegebenen Parametern.
	 * 
	 * Beim Aufruf dieses Konstruktor wird die Filterbank sofort erzeugt. 
	 * #Dies kann eine m�glicherweise erhebliche Rechenzeit in Anspruch nehmen.#
	 * 
	 * @param filter_width Breite der Gaborfiltermaske (gleichzeitig auch H�he der Filtermaske)
	 * @param orientations Anzahl der Orientierungen
	 * @param centroid_frequency Zentralfrequenz der Gaborfilterbank
	 * @param overlapping �berlappungsgrad der einzelnen Orientierungen
	 * 
	 * @see setOrientations()
	 * @see setFilterSize()
	 * @see setCentroidFrequency()
	 */
  	GaborFilter( int filter_width, int orientations, float centroid_frequency, float overlapping = 0.5 );



	/**
	 * Setzt die Parameter der Filterbank.
	 * 
	 * Beim Aufruf dieser Methode wird die Filterbank sofort erzeugt. #Dies kann eine
	 * m�glicherweise erhebliche Rechenzeit in Anspruch nehmen.#
	 * 
	 * @param filter_width Breite der Gaborfiltermaske (gleichzeitig auch H�he der Filtermaske)
	 * @param orientations Anzahl der Orientierungen
	 * @param centroid_frequency Zentralfrequenz der Gaborfilterbank
	 * @param overlapping �berlappungsgrad der einzelnen Orientierungen
	 * 
	 * @see setOrientations()
	 * @see setFilterSize()
	 * @see setCentroidFrequency()
	 */
	void setParameters( int filter_width, int orientations, float centroid_frequency, float overlapping = 0.5 );
	
	/**
	 * Setzt die Anzahl der Orientierungen der Gabor-Filterbank 
	 * 
	 * @param orientations Anzahl der Orientierungen
	 */
	void setOrientations( int orientations );

	/**
	 * Setzt Breite und H�he der Gaborfiltermasken.
	 * 
	 * Diese Klasse arbeitet nur mit quadratischen Filtermasken. 
	 * Die �bergeben Seitenl�nge wird deshalb als H�he und als Breite 
	 * der Filtermaske verwendet.
	 * 
	 * Dies bedeutet gleichzeitig, dass auch 
	 * die zu filternden Bilder eine Gr��e von width*width besitzen m�ssen.
	 * 
	 * @param width Breite der Gaborfiltermaske (gleichzeitig auch H�he der Filtermaske)
	 */
	void setFilterSize(  int width );
	
	/**
	 * Setzt die Zentralfrequenz und den �berlappungsgrad der einzelnen Orientierungen f�r die Gaborfilterbank.
	 * 
	 * @param k0 Zentralfrequenz der Gaborfilterbank
	 * @param overlapping �berlappungsgrad der einzelnen Orientierungen
	 */
	void setCentroidFrequency(  float k0, float overlapping = 0.5 );
	
	
	
	/**
	 * Liefert die Anzahl der Orientierungen.
	 */
	inline int getOrientations( ) const
	{
		return m_orientations;
	};
	
	/**
	 * Liefert die Filterbreite/-h�he.
	 * 
	 * Der Gaborfilter arbeitet bisher nur mit quadratischen Filtermasken. Diese
	 * Methode liefert die Seitenl�nge der quadratischen Maske.
	 * 
	 * @see setFilterSize()
	 */
	inline int getFilterSize( ) const
	{
		return m_width;
	};
	
	
	
	/**
	 * Liefert die Filterbank zur�ck.
	 * 
	 * @return Liste der Filterkerne f�r die einzelnen Orientierungen
	 */
	const ImageSequence<float> & getFilterbank( )
	{
		if (m_create_filter) doCreateGaborFilter();
		return m_filterbank;
	};
	
	/**
	 * Liefert die Frequenzvektoren aller Orientierungen f�r die letzte durchgef�hrte Gabortransformation.
	 * 
	 * Liefert f�r jede Orientierung den Frequenzvektor, der sich aus Zentralfrequenz 
	 * des Gaborfilters und der Orientierung ergibt. Es wird ein Array (std::vector) 
	 * zur�ckgeliefert, in dem das i-te Element der Frequenzvektor der i-ten 
	 * Orientierung ist.
	 * 
	 * @return Liste der Frequenzvektoren
	 */
	 inline const std::vector<Vector2D> & getFrequencyVectors( ) const
	 {
	 	return m_frequency_vectors;
	 };
	
	

	/** F�hrt die Gaborfilterung mit der gesamten Gabor-Filterbank durch.
	 * 
	 * Das Eingabebild wird mit jeder in der Filterbank vorhandenen Orientierung
	 * des Gaborfilters gefiltert. Als Ergebnis erh�lt man eine Liste von 
	 * Ergebnisbildern. Jedes Bild stellt das Ergebnis f�r eine bestimmte 
	 * Orientierung dar.
	 * 
	 * @param image Eingabebild - Bild im Ortsraum (Input)
	 * @param filter_result Liste der Filterergebnisse f�r die verschiedenen Orientierungen (Ouput)
	 */
	void doGaborFiltering( const Image<Complex> &image, ImageSequence<Complex> &filter_result );

  private:	
	/** 
	 * Erzeugt die Gaborfilterbank entsprechend der eingestellten Parameter.
	 * 
	 * @todo Berechnung(Geschwindigkeit) �berarbeiten
	 * @todo Hinweis auf die letztlich berechnete Formel in die Doku aufnehmen
	 */
	void doCreateGaborFilter( );

};



} /* namespace GET */

#endif /* __IMAGE_H */
