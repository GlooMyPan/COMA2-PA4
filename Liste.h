//
// Created by Xuantong on 2021/6/15.
//

#ifndef PA3_LISTE_H
#define PA3_LISTE_H
#include <list>
#include <iostream>
#include <iterator> // für advance()

template <class T>
class Liste
    : public std::list<T>
{
public:
typedef typename std::list<T>::iterator iterator;
typedef typename std::list<T>::const_iterator const_iterator;
/***  get-Methoden  ***/
    bool istSortiert() const
    {
        for (const_iterator jt = this->begin(), it = jt++; jt != this->end(); it = jt++)
            if (*it > *jt)   // Reihenfolge falsch?
                return false;
        return true;
    } // istSortiert() O(n)

    iterator find(T const &t)
    {
        // gebe Iterator auf den ersten Eintrag, der gem¨aß T::operator ==
        // gleich zu obj ist, bzw. end(), falls es keinen gibt
        iterator it;
        for (it = this->begin(); it != this->end(); ++it)
            if (*it == t)   // T::operator ==
                break;
        return it;
    } // find(const T &t) O(n)


/***  set-Methoden  ***/
    void mergeSort()
    {
        size_t n = this->size();
        if (n < 2) // nicht noetig zu sort
            return;
        size_t middle = n/2;

/*** teile Objekt in zwei H¨alften ***/
        iterator miditer = this->begin();
        advance(miditer, middle); // finde mitte Iterator

        Liste<T> l2; // neue Objekt darzustellen
        l2.splice(l2.begin(), *this, this->begin(), miditer); // l2 haben die begin() nach mitte Iterator Daten von original Objekt

/*** sortiere beide Listen rekursiv ***/
        this->mergeSort(); // rekursion
        l2.mergeSort(); //rekursion

/*** vereinige beide Listen ins Objekt zur¨uck ***/
        iterator i1 = this->begin(); // begin() von original Objekt
        iterator i2 = l2.begin(); // begin() von neue Objekt
        while (i1 != this->end() && i2 != l2.end())
            if (*i1 > *i2)  // T::operator >
                this->splice(i1, l2, i2++);
            else
                ++i1;
        // h¨ange restliche liste an *this an
        this->splice(i1, l2);
    } //mergeSort() nlog(n)
};  // class Liste<T>

#endif //PA3_LISTE_H
