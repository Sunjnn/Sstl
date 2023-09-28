#ifndef __STL_FUNCTION_H__
#define __STL_FUNCTION_H__

// unary_function and binary_function
namespace Sstl {

template<class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template<class Arg1, class Arg2, class Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

} // namespace Sstl unary_function and binary_function

// Arithmetic functor
namespace Sstl {

template<class T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x + y; }
};

template<class T>
struct minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x - y; }
};

template<class T>
struct multiplies : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x * y; }
};

template<class T>
struct divides : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x / y; }
};

template<class T>
struct modules : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const { return x % y; }
};

template<class T>
struct nagate : public unary_function<T, T> {
    T operator()(const T& x) const { return -x; }
};

} // namespace Sstl Arithmetic functor

// Relational functor
namespace Sstl {

template<class T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x == y; }
};

template<class T>
struct not_equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x != y; }
};

template<class T>
struct greater : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x > y; }
};

template<class T>
struct less : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x < y; }
};

template<class T>
struct greater_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x >= y; }
};

template<class T>
struct less_equal : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x <= y; }
};

template<class T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x == y; }
};

} // namespace Sstl Relational functor

// Logical functor
namespace Sstl {

template<class T>
struct logical_and : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x && y; }
};

template<class T>
struct logical_or : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const { return x || y; }
};

template<class T>
struct logical_not : public unary_function<T, bool> {
    bool operator()(const T& x) const { return !x; }
};

} // namespace Sstl Logical functor

// function adapters
namespace Sstl {

// unary nagate
template<class Predicate>
class unary_negate
    : public unary_function<typename Predicate::argument_type, bool> {
protected:
    Predicate pred;
public:
    explicit unary_function(const Predicate& x) : pred(x) {}
    bool operator()(const typename Predicate::argument_type& x) const {
        return pred(x);
    }
};

template<class Predicate>
inline unary_negate<Predicate> not1(const Predicate& pred) {
    return unary_negate<Predicate>(pred);
}


// binary nagate
template<class Predicate>
class binary_negate
    : public binary_function<typename Predicate::first_argument_type,
                             typename Predicate::second_argument_type,
                             bool> {
protected:
    Predicate pred;
public:
    explicit binary_negate(const Predicate& x) : pred(x) {}
    bool operator()(const typename Predicate::first_argument_type& x,
                    const typename Predicate::second_argument_type& y) {
        return !pred(x, y);
    }
};

template<class Predicate>
inline binary_negate<Predicate> not2(const Predicate& pred) {
    return binary_negate<Predicate>(pred);
}


// binder1st
template<class Operation>
class binder1st
    : public unary_function<typename Operation::second_argument_type,
                            typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::first_argument_type value;

public:
    binder1st(const Operation& x,
              const typename Operation::first_argument_type& y)
        : op(x), value(y) {}

    typename Operation::result_type
    operator()(const typename Operation::second_argument_type& x) const {
        return op(value, x);
    }
};

template<class Operation, class T>
inline binder1st<Operation> bind1st(const Operation& op, const T& x) {
    typedef typename Operation::first_argument_type arg1_type;
    return binder1st<Operation>(op, arg1_type(x));
}


// binder2nd
template<class Operation>
class binder2nd
    : public unary_function<typename Operation::first_argument_type,
                            typename Operation::result_type> {
protected:
    Operation op;
    typename Operation::second_argument_type value;
public:
    binder2nd(const Operation& x,
              const typename Operation::second_argument_type& y)
        : op(x), value(y) {}

    typename Operation::result_type
    operator()(const typename Operation::first_argument_type& x) const {
        return op(x, value);
    }
};

template<class Operation, class T>
inline binder2nd<Operation> bind2nd(const Operation& op, const T& x) {
    typedef typename Operation::second_argument_type arg2_type;
    return binder2nd<Operation>(op, arg2_type(x));
}


// unary compose
template<class Operation1, class Operation2>
class unary_compose
    : public unary_function<typename Operation2::argument_type,
                            typename Operation1::result_type> {
protected:
    Operation1 op1;
    Operation2 op2;
public:
    unary_compose(const Operation1& x, const Operation2& y) : op1(x), op2(y) {}

    typename Operation1::result_type
    operator()(const typename Operation2::argument_type& x) const {
        return op1(op2(x));
    }
};

template<class Operation1, class Operation2>
inline unary_compose<Operation1, Operation2>
compose1(const Operation1& op1, const Operation2& op2) {
    return unary_compose<Operation1, Operation2>(op1, op2);
}


// binary compose
template<class Operation1, class Operation2, class Operation3>
class binary_compre
    : public unary_function<typename Operation2::argument_type,
                            typename Operation1::result_type> {
protected:
    Operation1 op1;
    Operation2 op2;
    Operation3 op3;
public:
    binary_compre(const Operation1& x, const Operation2& y,
                  const Operation3& z) : op1(x), op2(y), op3(z) {}

    typename Operation1::result_type
    operator()(const typename Operation2::argument_type& x) const {
        return op1(op2(x), op3(x));
    }
};

template<class Operation1, class Operation2, class Operation3>
inline binary_compre<Operation1, Operation2, Operation3>
compose2(const Operation1& op1, const Operation2& op2, const Operation3& op3) {
    return binary_compre<Operation1, Operation2, Operation3>(op1, op2, op3);
}


