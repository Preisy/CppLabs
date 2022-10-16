#pragma once

//#include "Item.h"
#include "Resource.h"
#include <iostream>

template<class Key, class Head, class...Tail>
class Table {
private:
    int capacity;
    int size = 0;

    using Item = std::tuple<Key, Head, Tail...>;

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
    Table() : capacity(10) {}


    explicit Table(int capacity) : capacity(capacity) {};

    Table(Item *items, int size) {
        data = new Item[capacity];
        for (int i = 0; i < size; ++i) {
            add(items[i]);
        }
    }

    ~Table() {
        delete[] data;
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



//    template<class...Args,
//            typename = std::enable_if_t<sizeof...(Args) == sizeof...(Tail) + 1>>
//    bool add(Head&& head, Tail&&...tail) {
    bool add(const Item &item) {
        if (size == capacity) resize();
        Item *result = std::lower_bound(data, data + size, item.getKey(), [](const Item &current, int key) { return current.getKey() < key; });
        if (data == nullptr) data = new Item[capacity];
        if (result == nullptr) data[0] = item;
        else {
            if (result != data + size && result->getKey() == item.getKey()) return false;
            for (Item *p = data + size; p >= result + 1; --p) {
                *p = *(p - 1);
            }
            *result = item;
        }
        ++size;
        return true;
    }

    bool update(const Item &item) {
        int key = item.getKey();
        Item *result = std::lower_bound(data, data + size, key, [](const Item &current, int key) { return current.getKey() < key; });
        if (result == data + size || result->getKey() != key) return false;
        *result = item;
        return true;
    }

    bool remove(int key) {
        Item *result = std::lower_bound(data, data + size, key, [](const Item &current, int key) { return current.getKey() < key; });
        if (result == data + size || result->getKey() != key) return false;
        for (Item *i = result; i < data + size - 1; ++i) {
            *i = *(i + 1);
        }
        --size;
        return true;
    }

    void resize() {
        int newCapacity = capacity * 3 / 2;
        Item *newData = new Item[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        std::cout << *this << std::endl;
    }


    Resource<Item> operator[](int key) const {
        return getItem(key);
    }

    Resource<Item> getItem(int key) const {
        Item *result = std::lower_bound(data, data + size, key, [](const Item &current, int key) { return current.getKey() < key; });
        if (result == data + size || result->getKey() != key) return Resource<Item>();
        return Resource<Item>(result);
    }

    Table &operator=(const Table &other) {
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = new Item[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Table &operator=(Table &&other) noexcept {
        this->size = other.size;
        this->capacity = other.capacity;
        delete[] this->data;
        this->data = other.data;
        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
        return *this;
    }
    Table(const Table &other)
    {
        this->data = new Item[capacity];
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Table(Table &&other) noexcept
            : size(other.size), capacity(other.capacity){
        delete[] this->data;
        this->data = other.data;
        other.size = 0;
        other.capacity = 0;
        other.data = nullptr;
    }
};
