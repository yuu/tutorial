// g++ -o sif sample-ifstm.cpp
#include <fstream>
#include <iostream>

/*
 * socat pty,raw,echo=0,link=output pty,raw,echo=0,link=input
 * echo 1 > input
 *
 * result:
 *  a
 *
 *
 * echo -en '\xDD\xCC\x80\x00\x00\x80' > input
 *
 * result:
 *  dd cc 80 0 0 80
 */
int main() {
    std::ifstream ifs;
    ifs.open("./output");
    for (;;) {
        uint8_t x = 0;
        ifs >> x;
        std::cout << std::hex << static_cast<uint32_t>(x) << std::endl;
    }

    return 0;
}
