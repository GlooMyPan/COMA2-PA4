#include <iostream>
#include <cstdlib>				// für atol()
#include <string>
#include <vector>
#include <cmath>
#include "HashTabelle.h"
#include "Pair.h"

using namespace std ;

// Ausgabe von z/n in endlicher bzw. periodischer Darstellung
vector<string> dezimalbruch(long long z, long long n, size_t numberOfDigits=100)
{
    string underscore;
    if (z % n == 0) // keine Nachkommastellen
        return {underscore, to_string(z / n)};

    string zahl = to_string(z/n) + '.'; // Vorkommastellen, Dezimalpunkt

    HashTabelle<Pair> T(100); // initialisiere leere Hash-Tabelle T
    size_t stelle = 0; // akt. Stellenindex nach dem Komma
    size_t periode = 0; // Stelle des Periodenbeginns

    for (long long rest = 10*(z%n); rest > 0; rest = 10*(rest % n))
    {
        ++stelle; // aktualisiere Stellenindex
        Pair p(rest, stelle);

        HashTabelle<Pair>::iterator pIter = T.find(p);
        if (pIter != T.end())  // Periode gefunden
        {
            periode = stelle - pIter->get_count(); // richtige Stelle des Periodenbeginns
            break;
        }
        zahl += to_string(rest/n); // speichere akt. Dezimalstelle

        T.insert(p); // fuge neuen Listeneintrag ein
    }

    if (periode > 0)
        underscore = string(zahl.size()-periode, ' ') + string(periode, '_'); // bildt die Unterstreichen

    vector<string> ans; // ausgeben vector

    /*** sie werden korrekt angezeigt, auch wenn sie zu lang sind ***/
    //  Zeilenumbruch bei lange Zahlen
    while (zahl.size() >= numberOfDigits)
    {
        ans.push_back(underscore.substr(0, numberOfDigits));
        underscore.erase(0, numberOfDigits);
        ans.push_back(zahl.substr(0, numberOfDigits));
        zahl.erase(0, numberOfDigits);
    }
    ans.push_back(underscore);
    ans.push_back(zahl);
    return ans;
}

int main ( int narg, char* argv[] )
try
{
	// gebe Usage aus
	if ( narg < 3 )
	{
		cout << "Usage: " << argv[ 0 ] << "  zaehler  nenner"  << endl ;
		cout << "       zaehler: natuerliche Zahl"			   << endl ;
		cout << "       nenner : natuerliche Zahl"			   << endl ;
		cout << "Stellt den Bruch zaehler/nenner als endliche" << endl ;
		cout << "bzw. periodische Dezimalzahl dar."			   << endl ;

		return 0 ;
	}

/***  initialisiere Parameter  ***/

	long long zaehler = atol( argv[ 1 ] ) ;
	long long nenner  = atol( argv[ 2 ] ) ;

	if ( nenner == 0 )
	{
		cerr << "Der Nenner muss != 0 sein!" << endl ;
		return -1 ;
	}
	
	if ( zaehler < 0 )
		zaehler = -zaehler ;
	if ( nenner < 0 )
		nenner  = -nenner ;

/***  Algorithmus dezimalbruch()  ***/

	vector<string> ans = dezimalbruch(zaehler, nenner);
	for (const string & s : ans)
	    cout << s << endl; // gibt Ergebnisse aus

	return 0 ;

}  // main()

catch ( exception const& exc )
{
	cerr << exc.what() << endl ;
}

