# CMake 构建脚本：声明这是一个名为 first_frame 的 C++ 可执行程序。
# 典型用法：
#   cd lessons/01_first_frame
#   cmake -S . -B build
#   cmake --build build

# 最低要求的 CMake 版本，低于 3.16 会直接报错。
cmake_minimum_required(VERSION 3.16)

# project 声明项目名称和使用的语言；LANGUAGES CXX 表示只用 C++。
project(first_frame LANGUAGES CXX)

# 这一课只有 main.cpp 一个源文件，直接编译成可执行文件 first_frame。
add_executable(first_frame main.cpp)

# 要求按 C++17 标准编译。
target_compile_features(first_frame PRIVATE cxx_std_17)

# 按不同编译器打开更严格的警告，帮助尽早发现潜在问题。
if(MSVC)
    # MSVC：/W4 是较高的警告级别；/permissive- 要求更严格的标准符合性。
    target_compile_options(first_frame PRIVATE /W4 /permissive-)
else()
    # GCC/Clang：-Wall -Wextra -Wpedantic 打开常规警告，
    # -Wconversion 会警告有潜在信息丢失的类型转换（例如 double 转 int）。
    target_compile_options(first_frame PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
    )
endif()
