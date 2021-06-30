//
// Created by Xuantong on 2021/6/15.
//

#ifndef PA3_ZAEHLER_H
#define PA3_ZAEHLER_H

#include <iostream> // für cout
#include <string>

/**
* Klasse f¨ur einzelne W¨orter mit Z¨ahler f¨ur H¨aufigkeit
**/

class Zaehler
{
/***  private Elemente ***/
    std::string _s; // wort
    size_t _count; // zählt die Häufigkeit der Worter
public:

/***  Konstruktoren  ***/
    Zaehler(std::string const& s)
            :_s(s),
             _count(1)
    {}

/***  get-Methoden  ***/

    explicit operator size_t() const
    {
        std::hash<std::string> hasher; // StandardKlasse hash
        return hasher(_s);
    }

/***  set-Methoden  ***/
    void count()
    {
        ++_count;
    }

/***  Vergleichesoperatoren  ***/
    bool operator>(Zaehler const & zaehler) const
    {
        return _count < zaehler._count;
    }

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
