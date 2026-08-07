// main.cpp
// 第 1 课主程序：用固定大小的数组表示一帧 4x3 的 8-bit 灰度图，
// 计算平均亮度，并根据阈值判断曝光状态。
// 重点语法：constexpr、std::array、范围 for、static_cast、if/else。
#include <array>
#include <cstdint>
#include <iostream>

// main() 是程序入口：构造像素数据、累加亮度、计算平均值、打印结果。
int main() {
    // 第一版先使用固定尺寸，模拟一帧 4x3 的 8-bit 灰度图。
    constexpr int kWidth = 4;//constexpr 表示值在编译期确定，并且之后不能修改。
    constexpr int kHeight = 3;
    constexpr std::size_t kPixelCount =
        static_cast<std::size_t>(kWidth * kHeight); // std::size_t是 C++ 标准库里专门用来表示“大小 / 数量 / 下标”的无符号整数类型。等价于 unsigned long long 或者 unsigned long，64 位系统占用 8 个字节，64bit。
    // using起别名
    using Pixel = std::uint8_t;
    // std::array<T, N> 表示包含 N 个 T 的固定大小连续数组。这里的像素在内存中连续排列，前三行代码也刻意排成图像的三行，便于观察。
    // std::array 的元素数量必须在编译时确定
    const std::array<Pixel, kPixelCount> pixels{
        20,
        30,
        40,
        50,
        40,
        60,
        80,
        100,
        70,
        100,
        150,
        190,
    };

    std::uint32_t luma_sum = 0;
    // 这里的 pixel 是一个值拷贝。单个像素只有 1 byte，复制简单直接。以后元素变成较大的帧对象时，随手复制就可能导致昂贵的整帧拷贝；第 2 课会引入引用。
    for (const Pixel pixel : pixels) {
        luma_sum += pixel;
    }
    // static_cast 是 C++ 中表达“我有意进行这种类型转换”的写法，比 C 风格的 (double)value 更醒目，也更容易被工具检查。
    const double average_luma =
        static_cast<double>(luma_sum) / static_cast<double>(pixels.size());
    // 下面开始输出帧尺寸、像素数量和平均亮度。
    
    std::cout << "Frame: " << kWidth << 'x' << kHeight
              << ", pixels=" << pixels.size() << '\n';
    std::cout << "Average luma: " << average_luma << '\n';

    // 曝光阈值：平均亮度低于 90 视为欠曝，否则视为可接受。
    constexpr double kUnderexposedThreshold = 90.0;
    if (average_luma < kUnderexposedThreshold) {
        std::cout << "Exposure status: underexposed\n";
    } else {
        std::cout << "Exposure status: acceptable\n";
    }

    // 程序正常结束，返回 0 表示成功。
    return 0;
}
