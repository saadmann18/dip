#ifndef __GET__FREQUENCYDOMAINFILTERING_BASETEMPLATE_H
#define __GET__FREQUENCYDOMAINFILTERING_BASETEMPLATE_H

#include "image.h"
#include "fft.h"

namespace GET
{

	/**
	 * Gemeinsame Basisklasse f�r FrequencyDomainFiltering und FastFrequencyDomainFiltering.
	 *
	 * Dies ist die Basisklasse f�r die beiden Klassen zur Filterung im Frequenzsraum.
	 * Es ist nicht sinnvoll, von dieser Klasse Instanzen zu erstellen. Sie dient
	 * lediglich dazu den gemeinsamen Kern der beiden Klassen einheitlich an
	 * genau einer Stelle zu implementieren.
	 *
	 * Die Klassen zur Filterung im Frequenzraum habe folgende Eigenschaften:
	 *| FrequencyDomainFiltering | Dies ist die allgemeinere Klasse.
	 * Sie arbeiten mit komplexwertigen Masken und ist daher etwas langsamer.
	 * Daf�r bietet sie die M�glichkeit, ebenfalls Ortsraum-Filter im Frequenzraum zu
	 * berechnen (bessere Geschwindigkeit).
	 *| FastFrequencyDomainFiltering | Diese Klasse verwendet lediglich float-wertige
	 * Masken. Dies reicht aber f�r die Standardfilter im Frequenzraum aus und ben�tigt
	 * weniger Rechenzeit.
	 *
	 * @author Holger T�ubig
	 * @version VORL�UFIG FERTIG.
	 * @note keine Quellen.
	 *
	 * @todo Namensgebung der doConvolution-Methoden an die von
	 * doFilteringWithMaskGiveSpatialResult() anpassen, da letztere die Bedeutung einer
	 * Methode st�rker in den Vordergrund stellen
	 * @todo Geschwindigkeit der float-Instanz verbessern in dem FFT und DFT
	 * spezielle float->Complex Methoden hinzugef�gt werden
	 */
	template <typename MASKTYPE>
	class FrequencyDomainFilteringBaseTemplate
	{
	protected:
		/** Filtermaske */
		Image<MASKTYPE> m_filter_mask;

		/** true, wenn eine verwendbare Filtermaske vorhanden ist.*/
		bool m_filter_mask_available;

		/** Zu filterndes Bild.
		 *
		 * Dieser Zwischenspeicher des zu filternden Bildes wird genutzt, falls das Bild
		 * vor dem Aufruf von doFrequencyFiltering() getrennt gestzt wird. Diese Vorgehensweise ist
		 * n�tzlich, wenn ein Bild mehrfach mit unterschiedlichen Filtern gefiltert werden soll.
		 */
		Image<Complex> m_input_image;
		/** true, wenn ein verwendbares Eingabebild vorhanden ist. */
		bool m_input_image_available;

		/**
		 * Algorithmus zur Fourier-Transformation (FFT).
		 */
		FFT a_fft;
		/**
		 * Zwischenspeicher (haupts�chlich f�r das Filterergebnis im Frequenzraum).
		 */
		Image<Complex> m_tmp1;
		/**
		 * Zwischenspeicher (haupts�chlich f�r die Fourier-Transformierte des Input von doConvolutionWithMask() und doConvolutionWithImage()).
		 */
		Image<Complex> m_tmp2;

	public:
		/** Standardkonstruktor. */
		FrequencyDomainFilteringBaseTemplate();

		/** Setzt eine neue Filtermaske.
		 *
		 * @param filter_mask Image-Objekt in dem die neue Filtermaske �bergeben wird (Frequenzraum)
		 */
		void setMask(const Image<MASKTYPE> &filter_mask);

		/** Liefert die derzeitige Filtermaske.
		 *
		 * @param filter_mask Image-Objekt in dem die akuell verwendete Filtermaske zur�ckgeliefert wird (Frequenzraum)
		 *
		 * @todo konstante Referenz auf Maske zur�ckliefern spart Kopieraufwand
		 */
		void getMask(Image<MASKTYPE> &filter_mask);

		/** Setzt das zu filternde Eingabebild.
		 *
		 * @param image zu filterndes Bild (Frequenzraum)
		 */
		void setImage(const Image<Complex> &image);

		/** Filterung ausf�hren.
		 *
		 * Es wird das vorher gesetzte Eingabebild mit der vorher gesetzten Filtermaske
		 * gefiltert.
		 *
		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Frequenzraum)
		 *
		 * @see setMask()
		 * @see setImage()
		 */
		inline void doFiltering(Image<Complex> &result);

		/** Filterung(Faltung) ausf�hren.
		 *
		 * Es wird das vorher gesetzte Eingabebild mit der direkt �bergebenen Filtermaske
		 * gefiltert.
		 *
		 * @param filter_mask Filtermaske, mit der gefaltet werden soll (Frequenzraum)
		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Frequenzraum)
		 *
		 * @see setImage()
		 */
		inline void doFilteringWithMask(const Image<MASKTYPE> &filter_mask, Image<Complex> &result);

