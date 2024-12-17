#include "../exercise.h"

// READ: 复制构造函数 <https://zh.cppreference.com/w/cpp/language/copy_constructor>
// READ: 函数定义（显式弃置）<https://zh.cppreference.com/w/cpp/language/function>


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

    // TODO: 实现复制构造器
    DynFibonacci(DynFibonacci const &other) {
        this->cached_ = other.cached_;
        this->capacity_ = other.capacity_;
        cache_ = new size_t[capacity_];
        for (int i = 0; i < capacity_; ++i) {
            cache_[i] = other.cache_[i];
        }
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

    // NOTICE: 不要修改这个方法
    // NOTICE: 名字相同参数也相同，但 const 修饰不同的方法是一对重载方法，可以同时存在
    //         本质上，方法是隐藏了 this 参数的函数
    //         const 修饰作用在 this 上，因此它们实际上参数不同
    size_t get(int i) const {
        if (i <= cached_) {
            return cache_[i];
        }
        ASSERT(false, "i out of range");
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    DynFibonacci const fib_ = fib;
    ASSERT(fib_.get(10) == fib.get(10), "Object cloned");
    return 0;
}
