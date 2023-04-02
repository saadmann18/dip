#ifndef __GET__FREQUENCYFILTERING_H
#define __GET__FREQUENCYFILTERING_H

#include "fdfiltering_basetemplate.h"


namespace GET
{



/** Schnelle Filterung im Frequenzsraum (verwendet float-Matrizen).
 * 
 * Diese Klasse stellt Methoden zur Filterung im Frequenzraum zur Verfügung. 
 * Sie soll später außerdem die Faltung im Ortsraum (implementiert durch eine
 * Multiplikation im Frequenzraum) anbieten.
 * 
 * Die Klasse verwendet im Frequenzraum Bilder vom Typ Image<Complex> und
 * Filtermasken vom Typ Image<float>
 * 
 * @author Holger Täubig
 * @version VORLÄUFIG FERTIG.
 * @note keine Quellen.
 * 
 * @todo nach Einführung der Exceptions in GETGLOBAL: Exceptions erzeugen, wenn Eingabebild
 *       oder Filtermaske nicht gesetzt sind.
 */
class FastFrequencyDomainFiltering : public FrequencyDomainFilteringBaseTemplate<float> 
{
};


/** Filterung im Frequenzsraum.
 * 
 * Diese Klasse stellt Methoden zur Filterung im Frequenzraum zur Verfügung. 
 * Sie soll später außerdem die Faltung im Ortsraum (implementiert durch eine
 * Multiplikation im Frequenzraum) anbieten.
 * 
 * Die Klasse verwendet im Frequenzraum Bilder vom Typ Image<Complex> und
 * Filtermasken vom Typ Image<float>
 * 
 * @author Holger Täubig
 * @version VORLÄUFIG FERTIG.
 * @note keine Quellen.
 * 
 * @todo Faltung im Ortsraum inkl. Function-Padding implementieren
 * @todo nach Einführung der Exceptions in GETGLOBAL: Exceptions erzeugen, wenn Eingabebild
 *       oder Filtermaske nicht gesetzt sind.
 */
class FrequencyDomainFiltering : public FrequencyDomainFilteringBaseTemplate<Complex>
{
  public:
	
	/** Setzt eine neue Orts-Filtermaske. 
	 * 
	 * Die Filtermaske wird mittels Fopurier-Transformation in den
	 * Frequenzraum transformiert und dann wie mit setMask() gespeichert.
	 * 
	 * @param filter_mask Image-Objekt in dem die neue Filtermaske übergeben wird (Ortsraum)
	 */
	void setSpatialMask( const Image<Complex> &filter_mask );

	/** Filterung im Ortsraum(Faltung) ausführen.
	 * 
	 * Die Filtermaske wird als Ortsfiltermaske übergeben und zunächst in den
	 * Frequenzraum transformiert. Das Ergebnis der danach durchgeführten 
	 * Filterung wird dann mittels inverser 
	 * Fourier-Transformation in den Ortsraum rücktransformiert und dann 
	 * zurückgegeben. Dieses Ergebnis entspricht der Faltung der
	 * Ortsrepräsentanten von Filtermaske und Eingabebild.
	 * 
	 * Es wird das vorher gesetzte Eingabebild mit der direkt übergebenen Filtermaske
	 * (Ortsfiltermaske) gefiltert.
	 * 
	 * @param filter_mask Filtermaske, mit der gefaltet werden soll (Ortsraum)
	 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Ortsraum)
	 * 
	 * @see setImage()
	 */
	void doConvolutionWithMask( const Image<Complex> &filter_mask, Image<Complex> &result );
};



}

#endif /*__GET__FREQUENCYFILTERING_H*/