		/** Filterung(Faltung) ausf�hren.
		 *
		 * Es wird das direkt �bergebene Eingabebild mit der vorher gesetzten Filtermaske
		 * gefiltert.
		 *
		 * @param input_image Eingabebild, das gefiltert werden soll (Frequenzraum)
		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Frequenzraum)
		 *
		 * @see setMask()
		 */
		inline void doFilteringWithImage(const Image<Complex> &input_image, Image<Complex> &result);

		/** Erzeugt und setzt die Maske eines idealen Tiefpass-Filters.
		 *
		 * @note Quelle: Berechnung entsprechend Formel 4.3-4 aus
		 *               Gonzalez, Wintz - Digital Image Processing. 2nd edt. 1987. Seite 165.
		 *
		 * @param d0 Grenzfrequenz des idealen Tiefpass
		 * @param width Breite der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildbreite
		 *              des zu filternden Bildes �berein stimmen)
		 * @param height H�he der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildh�he
		 *               des zu filternden Bildes �berein stimmen)
		 *
		 * @see setMask()
		 */
		void setIdealLowpassMask(float d0, int width, int height);

		/** Erzeugt und setzt die Maske eines idealen Hochpass-Filters.
		 *
		 * @note Quelle: Berechnung entsprechend Formel 4.4-12 aus
		 *               Gonzalez, Wintz - Digital Image Processing. 2nd edt. 1987. Seite 181.
		 *
		 * @param d0 Grenzfrequenz des idealen Hochpass
		 * @param width Breite der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildbreite
		 *              des zu filternden Bildes �berein stimmen)
		 * @param height H�he der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildh�he
		 *               des zu filternden Bildes �berein stimmen)
		 *
		 * @see setMask()
		 */
		void setIdealHighpassMask(float d0, int width, int height);

		/** Erzeugt und setzt die Maske eines Butterworth-Tiefpass-Filters.
		 *
		 * @note Quelle: Berechnung entsprechend Formel 4.3-6 aus
		 *               Gonzalez, Wintz - Digital Image Processing. 2nd edt. 1987. Seite 170.
		 *
		 * @param d0 Grenzfrequenz des Butterworth-Tiefpass
		 * @param n  Ordnung des zu erzeugenden Butterworth-Filters
		 * @param width Breite der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildbreite
		 *              des zu filternden Bildes �berein stimmen)
		 * @param height H�he der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildh�he
		 *               des zu filternden Bildes �berein stimmen)
		 *
		 * @see setMask()
		 */
		void setButterworthLowpassMask(float d0, int n, int width, int height);

		/** Erzeugt und setzt die Maske eines Butterworth-Hochpass-Filters.
		 *
		 * @note Quelle: Berechnung entsprechend Formel 4.4-13 aus
		 *               Gonzalez, Wintz - Digital Image Processing. 2nd edt. 1987. Seite 181.
		 *
		 * @param d0 Grenzfrequenz des Butterworth-Hochpass
		 * @param n  Ordnung des zu erzeugenden Butterworth-Filters
		 * @param width Breite der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildbreite
		 *              des zu filternden Bildes �berein stimmen)
		 * @param height H�he der zu erzeugenden Filtermaske (Muss sp�ter mit der Bildh�he
		 *               des zu filternden Bildes �berein stimmen)
		 *
		 * @see setMask()
		 */
		void setButterworthHighpassMask(float d0, int n, int width, int height);

		/** Liefert die derzeitige Filtermaske in ihrer Ortrepr�sentation.
		 * Die aktuelle Filtermaske wird mittels inverser Fourier-Transformation
		 * in den Ortsraum zur�ck transformiert und dann an den Aufrufer zur�ckgeliefert.
		 *
		 * Die zur�ckgelieferte Ortsrepr�sentation der Filtermaske hat unabh�ngig vom Typ der Filtermaske
		 * den Typ Image<Complex>, da sie das Ergebnis einer inversen Fourier-Transformation ist.
		 *
		 * @param filter_mask Image-Objekt in dem die akuell verwendete Filtermaske zur�ckgeliefert wird  (Ortsraum)
		 *
		 * @todo konstante Referenz auf Maske zur�ckliefern spart Kopieraufwand
		 */
		void getSpatialMask(Image<Complex> &filter_mask);

		/** Setzt das zu filternde Eingabebild aus dem Ortsraum.
		 *
		 * Das Bild wird zun�chst mittels Fourier-Transformation in den Frequenzraum
		 * transformiert und steht, danach wie mit setImage() gespeichert,
		 * als Eingabebild f�r die Filterung zur Verf�gung.
		 *
		 * @param image zu filterndes Bild (Ortsraum)
		 */
		void setSpatialImage(const Image<Complex> &image);

