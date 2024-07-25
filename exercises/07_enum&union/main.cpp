#include "../exercise.h"

// READ: 枚举类型 <https://zh.cppreference.com/w/cpp/language/enum>

// `enum` 是 C 的兼容类型，本质上其对应类型的常量。
// 在 `enum` 中定义标识符等价于定义 constexpr 常量，
// 这些标识符不需要前缀，可以直接引用。
// 因此 `enum` 定义会污染命名空间。
enum ColorEnum : unsigned char {
    COLOR_RED = 31,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
};

// 有作用域枚举型是 C++ 引入的类型安全枚举。
// 其内部标识符需要带前缀引用，如 `Color::Red`。
// 作用域枚举型可以避免命名空间污染，并提供类型安全保证。
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

ColorEnum convert_by_pun(Color c) {
    // `union` 表示在同一内存位置存储的不同类型的值。
    // 其常见用法是实现类型双关转换，即将一种类型的值转换为另一种无关类型的值。
    // READ: <https://zh.cppreference.com/w/cpp/language/union>
    union TypePun {
        ColorEnum e;
        Color c;
    };
    // 这里类型双关的含义就是按 bit 转换成别的类型
    // 这个在 c++ 里面也是为定义行为，所以如果函数标记为 constexpr，并且变量也是 constexpr 的话
    // 那么这个代码没办法编译，因为不能存入 c 访问 e
    TypePun pun {
        .c =  c
    };
    // TODO: 补全类型双关转换

    return pun.e;
}

int main(int argc, char **argv) {
    // 下面的这种写法也能支持按 bit 转换成别的类型
    // 但这种在没对齐的情况下写法会有问题，会出现硬件报错
    // 用 union 的时候 c/c++ 编译器会解决这个问题
    float a = 2.5, *p = &a;
    std::cout << *(int *) p << std::endl // c 的写法
              << *reinterpret_cast<int *>(p) << std::endl; // c++ 的写法

    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}
