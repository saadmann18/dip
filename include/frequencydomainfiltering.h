#ifndef __GET__FREQUENCYFILTERING_H
#define __GET__FREQUENCYFILTERING_H

#include "fdfiltering_basetemplate.h"


namespace GET
{



/** Schnelle Filterung im Frequenzsraum (verwendet float-Matrizen).
 * 
 * Diese Klasse stellt Methoden zur Filterung im Frequenzraum zur Verf�gung. 
 * Sie soll sp�ter au�erdem die Faltung im Ortsraum (implementiert durch eine
 * Multiplikation im Frequenzraum) anbieten.
 * 
 * Die Klasse verwendet im Frequenzraum Bilder vom Typ Image<Complex> und
 * Filtermasken vom Typ Image<float>
 * 
 * @author Holger T�ubig
 * @version VORL�UFIG FERTIG.
 * @note keine Quellen.
 * 
 * @todo nach Einf�hrung der Exceptions in GETGLOBAL: Exceptions erzeugen, wenn Eingabebild
 *       oder Filtermaske nicht gesetzt sind.
 */
class FastFrequencyDomainFiltering : public FrequencyDomainFilteringBaseTemplate<float> 
{
};


/** Filterung im Frequenzsraum.
 * 
 * Diese Klasse stellt Methoden zur Filterung im Frequenzraum zur Verf�gung. 
 * Sie soll sp�ter au�erdem die Faltung im Ortsraum (implementiert durch eine
 * Multiplikation im Frequenzraum) anbieten.
 * 
 * Die Klasse verwendet im Frequenzraum Bilder vom Typ Image<Complex> und
 * Filtermasken vom Typ Image<float>
 * 
 * @author Holger T�ubig
 * @version VORL�UFIG FERTIG.
 * @note keine Quellen.
 * 
 * @todo Faltung im Ortsraum inkl. Function-Padding implementieren
 * @todo nach Einf�hrung der Exceptions in GETGLOBAL: Exceptions erzeugen, wenn Eingabebild
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
	 * @param filter_mask Image-Objekt in dem die neue Filtermaske �bergeben wird (Ortsraum)
	 */
	void setSpatialMask( const Image<Complex> &filter_mask );

	/** Filterung im Ortsraum(Faltung) ausf�hren.
	 * 
	 * Die Filtermaske wird als Ortsfiltermaske �bergeben und zun�chst in den
	 * Frequenzraum transformiert. Das Ergebnis der danach durchgef�hrten 
	 * Filterung wird dann mittels inverser 
	 * Fourier-Transformation in den Ortsraum r�cktransformiert und dann 
	 * zur�ckgegeben. Dieses Ergebnis entspricht der Faltung der
	 * Ortsrepr�sentanten von Filtermaske und Eingabebild.
	 * 
	 * Es wird das vorher gesetzte Eingabebild mit der direkt �bergebenen Filtermaske
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
