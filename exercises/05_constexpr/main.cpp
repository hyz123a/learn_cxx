#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    if (i > 20) {
        return 0;
    }
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            // 递归深度影响是否能进行编译器计算
            return fibonacci(i - 2) + fibonacci(i - 1);
    }
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    constexpr auto ANS_N = 90;
    constexpr auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
