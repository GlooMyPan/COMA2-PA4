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
 * besitzen, um einen Schlüsselwert zu liefern. Außerdem muss er
 * 
 *    T::operator == ( T const& ) const
 *
 * besitzen, um HashTabelle<T>::find() zu unterstützen.
 */

template < typename T >
class HashTabelle
{
/***  private Attribute  ***/

	// Array der Buckets
	vector< Liste<T> > _buckets ;
	const double _gamma = 0.5*(sqrt(5)-1); // der Kehrwert des goldenen Schnitts

/***  private Hilfsfunktionen  ***/

	// Hash-Funktion: berechne aus obj seinen _buckets[]-Index
	size_t _hash ( T const& obj ) const
	{
        double st = _gamma*size_t(obj);
        return floor(_buckets.size()*(st - floor(st)));
               // hash(k) = floor(m*((gamma*k) mod 1))
	}

public:
	// übernehme den Iterator-Typ von SortListe<T>
	typedef  typename Liste<T>::iterator  iterator ;

/***  Konstruktoren  ***/

	// Initialisierungskonstruktor mit Anzahl Buckets,
	// initialisiert leeres Objekt
	HashTabelle ( size_t nBuckets )
	: _buckets(nBuckets)
    {}

/***  get-Methoden  ***/

	// gib Anzahl Einträge im Objekt aus
	size_t size () const
	{
		size_t anzahl = 0 ;
		for ( Liste<T> const& bucket : _buckets )
			anzahl += bucket.size() ;
		return anzahl ;
	}

	// gebe ungültigen Iterator aus
	iterator end () const
	{
	    static Liste<T> _list;
	    return _list.end(); // ung¨¹ltige Iterator
	}

/***  set-Methoden  ***/

	// füge neuen Eintrag in das Objekt ein
	void insert ( T const& obj )
	{
        _buckets[_hash(obj)].push_back(obj); // f¨¹gt eine Kopie des ¨¹bergebenen obj in Bucket ein
	}

	// gebe den ersten Eintrag aus, der T::operator == obj 
	// ist oder end(), falls es keinen gibt
    iterator find ( T const& obj )
    {
        Liste<T>& bucket = _buckets[_hash(obj)];
        iterator i = bucket.find(obj); // sucht obj in bucket
        return i != bucket.end() ? i : end(); // geben i zur¨¹ck wenn obj gefunden hat, sonst ein ung¨¹ltige Iterator
    }

	// verkette alle Buckets zu einer Liste und gebe
	// sie zurück, das Objekt ist danach leer
	Liste<T> toList ()
	{
        Liste<T> ans;
        for (Liste<T> &bucket : _buckets)
            ans.splice(ans.begin(), bucket); // f¨¹gt alle Buckets in ans ein
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

#else	// zeige nur Größen der Buckets an

		ostr << "<" << tab.size() << ">[" ;
		for ( Liste<T> const& liste : tab._buckets )
			ostr << " " << liste.size() ;
		return ostr << " ]" << endl ;
#endif
	}

} ;  // class Hashtabelle<T>


#endif  // HASHTABELLE