#ifndef LAB3_TUPLEUNPACKER_H
#define LAB3_TUPLEUNPACKER_H

#include <tuple>

template<std::size_t N>
struct TupleUnpacker {
    template<typename Function, class...ArgsTuple, class...Args>
    constexpr inline static auto _apply(Function f, const std::tuple<ArgsTuple...> & tuple, Args&&...args) -> decltype(auto) {
        return TupleUnpacker<N-1>::_apply(f,
                                   tuple,
                                   std::get<N-1>(tuple),
                                   std::forward<Args>(args)...);
    }

    template<typename Function, class...ArgsTuple, class...Args>
    constexpr inline static auto _apply(Function f, std::tuple<ArgsTuple...> && tuple, Args&&...args) -> decltype(auto) {
        return TupleUnpacker<N-1>::_apply(f,
                                   std::move(tuple),
                                   std::get<N-1>(std::move(tuple)),
                                   std::forward<Args>(args)...);
    }
};

template<>
struct TupleUnpacker<0> {
    template<typename Function, class...ArgsTuple, class...Args>
    constexpr inline static auto _apply(Function f, const std::tuple<ArgsTuple...> & tuple, Args&&...args) -> decltype(auto) {
//        std::cout << "_apply(const &)" << std::endl;
        return f(std::forward<Args>(args)...);
    }

    template<typename Function, class...ArgsTuple, class...Args>
    constexpr inline static auto _apply(Function f, std::tuple<ArgsTuple...> && tuple, Args&&...args) -> decltype(auto) {
        return f(std::forward<Args>(args)...);
    }
};

template<class Function, class...Args>
constexpr auto applyTuple(Function f, const std::tuple<Args...> & t) -> decltype(auto) {
    return TupleUnpacker<sizeof...(Args)>::_apply(f, t);
}
template<class Function, class...Args>
constexpr auto applyTuple(Function f, std::tuple<Args...>&& t) -> decltype(auto) {
    return TupleUnpacker<sizeof...(Args)>::_apply(f, std::move(t));
}

#endif //LAB3_TUPLEUNPACKER_H
