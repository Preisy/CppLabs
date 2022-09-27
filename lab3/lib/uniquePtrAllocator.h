#include <iostream>
#include <vector>
#include <memory>

template<class T, class Alloc>
class Deleter;

template<class T, class Alloc>
class UniqueAllocatorTraits : public std::allocator_traits<Alloc> {
public:
    static std::unique_ptr<T, Deleter<T, Alloc>> allocateUnique(Alloc& a, size_t n) {
        T* p = std::allocator_traits<Alloc>::allocate(a, n);
        auto up = std::unique_ptr<T, Deleter<T, Alloc>>(p, Deleter<T, Alloc>(a));
        return up;
    }
};

template<class T, class Alloc>
class Deleter {
    mutable Alloc a;

public:
    explicit Deleter(const Alloc & a) : a(a) {};

    void operator()(T* p) const {
        UniqueAllocatorTraits<T, Alloc>::destroy(a, p);
        std::allocator_traits<Alloc>::deallocate(a, p, 1);
    }
};
