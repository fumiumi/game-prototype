#pragma once
#include <iostream>

namespace utils
{
#ifdef DEBUG
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "Assertion failed: " << message \
                      << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl; \
            if (std::uncaught_exceptions() > 0) \
            { \
                std::terminate(); \
            } \
            else { \
                std::abort(); \
            } \
        } \
    } while (false) // ループを一度だけ行うテクニック
#else
  #define ASSERT(condition, ...) do {} while (false) // 何もしない
#endif
}