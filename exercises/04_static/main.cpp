#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) { // 在函数声明前使用 static 关键字，表示这个函数的作用域被限制在声明它的文件内（文件作用域）
    // 第一次调用：当你第一次调用 func 函数时，static_ 变量会被初始化为 param 的值。
    // 后续调用：在随后的每次调用中，static_ 变量将不会重新初始化，而是保持之前的值并递增。
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