		/** Filterung im Ortsraum(Faltung) ausf�hren.
		 *
		 * Das bedeutet, dass das Ergebnis der Filterung mittels inverser
		 * Fourier-Transformation in den Ortsraum r�cktransformiert und dann
		 * zur�ckgegeben wird. Dieses Ergebnis entspricht der Faltung der
		 * Ortsrepr�sentanten von Filtermaske und Eingabebild.
		 *
		 * Es wird das vorher gesetzte Eingabebild mit der vorher gesetzten Filtermaske
		 * gefaltet.

		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Ortsraum)
		 *
		 * @see setMask()
		 * @see setImage()
		 */
		void doConvolution(Image<Complex> &result);

		/** Filterung im Ortsraum(Faltung) ausf�hren.
		 *
		 * Das Eingabebild wird wird im Ortsraum �bergeben und zun�chst in den
		 * Frequenzraum transformiert. Das Ergebnis der danach durchgef�hrten
		 * Filterung wird dann mittels inverser
		 * Fourier-Transformation in den Ortsraum r�cktransformiert und dann
		 * zur�ckgegeben. Dieses Ergebnis entspricht der Faltung der
		 * Ortsrepr�sentanten von Filtermaske und Eingabebild.
		 *
		 * Es wird das direkt �bergebene Eingabebild(Bild im Ortsraum) mit der
		 * vorher gesetzten Filtermaske gefiltert.
		 *
		 * @param input_image Eingabebild, das gefiltert werden soll (Ortsraum)
		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Ortsraum)
		 *
		 * @see setMask()
		 */
		void doConvolutionWithImage(const Image<Complex> &input_image, Image<Complex> &result);

		/** Filterung(Faltung) ausf�hren.
		 *
		 * Es wird das vorher gesetzte Eingabebild mit der direkt �bergebenen Filtermaske
		 * gefiltert.
		 *
		 * @param filter_mask Filtermaske, mit der gefaltet werden soll (Frequenzraum)
		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert werden soll (Frequenzraum)
		 *
		 * @see setImage()
		 */
		void doFilteringWithMaskGiveSpatialResult(const Image<MASKTYPE> &filter_mask, Image<Complex> &result);

	protected:
		/** Implementation der Filterung.
		 *
		 * Alle vom Nutzer ausf�hrbaren Aufrufe nutzen diese Methode, um das Ergebnis
		 * der Faltung von Filtermaske und Eingabebild zu berechnen.
		 *
		 * @param input_image Eingabebild, das gerade gefiltert wird (Frequenzraum)
		 * @param filter_mask Filtermaske, mit der gefaltet wird (Frequenzraum)
		 * @param result Image-Objekt, in dem das Ergebnis der Faltung gespeichert wird (Frequenzraum)
		 *
		 * @see doFiltering(), doFilteringWithMask() bzw. doFilteringWithImage()
		 * @see doBoundaryCalculations()
		 *
		 * @todo Multiplikation und Zuweisung in der Schleife durch eine Operation ersetzen (Geschwindigkeit)
		 */
		void doFiltering(const Image<Complex> &input_image, const Image<MASKTYPE> &filter_mask, Image<Complex> &result);
	};

	/* *********************************************************************************** */
	/* Faltung mit vorher gesetztem Eingabebild und vorher gesetzter Filtermaske ausf�hren. */
	template <typename MASKTYPE>
	inline void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doFiltering(Image<Complex> &result)
	/* *********************************************************************************** */
	{
		if (m_filter_mask_available && m_input_image_available)
			doFiltering(m_input_image, m_filter_mask, result);
		else
		{
			gerr << "Fehler in FrequencyFiltering::doFiltering( Image<Complex> &result )" << endl;
			gerr << "Filtermaske oder Eingabebild existiert nicht." << endl;
		};
	}

	/* *********************************************************************************** */
	/* Faltung mit Filtermaske ausf�hren. */
	template <typename MASKTYPE>
	inline void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doFilteringWithMask(const Image<MASKTYPE> &filter_mask, Image<Complex> &result)
	/* *********************************************************************************** */
	{
		if (m_input_image_available)
			doFiltering(m_input_image, filter_mask, result);
		else
		{
			gerr << "Fehler in FrequencyFiltering::doFilteringWithMask( const Image<Complex> &filter_mask, Image<Complex> &result )" << endl;
			gerr << "Eingabebild existiert nicht." << endl;
		};
	}

	/* *********************************************************************************** */
	/* Faltung mit Eingabebild ausf�hren. */
	template <typename MASKTYPE>
	inline void FrequencyDomainFilteringBaseTemplate<MASKTYPE>::doFilteringWithImage(const Image<Complex> &input_image, Image<Complex> &result)
	/* *********************************************************************************** */
	{
		if (m_filter_mask_available)
			doFiltering(input_image, m_filter_mask, result);
		else
		{
			gerr << "Fehler in FrequencyFiltering::doFilteringWithImage( const Image<Complex> &input_image, Image<Complex> &result )" << endl;
			gerr << "Filtermaske existiert nicht." << endl;
		};
	}

}

#endif /*__GET__FREQUENCYDOMAINFILTERING_BASETEMPLATE_H*/
