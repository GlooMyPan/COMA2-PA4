#ifndef PA4_PAIR_H
#define PA4_PAIR_H

#include <functional> // für hash<T>

class Pair {

/***  private Elemente ***/
    long long _number;
    size_t _count;

public:
/***  Konstruktoren  ***/
    Pair(long long number, size_t count)
    : _number(number),
      _count(count)
    {}

/***  get-Methoden  ***/
    // gibt _count aus
    size_t get_count() const
    {
        return _count;
    }

    // gibt hash-wert von _s aus
    explicit operator size_t() const
    {
        static std::hash<long long> hasher; // StandardKlasse hash
        return hasher(_number);
    }

/***  Vergleichesoperatoren  ***/
    // ob pair._number gleich this->_number ist.
    bool operator==(const Pair& pair) const
    {
        return pair._number == _number;
    }
}; // class Pair

#endif //PA4_PAIR_H
