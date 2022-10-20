#pragma once

#include <tuple>
#include <sstream>
#include <iostream>
#include <typeinfo>

#include "TypeTraits.h"
#include "TupleUnpacker.h"


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

    static std::string serialize(const std::tuple<Args...> & t) {
        static_assert(std::__and_<
                HasOutputOperator<Args>...
        >::value, "Type parameters must have overloaded operator <<");
        std::ostringstream out;

        applyTuple([&out](const Args & ... args) {
            print(out, args...);
        }, t);

        return out.str();
    }

private:
    static void print(std::ostream &) {}

    template<class Head, class...Tail>
    static void print(std::ostream & os, Head&& head, Tail&&...tail) {
        os << std::forward<Head>(head) << " ";
        print(os, std::forward<Tail>(tail)...);
    }



    template<class T>
    static T getEl(std::istream & in) {
        T el;
        in >> el;
        return el;
    }

};



