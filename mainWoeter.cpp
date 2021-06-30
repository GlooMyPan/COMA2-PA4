#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Liste.h"
#include "Zaehler.h"
#include "HashTabelle.h"
#include "Stoppuhr.h"

using namespace std ;

/***
 * Zeit Einlesen:      0.214 s
 * Zeit MergeSort:     0.007 s
 */
int main ( int narg, char* argv[] )
try
{
	// gebe Usage aus
	if ( narg < 2 )
	{
		cout << "Usage: " << argv[ 0 ] << "  dateiName  [anzahl]" << endl ;
		cout << "       dateiName: Name einer ASCII-Datei"		  << endl ;
		cout << "       anzahl   : (optional) natuerliche Zahl"	  << endl ;
		cout << "Zaehlt die in der Datei auftretenden Woerter"	  << endl ;
		cout << "und gibt sie nach absteigender Haeufigkeit aus." << endl ;
		cout << "Wenn anzahl gegeben wird, werden hoechstens"     << endl ;
		cout << "soviele Woerter ausgegeben, sonst alle."		  << endl ;

		return 0 ;
	}

/***  lese Parameter  ***/

	char*    dateiName = argv[ 1 ] ;
	size_t   anzahl    = ( narg >= 3 ? atoi( argv[ 2 ] ) : UINT_MAX ) ;
    size_t   nBuckets  = ( narg >= 3 ? atoi( argv[ 2 ] ) : UINT_MAX ) ; // get size of buckets
/***  �ffne Datei  ***/

	ifstream datei( dateiName ) ;

	if ( ! datei )
	{
		cerr << "Datei " << dateiName << " kann nicht geoeffnet werden!" << endl ;
		return -1 ;		// melde Fehlerzustand
	}

/***  bearbeite W�rter aus der Datei  ***/

	char const	   SATZZEICHEN[] = ".,:;!?\"\'-" ;
    HashTabelle<Zaehler> woerter(nBuckets);
	string		   wort ;
	Stoppuhr	   uhr ;

	while ( datei >> wort )
	{
		// l�sche alle Satzzeichen
		for ( size_t pos  = wort.find_first_of( SATZZEICHEN ) ;
					 pos != string::npos ;
					 pos  = wort.find_first_of( SATZZEICHEN, pos ) )
			wort.erase( pos, 1 ) ;

		// ignoriere leer gewordene W�rter (die nur Satzzeichen enthielten)
		if ( wort.empty() )
			continue ;

		// mache Anfangs-Gro�buchstaben klein
		if ( wort[ 0 ] >= 'A'  &&  wort[ 0 ] <= 'Z' )
			wort[ 0 ] += 'a' - 'A' ;

	/***  z�hle wort, wenn in Liste woerter vorhanden;
	      f�ge wort neu in woerter ein, wenn nicht      ***/


        Zaehler zaehler(wort);
        Liste<Zaehler>::iterator zaehlerIter = woerter.find(zaehler); // suche wort in woerter

        if (zaehlerIter != woerter.end()) // wenn wort in woerter stellt
            zaehlerIter->count(); // +1 count

        else // wenn nicht
            woerter.insert(zaehler); // setze wort in woerter ein


	}  // while ( datei >> wort )
	datei.close() ;

	cout << "Zeit Einlesen:      " << uhr << endl ;

/***  sortiere W�rter nach absteigender H�ufigkeit mit MergeSort  ***/

    Liste<Zaehler> liste = woerter.toList();

	uhr.start() ;
    liste.mergeSort() ;
	cout << "Zeit MergeSort:     " << uhr << endl ;

	// pr�fe Korrektheit der Sortierung
	if ( ! liste.istSortiert() )
		cout << "Liste wurde nicht korrekt sortiert!" << endl ;

/***  gebe aufgetretene W�rter aus  ***/

	cout << endl ;
	cout << liste.size() << " verschiedene Woerter:" << endl ;
	cout << left << endl ;

	for ( Zaehler const& z : liste )
	{
		// begrenze Ausgabe auf vorgegebene Anzahl
		if ( anzahl-- == 0 )
			break ;

		cout << setw( 17 ) << z << endl ;
	}
	cout << endl ;
	
	return 0 ;

}  // main()

catch ( exception const& exc )
{
	cerr << exc.what() << endl ;
}
catch ( char const* text )
{
	cerr << text << endl ;
}