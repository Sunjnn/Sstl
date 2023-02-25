#ifndef MAX_H
#define MAX_H

template <class T>
inline T max(T a, T b) {
    if (a > b) return a;
    return b;
}

#endif