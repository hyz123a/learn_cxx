#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache_[128] = {0, 1};
    int cached_{2};

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        for (; cached_ < sizeof(cache_) / sizeof(*cache_); ++cached_) {
            cache_[cached_] = cache_[cached_ - 1] + cache_[cached_ - 2];
        }
        return cache_[i];
    }
};

int main(int argc, char **argv) {
    // TODO: 初始化缓存结构体，使计算正确
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
