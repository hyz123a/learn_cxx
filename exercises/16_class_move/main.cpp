#include "../exercise.h"
#include <cstddef>
#include <utility>

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache_;
    int cached_;
    int capacity_;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity = 2) : capacity_(capacity), cache_(new size_t[capacity]), cached_(2) {
        cache_[0] = 0;
        cache_[1] = 1;
    }

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept {
        capacity_ = other.capacity_;
        cached_ = other.cached_;
        cache_ = other.cache_;
        other.cache_ = nullptr;
        other.cached_ = 0;
        other.capacity_ = 0;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        if (this == &other) {
            return *this;
        }
        capacity_ = other.capacity_;
        cached_ = other.cached_;
        cache_ = other.cache_;
        other.cache_ = nullptr;
        other.cached_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache_;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        for (; cached_ < capacity_; ++cached_) {
            cache_[cached_] = cache_[cached_ - 1] + cache_[cached_ - 2];
        }
        return cache_[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached_, "i out of range");
        return cache_[i];
    }
    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache_;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);
    ASSERT(!fib.is_alive(), "Object moved");
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);
    fib0 = std::move(fib0);
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}
