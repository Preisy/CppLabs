#pragma once


#include <tuple>
#include <typeinfo>

template<class T>
struct HasInputOperator {
private:

    template<class TT,
            typename = decltype(std::declval<std::istream>().operator>>(std::declval<TT &>()))>
    static std::true_type method(int) { return {}; }

    template<class ...>
    static std::false_type method(...) { return {}; }


    template<class TT,
            typename = decltype(operator>>(std::declval<std::istream &>(), std::declval<const TT &>()))>
    static std::true_type op1(int) { return {}; }


    template<class ...>
    static std::false_type op1(...) { return {}; }

    template<class TT,
            typename = decltype(operator>>(std::declval<std::istream &>(), std::declval<TT &>()))>
    static std::true_type op2(int) { return {}; }


    template<class ...>
    static std::false_type op2(...) { return {}; }

public:
    static constexpr bool value = std::__or_<
            decltype(method<T>(7)),
            decltype(op1<T>(7)),
            decltype(op2<T>(7))
    >::value;
    using type = decltype(value);
};


template<class T>
inline constexpr bool HasInputOperatorV = HasInputOperator<T>::value;

template<class T>
struct HasOutputOperator {
private:

    template<class TT,
            typename = decltype(std::declval<std::ostream>().operator<<(std::declval<TT &>()))>
    static std::true_type method(int) { return {}; }

    template<class ...>
    static std::false_type method(...) { return {}; }


    template<class TT,
            typename = decltype(operator<<(std::declval<std::ostream &>(), std::declval<const TT &>()))>
    static std::true_type op1(int) { return {}; }


    template<class ...>
    static std::false_type op1(...) { return {}; }

    template<class TT,
            typename = decltype(operator<<(std::declval<std::ostream &>(), std::declval<TT &>()))>
    static std::true_type op2(int) { return {}; }


    template<class ...>
    static std::false_type op2(...) { return {}; }

public:
    static constexpr bool value = std::__or_<
            decltype(method<T>(7)),
            decltype(op1<T>(7)),
            decltype(op2<T>(7))
    >::value;
    using type = decltype(value);
};

template<class T>
inline constexpr bool HasOutputOperatorV = HasOutputOperator<T>::value;