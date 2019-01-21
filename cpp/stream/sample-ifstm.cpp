// g++ -o sif sample-ifstm.cpp
#include <fstream>
#include <iostream>

/*
 * socat pty,raw,echo=0,link=output pty,raw,echo=0,link=input
 * echo 1 > input
 *
 * result:
 *  a
 */
int main() {
    std::ifstream ifs;
    ifs.open("./output");
    for (;;) {
        uint8_t x = 0;
        ifs >> x;
        std::cout << x << std::endl;
    }

    return 0;
}
