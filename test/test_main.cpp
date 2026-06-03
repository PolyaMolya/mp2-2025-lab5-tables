// test_main.cpp
// Минимальная версия для запуска Google тестов

#include <gtest.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}