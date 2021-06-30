#ifndef HASHTABELLE
#define HASHTABELLE

#include <iostream>
#include <vector>
#include <cmath> // sqrt()
#include "Liste.h"
using namespace std ;


/**
 * Generische Hash-Tabelle mit Liste<T>-Objekten als Buckets.
 * Der Eintragstyp T muss die Methode
 *
 *    T::operator size_t () const
 *
 * besitzen, um einen Schl�sselwert zu liefern. Au�erdem muss er
 * 
 *    T::operator == ( T const& ) const
 *
 * besitzen, um HashTabelle<T>::find() zu unterst�tzen.
 */

template < typename T >
class HashTabelle
{
/***  private Attribute  ***/

	// Array der Buckets
	vector< Liste<T> > _buckets ;

/***  private Hilfsfunktionen  ***/

	// Hash-Funktion: berechne aus obj seinen _buckets[]-Index
	size_t _hash ( T const& obj ) const
	{
        size_t st = size_t(obj);
        double gamma = 0.5*(sqrt(5)-1); // der Kehrwert des goldenen Schnitts
        return size_t(floor(_buckets.size()*(gamma*st - size_t(gamma*st))));
               // hash(k) = floor(m*((gamma*k) mod 1))
	}

public:
	// �bernehme den Iterator-Typ von SortListe<T>
	typedef  typename Liste<T>::iterator  iterator ;

/***  Konstruktoren  ***/

	// Initialisierungskonstruktor mit Anzahl Buckets,
	// initialisiert leeres Objekt
	HashTabelle ( size_t nBuckets )
    {
	    _buckets.resize(nBuckets);
    }

/***  get-Methoden  ***/

	// gib Anzahl Eintr�ge im Objekt aus
	size_t size () const
	{
		size_t anzahl = 0 ;
		for ( Liste<T> const& bucket : _buckets )
			anzahl += bucket.size() ;
		return anzahl ;
	}


	// gebe ung�ltigen Iterator aus
	iterator end () const
	{
	    static Liste<T> _list;
	    return _list.end(); // ung��ltige Iterator
	}

/***  set-Methoden  ***/

	// f�ge neuen Eintrag in das Objekt ein
	void insert ( T const& obj )
	{
        _buckets[_hash(obj)].push_back(obj); // f��gt eine Kopie des ��bergebenen obj in Bucket ein
	}

	// gebe den ersten Eintrag aus, der T::operator == obj 
	// ist oder end(), falls es keinen gibt

/***  get-Methoden  ***/
    iterator find ( T const& obj )
    {
        Liste<T>& bucket = _buckets[_hash(obj)];
        iterator i = bucket.find(obj); // sucht obj in bucket
        return i != bucket.end() ? i : end(); // geben i zur��ck wenn obj gefunden hat, sonst ein ung��ltige Iterator
    }

	// verkette alle Buckets zu einer Liste und gebe
	// sie zur�ck, das Objekt ist danach leer

	Liste<T> toList ()
	{
        Liste<T> ans;
        for (Liste<T> &bucket : _buckets)
            ans.splice(ans.begin(), bucket); // f��gt alle Buckets in ans ein
        return ans;
	}

/***  Ausgabe auf ostream  ***/

	friend
	ostream& operator << ( ostream& ostr, HashTabelle const& tab )
	{
#if 0	// zeige Inhalte der Buckets an

		ostr << "    <" << tab.size() << ">" << endl ;
		for ( size_t i = 0 ;  i < tab._buckets.size() ;  ++i )
			ostr << "[" << i << "] " << tab._buckets[ i ] << endl ;
		return ostr ;

#else	// zeige nur Gr��en der Buckets an

		ostr << "<" << tab.size() << ">[" ;
		for ( Liste<T> const& liste : tab._buckets )
			ostr << " " << liste.size() ;
		return ostr << " ]" << endl ;
#endif
	}

} ;  // class Hashtabelle<T>


#endif  // HASHTABELLE