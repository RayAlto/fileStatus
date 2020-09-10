#include "FileStatus.hpp"
#include <iostream>

int main(int argc, char const* argv[]) {
    std::cout << std::boolalpha
              << FileStatus("../shit").isRegularFile()
              << std::noboolalpha
              << std::endl;
    return 0;
}