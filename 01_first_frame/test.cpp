// test.cpp
// 第 1 课练习版：在固定尺寸灰度帧的基础上，额外统计最暗和最亮像素，
// 并打印最小/最大亮度。其余逻辑与 main.cpp 基本一致。
#include <array>
#include <cstdint>
#include <iostream>

// main() 是程序入口：准备像素、统计总和与最值、计算平均值并输出。
int main()
{
    // 第一版先使用固定尺寸，模拟一帧 4x3 的 8-bit 灰度图。
    constexpr int kWidth = 4;
    constexpr int kHeight = 3;
    constexpr std::size_t kPixelCount =
        static_cast<std::size_t>(kWidth * kHeight);

    using Pixel = std::uint8_t;
    const std::array<Pixel, kPixelCount> pixels{
        245,
        30,
        40,
        245,
        40,
        245,
        80,
        245,
        70,
        245,
        150,
        190,
    };

    // luma_sum 用 32 位无符号整数累加；像素最大 255，12 个像素不会溢出。
    std::uint32_t luma_sum = 0;
    // std::array 元素数量固定，理论上不会为空；这里演示防御式检查，
    // 返回 0 表示提前正常退出。
    if(pixels.empty()){
        return 0;
    }
    // 用第一个像素初始化最值，再在遍历中逐步更新。
    std::uint8_t min_luma = pixels[0];
    std::uint8_t max_luma = pixels[0];
    // 范围 for 遍历每个像素；pixel 是值拷贝，1 字节的复制开销很小。
    for (const Pixel pixel : pixels)
    {
        luma_sum += pixel;
        // 发现更暗的像素就更新 min_luma。
        if (pixel < min_luma){
            min_luma = pixel;
        }
        // 发现更亮的像素就更新 max_luma。
        if (pixel > max_luma){
            max_luma = pixel;
        }
    }

    // 平均亮度 = 总和 / 数量；先转成 double 再做浮点除法，避免整数除法丢精度。
    const double average_luma =
        static_cast<double>(luma_sum) / static_cast<double>(pixels.size());
    // 下面输出统计结果；uint8_t 直接输出会被当作字符，所以先转成 int。

    std::cout << "Frame: " << kWidth << 'x' << kHeight
              << ", pixels=" << pixels.size() << '\n';
    std::cout << "Average luma: " << average_luma << '\n';
    std::cout << "Min_Luma:" << static_cast<int>(min_luma) << "\n";
    std::cout << "Max_Luma:" << static_cast<int>(max_luma) << "\n";

    // 曝光阈值：平均亮度低于 90 视为欠曝。
    constexpr double kUnderexposedThreshold = 90.0;
    if (average_luma < kUnderexposedThreshold)
    {
        std::cout << "Exposure status: underexposed\n";
    }
    else
    {
        std::cout << "Exposure status: acceptable\n";
    }

    // 程序正常结束，返回 0 表示成功。
    return 0;
}
