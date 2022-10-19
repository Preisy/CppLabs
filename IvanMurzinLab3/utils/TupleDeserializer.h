#pragma once

#include <tuple>
#include <sstream>
#include <iostream>
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

template<class...Args>
class TupleDeserializer {
public:
    static std::tuple<Args...> deserialize(std::istream & in) {
        static_assert(std::__and_<
                HasInputOperator<Args>...
        >::value, "Type parameters must have overloaded operator >>");

        return {getEl<Args>(in)...};
    }

    static std::tuple<Args...> deserialize(const std::string & str) {
        static_assert(std::__and_<
                    HasInputOperator<Args>...
                >::value, "Type parameters must have overloaded operator >>");
        std::istringstream in(str);
        return {getEl<Args>(in)...};
    }

private:
    template<class T>
    static T getEl(std::istream & in) {
        T el;
        in >> el;
        if (!in) {
            throw std::invalid_argument("Cant read " + std::string(typeid(T).name()) + " from input stream");
        }
        return el;
    }

};



