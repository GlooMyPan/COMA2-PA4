#ifndef PA4_PAIR_H
#define PA4_PAIR_H


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
    size_t get_count() const
    {
        return _count;
    }

    explicit operator size_t() const
    {
        std::hash<size_t> hasher; // StandardKlasse hash
        return hasher(_number);
    }

/***  Vergleichesoperatoren  ***/
    bool operator==(const Pair& pair) const
    {
        return pair._number == _number;
    }
}; // class Pair

#endif //PA4_PAIR_H
