#pragma once

#include <iostream>
#include <sstream>
#include <list>

namespace GET
{

	/* endl wird aus dem Namespace std in den Namespace GET �bernommen */
	using std::endl;
	/* flush wird aus dem Namespace std in den Namespace GET �bernommen */
	using std::flush;

	/** Klasse um innerhalb der GETLib standardisierte Ausgaben zu realisieren.
	 *
	 * Die Klasse erlaubt es einheitlich Ausgaben durchzuf�hren, egal wohin
	 * (Standardausgabe oder ein Textfenster) diese Ausgaben erfolgen sollen.
	 *
	 * Die Klasse ist nach dem Observer - Design Pattern implementiert. Beliebige
	 * Ausgabeorte k�nnen sich bei einem solchen Ausgabeobjekt anmelden,
	 *
	 * Die Klasse wird verwendet um die Standardausgaben innerhalb der GETLib zu
	 * realisieren. F�r Standardausgaben wird innerhalb der GETLib gout
	 * und f�r Standardfehlerausgaben gerr verwendet.
	 *
	 * @author Holger T�ubig
	 *
	 * @see gout oder gerr
	 */
	class StandardOutput
	{
	private:
		/** Zwischenspeicher f�r die Ausgaben */
		std::ostringstream m_out;
		/** true, wenn alle Ausgaben dieses Objektes auch auf der Standardausgabe
		 * (std::cout) ausgegeben werden sollen.
		 */
		bool m_use_cout;
		/** true, wenn alle Ausgaben dieses Objektes auch auf der Standardfehlerausgabe
		 * (std::cerr) ausgegeben werden sollen.
		 */
		bool m_use_cerr;

	public:
		/**
		 * Konstruktor.
		 *
		 * Erzeugt ein Ausgabeobjekt.
		 *
		 * @param use_cout Wert f�r m_use_cout
		 * @param use_cerr Wert f�r m_use_cerr
		 */
		StandardOutput(bool use_cout = true, bool use_cerr = false);

		/**
		 * 	Ausgabe an  std::cout ein-/ausschalten
		 */
		inline void setCout(bool use_cout) { m_use_cout = use_cout; }

		/**
		 * 	Ausgabe an  std::cerr ein-/ausschalten
		 */
		inline void setCerr(bool use_cerr) { m_use_cerr = use_cerr; }

		/**
		 * Liefert, ob die Ausgabe an std::cout aktiviert ist.
		 */
		inline bool getCout() { return m_use_cout; };

		/**
		 * Liefert, ob die Ausgabe an std::cerr aktiviert ist.
		 */
		inline bool getCerr() { return m_use_cerr; };

		/**
		 * Ueberladen des Ausgabe Operators << fuer verschiedene Ausgabetypen. Es
		 * sind alle die Ausgabem�glichkeiteb vorhanden, die auch std::cout zur
		 * Verf�gung stellt.
		 */
		template <typename TYP>
		StandardOutput &operator<<(TYP value);

		/**
		 * Ueberladen des Ausgabe Operators << fuer die Manipulatoren
		 */
		StandardOutput &operator<<(std::ostream &(*functionPointer)(std::ostream &));
		/**
		 * Ueberladen des Ausgabe Operators << fuer die Manipulatoren
		 */
		StandardOutput &operator<<(std::ios &(*functionPointer)(std::ios &));
		/**
		 * Ueberladen des Ausgabe Operators << fuer die Manipulatoren
		 */
		StandardOutput &operator<<(std::ios_base &(*functionPointer)(std::ios_base &));

		/* ********************************************************** */
		/* ******Observer Design-Pattern **************************** */
		/* ********************************************************** */
		/* ******mit Observer-Interface StandardOutput::Observer***** */
		/* ******und Subject StandardOutput************************** */
		/* ********************************************************** */

		/** Observer-Interface (Basisklasse f�r Ausgabeorte, die
		 * sich bei einem Objekt der Klasse StandardOutput anmelden
		 * wollen
		 */
		class Observer
		{
		public:
			virtual void update(std::string text) = 0;
			virtual ~Observer(){};
		};

	private:
		/** Subject-Interface des Observer - Design Pattern */
		std::list<Observer *> m_observer_list;

		/** Subject-Interface des Observer - Design Pattern.
		 *
		 * Alle angemeldeten Objekt werden angewiesen den �bergebenen
		 * Text auszugeben.
		 *
		 * @param text Text, der an allen angemeldeten Ausgabeorten ausgegeben werden soll
		 */
		inline void fireUpdate(std::string text)
		{
			std::list<Observer *>::iterator it_observer = m_observer_list.begin();
			while (it_observer != m_observer_list.end())
			{
				(*it_observer)->update(text);
				++it_observer;
			}
		};

	public:
		/** Subject-Interface des Observer - Design Pattern (Objekt anmelden).
		 *
		 * Mit dieser Methode kann StandardOutput ein zusaetzliches Ausgabeobjekt hinzugefuegt
		 * werden. Das Ausgabeobjekt mu� von StandardOutput::Observer abgeleitet sein.
		 * F�r Ausgabe ueber std::cout und std::cerr siehe auch setCout und setCerr;
		 */
		void attach(Observer *observer)
		{
			m_observer_list.push_back(observer);
		};
		/** Subject-Interface des Observer - Design Pattern (Objekt abmelden).
		 *
		 * Mit dieser Methode kann ein zusaetzliches Ausgabeobjekt wieder entfernt werden.
		 */
		void detach(Observer *observer)
		{
			m_observer_list.remove(observer);
		};
	};

	/**
	Ueberladen des Operators << fuer verschiedene Ausgabetypen
	*/
	template <typename TYP>
	StandardOutput &StandardOutput::operator<<(TYP value)
	{
		// cout und cerr nutzten, wenn dies eingeschaltet ist
		if (m_use_cout)
			std::cout << value;
		if (m_use_cerr)
			std::cerr << value;

		// alle eingetragenen zusaetzlichen Ausgabeobjekte informieren
		m_out << value;
		fireUpdate(m_out.str());
		m_out.str("");

		// fertig
		return *this;
	}

	/**
	 * Standardausgabeobjekt innerhalb der GETLib
	 */
	extern StandardOutput &gout;
	/**
	 * Standardfehlerausgabeobjekt innerhalb der GETLib
	 */
	extern StandardOutput &gerr;

	/**
	Funktion, um gout bei Initialisierung der Bibliothek einen Observer hinzuzufuegen
	*/
	void __attach_observer_to_gout(StandardOutput::Observer *observer, bool disable_cout = false);
	/**
	Funktion, um gerr bei Initialisierung der Bibliothek einen Observer hinzuzufuegen
	*/
	void __attach_observer_to_gerr(StandardOutput::Observer *observer, bool disable_cerr = false);

} /* namespace GET */
