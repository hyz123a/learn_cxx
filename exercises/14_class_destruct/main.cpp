#include "../exercise.h"
#include <cstddef>
#include <cstdlib>

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache_;
    int cached_;
    int capacity_;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity) : capacity_(capacity), cache_(new size_t[16]), cached_(2) {
        cache_[0] = 0;
        cache_[1] = 1;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache_;
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t get(int i) {
        for (; cached_ < capacity_; ++cached_) {
            cache_[cached_] = cache_[cached_ - 1] + cache_[cached_ - 2];
        }
        return cache_[i];
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
