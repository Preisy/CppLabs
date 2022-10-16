#pragma once

#include <tuple>

template<class Key, class Head, class...Tail>
class Item {
private:
    Key key;

    using Tuple = std::tuple<Head, Tail...>;
    Tuple data;

public:
    constexpr Item() = default;
    constexpr ~Item() = default;

//    template<class...Args,
//            typename = std::enable_if_t<sizeof...(Args) == std::tuple_size_v<Tuple>>>

//    template<class...Args>

    template<class KKey, class...Args>
    constexpr Item(KKey&& key, Args&&... names)
        : key(std::forward<KKey>(key)), data(std::forward<Args>(names)...) {}

    int getSize() {
        return std::tuple_size_v<Tuple>;
    }

    constexpr const Key & getKey() const {
        return key;
    }

    template<std::size_t I,
            typename = std::enable_if_t<I < std::tuple_size_v<Tuple>>>
    constexpr typename std::tuple_element<I, Tuple>::type &
    get() noexcept { // why noexcept
        return std::get<I>(data);
    }
};