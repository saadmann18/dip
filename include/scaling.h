#ifndef __GET__SCALING_H
#define __GET__SCALING_H

namespace GET
{

/**
 * Skalieren einzelner Werte aus einem originalen Wertebereich in den
 * skalierten Wertebereich
 * 
 * @author Holger Täubig
 * @version VORLÄUFIG FERTIG.
 * 
 * @todo Geschwindigkeitsoptimierung falls einer der Minimalwerte 0 ist.
 */
class Scaling
{
  private:
	float m_orig_minval; ///< untere Grenze des originalen Wertebereichs
	float m_orig_maxval; ///< obere Grenze des originalen Wertebereichs
	float m_scal_minval; ///< untere Grenze des skalierten Wertebereichs
	float m_scal_maxval; ///< obere Grenze des skalierten Wertebereichs
	
	/**
	 * Skalierungsfaktor zur Korrektur der Grösse der Wertebereiche bei Skalierung Original->Skaliert.
	 */
	float m_factor_orig2scal; 

	/**
	 * Skalierungsfaktor zur Korrektur der Grösse der Wertebereiche bei Rückskalierung Skaliert->Original.
	 */
	 float m_factor_scal2orig;
	
	/**
	 * Berechnet die Skalierungsfaktoren m_factor_orig2scal und m_factor_scal2orig neu.
	 */
	void doRecalculateFactors( );
	
	int m_discrete_trunc_orig; ///< maximaler Rückgabewert von Scaling::doScaleBackDiskreteWithTruncation()
	int m_discrete_trunc_scal; ///< maximaler Rückgabewert von Scaling::doScaleDiskreteWithTruncation()
	
  public:
	/**
	 * Konstruktor mit Festlegung des originalen und des skalierten Wertebereichs.
	 * 
	 * @param orig_minval untere Grenze des originalen Wertebereichs
	 * @param orig_maxval obere Grenze des originalen Wertebereichs
	 * @param scal_minval untere Grenze des skalierten Wertebereichs
	 * @param scal_maxval obere Grenze des skalierten Wertebereichs
	 */
	Scaling(float orig_minval, float orig_maxval, float scal_minval, float scal_maxval );
	
	/**
	 * Destruktor.
	 */
	~Scaling();
	
	/**
	 * Setzt den originalen Wertebereich.
	 * 
	 * @param orig_minval untere Grenze des originalen Wertebereichs
	 * @param orig_maxval obere Grenze des originalen Wertebereichs
	 */
	void setOriginalRange( float orig_minval, float orig_maxval );
	
	/**
	 * Setzt den skalierten Wertebereich.
	 * 
	 * @param scal_minval untere Grenze des skalierten Wertebereichs
	 * @param scal_maxval obere Grenze des skalierten Wertebereichs
	 */
	void setScaledRange( float scal_minval, float scal_maxval );
	
	/**
	 * Setzt den maximalen diskreten Wert, den 
	 * Scaling::doScaleDiskreteWithTruncation() liefert. Alle 
	 * grösseren Werte werden auf diesen Wert reduziert.
	 * 
	 * @see Scaling::doScaleDiskreteWithTruncation()
	 * 
	 * @param maximal von Scaling::doScaleDiskreteWithTruncation() zurückzuliefernder Wert
	 */
	void setDiskreteTruncationScaled( int max_diskrete_val )
	{
		m_discrete_trunc_scal = max_diskrete_val;
	};
	
	/**
	 * Setzt den maximalen diskreten Wert, den Scaling::doScaleBackDiskreteWithTruncation() liefert. 
	 * Alle grösseren Werte werden auf diesen Wert reduziert.
	 * 
	 * @see Scaling::doScaleDiskreteWithTruncation()
	 * 
	 * @param max_diskrete_val maximal von Scaling::doScaleBackDiskreteWithTruncation() zurückzuliefernder Wert
	 */
	void setDiskreteTruncationOriginal( int max_diskrete_val )
	{
		m_discrete_trunc_orig = max_diskrete_val;
	};
		
	
	
	/**
	 * Skaliert einen Wert aus dem Originalen Wertebereich in den skalierten 
	 * Wertebereich.
	 * 
	 * @param orig_value Wert aus dem originalen Wertebereich
	 * @return entsprechender skalierter Wert aus dem skalierten Wertebereich
	 */
	float doScale( float orig_value );
	
	/** 
	 * Skaliert einen Wert aus dem skalierten Wertebereich in den originalen
	 * Wertebereich zurück.
	 * 
	 * @param scal_value Wert aus dem skalierten Wertebereich 
	 * @return entsprechender zurückskalierter Wert aus dem originalen Wertebereich
	 */
	float doScaleBack( float scal_value );


	
	/**
	 * Skaliert einen Wert aus dem Originalen Wertebereich in den skalierten 
	 * Wertebereich und diskretisiert das Ergebnis.
	 * 
	 * @param orig_value Wert aus dem originalen Wertebereich
	 * @return entsprechender skalierter und danach diskretisierter Wert aus dem skalierten Wertebereich
	 */
	int doScaleDiskrete( float original_value );

	/** 
	 * Skaliert einen Wert aus dem skalierten Wertebereich in den originalen
	 * Wertebereich zurück und diskretisiert das Ergebnis.
	 * 
	 * @param scal_value Wert aus dem skalierten Wertebereich 
	 * @return entsprechender zurückskalierter und danach diskretisierter Wert aus dem originalen Wertebereich
	 */
	int doScaleBackDiskrete( float scaled_value );


	
	/**
	 * Skaliert einen Wert aus dem Originalen Wertebereich in den skalierten 
	 * Wertebereich und diskretisiert das Ergebnis. 
	 * 
	 * Ausserdem wird das diskretisierte Ergebnis bei einem vorgegebenen Wert 
	 * abgeschnitten, d.h. alle Ergebnisse die grösser als dieser Wert sind, 
	 * werden auf diesen Wert reduziert. Dies kann z.B. dazu
	 * verwendet werden, bei Diskretisierung des Bereiches [0,N] den ganzzahligen
	 * Wert N mit in den Kontainer N-1 einzuorden (ihn also dem Bereich [N-1,N)
	 * zu zu weisen)
	 * 
	 * @see Scaling::setDiskreteTruncationScaled()
	 * 
	 * @param orig_value Wert aus dem originalen Wertebereich
	 * @return entsprechender skalierter und danach diskretisierter Wert aus dem skalierten Wertebereich
	 */
	int doScaleDiskreteWithTruncation( float original_value );

	/** 
	 * Skaliert einen Wert aus dem skalierten Wertebereich in den originalen
	 * Wertebereich zurück und diskretisiert das Ergebnis.
	 * 
	 * Ausserdem wird das diskretisierte Ergebnis bei einem vorgegebenen Wert 
	 * abgeschnitten, d.h. alle Ergebnisse die grösser als dieser Wert sind, 
	 * werden auf diesen Wert reduziert. Dies kann z.B. dazu
	 * verwendet werden, bei Diskretisierung des Bereiches [0,N] den ganzzahligen
	 * Wert N mit in den Kontainer N-1 einzuorden (ihn also dem Bereich [N-1,N)
	 * zu zu weisen)
	 * 
	 * @see Scaling::setDiskreteTruncationOriginal()
	 * 
	 * @param scal_value Wert aus dem skalierten Wertebereich 
	 * @return entsprechender zurückskalierter und danach diskretisierter Wert aus dem originalen Wertebereich
	 */
	int doScaleBackDiskreteWithTruncation( float scaled_value );
};

}

#endif //_SKALING_H_
