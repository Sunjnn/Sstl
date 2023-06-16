#ifndef __STL_PAIR__
#define __STL_PAIR__

namespace Sstl {

template<class T1, class T2>
struct pair {
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    pair() : first(T1()), second(T2()) {}
    pair(const T1 &a, const T2 &b) : first(a), second(b) {}
}; // class pair

} // namespace Sstl

namespace Sstl {

template<class pair>
class select1st {
public:
    const pair::first_type operator()(const pair &x) {
        return x.first;
    }
};

} // namespace Sstl


#endif
