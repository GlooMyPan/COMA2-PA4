//
// Created by Xuantong on 2021/6/15.
//

#ifndef PA3_ZAEHLER_H
#define PA3_ZAEHLER_H

#include <iostream> // für cout
#include <string>
#include <functional> // für hash<T>

/**
* Klasse f¨ur einzelne W¨orter mit Z¨ahler f¨ur H¨aufigkeit
**/

class Zaehler
{
/***  private Elemente ***/
    std::string _s; // wort
    size_t _count; // die Häufigkeit von _s
public:

/***  Konstruktoren  ***/
    Zaehler(std::string const& s)
            :_s(s),
             _count(1)
    {}

/***  get-Methoden  ***/
    // gibt hash-wert von _s aus
    explicit operator size_t() const
    {
        static std::hash<std::string> hasher; // StandardKlasse hash
        return hasher(_s);
    }

/***  set-Methoden  ***/
    // zählt _s
    void count()
    {
        ++_count; //
    }

/***  Vergleichesoperatoren  ***/
    // ob die Häufigkeit von zaehler größer als _s ist.
    bool operator>(Zaehler const & zaehler) const
    {
        return _count < zaehler._count;
    }

    // ob die Häufigkeit von zaehler gleich _s ist.
    bool operator==(Zaehler const & zaehler) const
    {
        return _s == zaehler._s;
    }

/***  Ausgabe auf ostream  ***/
    friend
    std::ostream &operator<<(std::ostream &cout, Zaehler const &zaehler)
    {
        return std::cout << zaehler._s << " "<< zaehler._count;;
    }
};

#endif //PA3_ZAEHLER_H
