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
 * Bildgröße(Filtermaskengröße), Anzahl der Orientierungen und Zentralfrequenz
 * parametrisiert werden kann. \n
 * Mittels doGaborFiltering() kann das Ergebnis der Gaborfilterung (Liste mit
 * Filterergebnissen der einzelnen Orientierungen) bestimmt werden.
 * 
 * Diese Klasse arbeitet nur mit quadratischen Filtermasken (siehe m_width)
 * 
 * @author Holger Täubig
 * @version VORLÄUFIG FERTIG.
 * @note Erstimplementation von Zaheer Aziz übernommen und umgeschrieben
 * 
 * @todo Zusätzliche Methode einführen, die auf Image<float> arbeitet und dafür
 * optimiert wurde (hauptsächlich Implementation dieser Methode für aufgerufene
 * FilterKlasse).
 */
class GaborFilter
{
  private:
	/** Anzahl der Orientierungen der Gabor-Filterbank */
	int m_orientations;

	/** Filtergröße (Breite,Höhe).
	 * 
	 * Breite und Höhe des Gaborfilters. Diese Klasse arbeitet nur mit
	 * quadratischen Filtermasken. Dies bedeutet gleichzeitig, dass auch 
	 * die zu filternden Bilder eine Größe von m_width*m_width besitzen müssen.
	 */
	int m_width;               

	/** Zentralfrequenz der Gaborfilterbank */
	float m_k0;
	
	/** Überlappungsgrad der einzelnen Orientierungen */
	float m_overlapping;

	/**
	 * Neuberechnung der Filterbank.
	 *  
	 * Dieses Flag zeigt an (wenn true), dass die Filterbank vor der 
	 * nächsten Benutzung neuberechnet werden muss.
	 */
	bool m_create_filter; 

	/** Filterbank.
	 * 
	 * Hier sind die Filtermasken für die einzelnen Orientierungen gespeichert.
	 */
	ImageSequence<float> m_filterbank;                                       
	
	/**
	 * Algorithmus zur Filterung im Frequenzraum.
	 */
	FastFrequencyDomainFiltering a_filtering;



	/**
	 * Speichert die Frequenzvektoren aller Orientierungen für die letzte durchgeführte Grabortansformation.
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
	 * #Dies kann eine möglicherweise erhebliche Rechenzeit in Anspruch nehmen.#
	 * 
	 * @param filter_width Breite der Gaborfiltermaske (gleichzeitig auch Höhe der Filtermaske)
	 * @param orientations Anzahl der Orientierungen
	 * @param centroid_frequency Zentralfrequenz der Gaborfilterbank
	 * @param overlapping Überlappungsgrad der einzelnen Orientierungen
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
	 * möglicherweise erhebliche Rechenzeit in Anspruch nehmen.#
	 * 
	 * @param filter_width Breite der Gaborfiltermaske (gleichzeitig auch Höhe der Filtermaske)
	 * @param orientations Anzahl der Orientierungen
	 * @param centroid_frequency Zentralfrequenz der Gaborfilterbank
	 * @param overlapping Überlappungsgrad der einzelnen Orientierungen
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
	 * Setzt Breite und Höhe der Gaborfiltermasken.
	 * 
	 * Diese Klasse arbeitet nur mit quadratischen Filtermasken. 
	 * Die übergeben Seitenlänge wird deshalb als Höhe und als Breite 
	 * der Filtermaske verwendet.
	 * 
	 * Dies bedeutet gleichzeitig, dass auch 
	 * die zu filternden Bilder eine Größe von width*width besitzen müssen.
	 * 
	 * @param width Breite der Gaborfiltermaske (gleichzeitig auch Höhe der Filtermaske)
	 */
	void setFilterSize(  int width );
	
	/**
	 * Setzt die Zentralfrequenz und den Überlappungsgrad der einzelnen Orientierungen für die Gaborfilterbank.
	 * 
	 * @param k0 Zentralfrequenz der Gaborfilterbank
	 * @param overlapping Überlappungsgrad der einzelnen Orientierungen
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
	 * Liefert die Filterbreite/-höhe.
	 * 
	 * Der Gaborfilter arbeitet bisher nur mit quadratischen Filtermasken. Diese
	 * Methode liefert die Seitenlänge der quadratischen Maske.
	 * 
	 * @see setFilterSize()
	 */
	inline int getFilterSize( ) const
	{
		return m_width;
	};
	
	
	
	/**
	 * Liefert die Filterbank zurück.
	 * 
	 * @return Liste der Filterkerne für die einzelnen Orientierungen
	 */
	const ImageSequence<float> & getFilterbank( )
	{
		if (m_create_filter) doCreateGaborFilter();
		return m_filterbank;
	};
	
	/**
	 * Liefert die Frequenzvektoren aller Orientierungen für die letzte durchgeführte Gabortransformation.
	 * 
	 * Liefert für jede Orientierung den Frequenzvektor, der sich aus Zentralfrequenz 
	 * des Gaborfilters und der Orientierung ergibt. Es wird ein Array (std::vector) 
	 * zurückgeliefert, in dem das i-te Element der Frequenzvektor der i-ten 
	 * Orientierung ist.
	 * 
	 * @return Liste der Frequenzvektoren
	 */
	 inline const std::vector<Vector2D> & getFrequencyVectors( ) const
	 {
	 	return m_frequency_vectors;
	 };
	
	

	/** Führt die Gaborfilterung mit der gesamten Gabor-Filterbank durch.
	 * 
	 * Das Eingabebild wird mit jeder in der Filterbank vorhandenen Orientierung
	 * des Gaborfilters gefiltert. Als Ergebnis erhält man eine Liste von 
	 * Ergebnisbildern. Jedes Bild stellt das Ergebnis für eine bestimmte 
	 * Orientierung dar.
	 * 
	 * @param image Eingabebild - Bild im Ortsraum (Input)
	 * @param filter_result Liste der Filterergebnisse für die verschiedenen Orientierungen (Ouput)
	 */
	void doGaborFiltering( const Image<Complex> &image, ImageSequence<Complex> &filter_result );

  private:	
	/** 
	 * Erzeugt die Gaborfilterbank entsprechend der eingestellten Parameter.
	 * 
	 * @todo Berechnung(Geschwindigkeit) überarbeiten
	 * @todo Hinweis auf die letztlich berechnete Formel in die Doku aufnehmen
	 */
	void doCreateGaborFilter( );

};



} /* namespace GET */

#endif /* __IMAGE_H */