// ptr to unary function
template<class Arg, class Result>
class pointer_to_unary_function : public unary_function<Arg, Result> {
protected:
    Result (*ptr)(Arg);
public:
    pointer_to_unary_function() {}
    explicit pointer_to_unary_function(Result (*x)(Arg)) : ptr(x) {}

    Result operator()(Arg x) const { return ptr(x); }
};

template<class Arg, class Result>
inline pointer_to_unary_function<Arg, Result>
ptr_fun(Result (*x)(Arg)) {
    return pointer_to_unary_function<Arg, Result>(x);
}


// ptr to binary function
template<class Arg1, class Arg2, class Result>
class pointer_to_binary_function
    : public binary_function<Arg1, Arg2, Result> {
protected:
    Result (*ptr)(Arg1, Arg2);
public:
    pointer_to_binary_function() {}
    explicit pointer_to_binary_function(Result (*x)(Arg1, Arg2)) : ptr(x) {}

    Result operator()(Arg1 x, Arg2 y) const { return ptr(x, y); }
};

template<class Arg1, class Arg2, class Result>
inline pointer_to_binary_function<Arg1, Arg2, Result>
ptr_fun(Result (*x)(Arg1, Arg2)) {
    return pointer_to_binary_function<Arg1, Arg2, Result>(x);
}


// mem func
template<class S, class T>
class mem_fun_t : public unary_function<T*, S> {
public:
    explicit mem_fun_t(S (T::*pf)()) : f(pf) {}
    S operator()(T* p) const { return (p->*f)(); }
private:
    S (T::*f)();
};

template<class S, class T>
inline mem_fun_t<S, T> mem_fun(S (T::*f)()) {
    return mem_fun_t<S, T>(f);
}


template<class S, class T>
class const_mem_fun_t : public unary_function<const T*, S> {
public:
    explicit const_mem_fun_t(S (T::*pf)() const) : f(pf) {}
    S operator()(const T* p) const { return (p->*f)(); }
private:
    S (T::*f)() const;
};

template<class S, class T>
inline const_mem_fun_t<S, T> mem_fun(S (T::*f)() const) {
    return const_mem_fun_t<S, T>(f);
}


template<class S, class T>
class mem_fun_ref_t : public unary_function<T, S> {
public:
    explicit mem_fun_ref_t(S (T::*pf)()) : f(pf) {}
    S operator()(T& r) const { return (r.*f)(); }
private:
    S (T::*f)();
};

template<class S, class T>
inline mem_fun_ref_t<S, T> mem_fun_ref(S (T::*f)()) {
    return mem_fun_ref_t<S, T>(f);
}


template<class S, class T>
class const_mem_fun_ref_t : public unary_function<T, S> {
public:
    explicit const_mem_fun_ref_t(S (T::*pf)() const) : f(pf) {}
    S operator()(const T& r) const { return (r.*f)(); }
private:
    S (T::*f)() const;
};

template<class S, class T>
inline const_mem_fun_ref_t<S, T> mem_fun_ref(S (T::*f)() const) {
    return const_mem_fun_ref_t<S, T>(f);
}


template<class S, class T, class A>
class mem_fun1_t : public binary_function<T*, A, S> {
public:
    explicit mem_fun1_t(S (T::*pf)(A)) : f(pf) {}
    S operator()(T* p, A x) const { return (p->*f)(x); }
private:
    S (T::*f)(A);
};

template<class S, class T, class A>
inline mem_fun1_t<S, T, A> mem_fun1(S (T::*f)(A)) {
    return mem_fun1_t<S, T, A>(f);
}


template<class S, class T, class A>
class const_mem_fun1_t : public binary_function<T*, A, S> {
public:
    explicit const_mem_fun1_t(S (T::*pf)(A) const) : f(pf) {}
    S operator()(const T* p, A x) const { return (p->*f)(x); }
private:
    S (T::*f)(A) const;
};

template<class S, class T, class A>
inline const_mem_fun1_t<S, T, A> mem_fun1(S (T::*f)(A) const) {
    return const_mem_fun1_t<S, T, A>(f);
}


template<class S, class T, class A>
class mem_fun1_ref_t : public binary_function<T, A, S> {
public:
    explicit mem_fun1_ref_t(S (T::*pf)(A)) : f(pf) {}
    S operator()(T& r, A x) const { return (r.*f)(x); }
private:
    S (T::*f)(A);
};

template<class S, class T, class A>
inline mem_fun1_ref_t<S, T, A> mem_fun1_ref(S (T::*f)(A)) {
    return mem_fun1_ref_t<S, T, A>(f);
}


template<class S, class T, class A>
class const_mem_fun1_ref_t : public binary_function<T, A, S> {
public:
    explicit const_mem_fun1_ref_t(S (T::*pf)(A) const) : f(pf) {}
    S operator()(const T& r, A x) const { return (r.*f)(x); }
private:
    S (T::*f)(A) const;
};

template<class S, class T, class A>
inline const_mem_fun1_ref_t<S, T, A> mem_fun1_ref(S (T::*f)(A) const) {
    return const_mem_fun1_ref_t<S, T, A>(f);
}

} // namespace Sstl function adapters

#endif
