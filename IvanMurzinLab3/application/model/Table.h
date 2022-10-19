#pragma once

//#include "Item.h"
#include "Resource.h"
#include <iostream>
#include <algorithm>
#include <utility>
#include <tuple>
#include "TupleUnpacker.h"

namespace Models {

template<class Key, class Head, class...Tail>
class Table {
private:
    int capacity;
    int size = 0;

    using Item = std::tuple<Key, Head, Tail...>;
    using CItem = std::tuple<Key, Head, Tail...>;

    Item *data = nullptr;

    class Iterator {
    private:
        int current = 0;
        Item *data;

    public:
        Iterator(Item *data, int current) : data(data), current(current) {};

        Item &operator*() const {
            return data[current];
        }

        Item *operator->() const {
            return &data[current];
        }

        Iterator &operator++() {
            ++current;
            return *this;
        }

        Iterator operator++(int) {
            Iterator old(*this);
            ++*this;
            return old;
        }

        bool operator!=(const Iterator &right) const {
            return current != right.current;
        }

    };

public:
    Table() : capacity(0) {}

    explicit Table(int capacity) : capacity(capacity) {};


    ~Table() {
        delete[] reinterpret_cast<uint8_t*>(data);
    }

    int getSize() const {
        return size;
    }

    Iterator begin() const {
        return {data, 0};
    }

    Iterator end() const {
        return {data, size};
    }


    template<class KKey, class...Args>
    constexpr bool emplaceAdd(KKey&& key, Args&&...args) {
        if (size == capacity) resize();
        Item *result = std::lower_bound(data, data + size, key, [](const Item &current, const KKey & key) {
            return std::get<0>(current) < key;
        });
        if (result >= data + size) {
            ::new (result) Item(std::forward<Key>(key), std::forward<Args>(args)...);
        } else {
            if (result != data + size && std::get<0>(*result) == key) return false;

            ::new (data + size) Item(std::move(*(data + size - 1)));
            for (Item *p = data + size - 1; p >= result + 1; --p) {
                *p = std::move(*(p - 1));
            }
            *result = {std::forward<Key>(key), std::forward<Args>(args)...};
        }
        ++size;
        return true;
    }

public:
    constexpr bool add(const Item & item) {
        return applyTuple([this](const Key & key, const Head & head, const Tail & ... tail){
            return emplaceAdd(key, head, tail...);
        }, item);
    }

    constexpr bool add(Item && item) {
        return applyTuple([this](Key&& key, Head && head, Tail && ... tail){
            return emplaceAdd(std::move(key), std::move(head), std::move(tail)...);
        }, std::move(item));
    }

    bool update(const Item &item) {
        Item *result = std::lower_bound(data, data + size, std::get<0>(item), [](const Item &current, const Key & key) { return std::get<0>(current) < key; });
        if (result == data + size || std::get<0>(result) != std::get<0>(item)) return false;
        *result = item;
        return true;
    }

    bool update(Item &&item) {
        Item *result = std::lower_bound(data, data + size, std::get<0>(item), [](const Item &current, const Key & key) { return std::get<0>(current) < key; });
        if (result == data + size || std::get<0>(result) != std::get<0>(item)) return false;
        *result = std::move(item);
        return true;
    }

    bool remove(const Key & key) {
        Item *result = std::lower_bound(data, data + size, key, [](const Item &current, const Key & key) { return std::get<0>(current) < key; });
        if (result == data + size || std::get<0>(*result) != key) return false;
        for (Item *i = result; i < data + size - 1; ++i) {
            *i = std::move(*(i + 1));
        }
        --size;
        return true;
    }

    void resize() {
        capacity = capacity == 0 ? 2 : capacity * 3 / 2;
        Item* newData = reinterpret_cast<Item*>(new uint8_t[sizeof(Item) * capacity]);
        for (int i = 0; i < size; ++i) {
            ::new (newData + i) Item(std::move(data[i]));
        }
        delete[] reinterpret_cast<uint8_t*>(data);
        data = newData;
    }


    Resource<Item> operator[](const Key & key) const {
        return getItem(key);
    }

    Resource<Item> getItem(const Key & key) const {
        Item *result = std::lower_bound(data, data + size, key, [](const Item &current, const Key & key) { return std::get<0>(current) < key; });
        if (result == data + size || std::get<0>(*result) != key) return Resource<Item>();
        return Resource<Item>(result);
    }

    Table &operator=(const Table &other) {
        if (std::addressof(other) == this)
            return *this;
        this->size = other.size;
        this->capacity = other.capacity;
        for (int i = 0; i < size; ++i)
            (data + size)->~Item();
        delete[] reinterpret_cast<uint8_t*>(this->data);
        this->data = reinterpret_cast<Item*>(new uint8_t[capacity * sizeof(Item)]);
        for (int i = 0; i < size; ++i) {
            ::new (data + i) Item(other.data[i]);
        }
        return *this;
    }

    Table &operator=(Table &&other) noexcept {
        if (std::addressof(other) == this)
            return *this;
        this->size = other.size;
        this->capacity = other.capacity;
        for (int i = 0; i < size; ++i)
            (data + size)->~Item();
        delete[] reinterpret_cast<uint8_t*>(this->data);
        this->data = other.data;
        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
        return *this;
    }
    Table(const Table &other) {
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = reinterpret_cast<Item*>(new uint8_t[capacity * sizeof(Item)]);
        for (int i = 0; i < size; ++i) {
            ::new (data + i) Item(other.data[i]);
        }
    }

    Table(Table &&other) noexcept
            : size(other.size), capacity(other.capacity){
        this->data = other.data;
        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
    }
};

}
