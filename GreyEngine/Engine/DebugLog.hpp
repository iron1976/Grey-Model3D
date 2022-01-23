#pragma once
#include <stdexcept>
#include <iostream>

#define print(Description) std::cout << Description << "\n";

#define LOGBREAK(Description) \
    std::cout << "\n[ERROR]" << __FILE__ << ":" << __LINE__ << ":\n" << Description; \
    __debugbreak()

#define LOGWARNING(Description) \
    std::cout << "\n[WARNING]" << __FILE__ << ":" << __LINE__ << ":\n" << Description;

