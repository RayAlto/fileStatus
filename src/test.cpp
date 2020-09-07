#include "FileStatus.hpp"
#include <iostream>

int main(int argc, char const* argv[]) {
    std::cout << std::boolalpha << FileStatus("../../../vmware").isRegularFile() << std::noboolalpha << std::endl;
    return 0;
}