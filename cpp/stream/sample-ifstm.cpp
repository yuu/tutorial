// g++ -o sif sample-ifstm.cpp
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <istream>
#include <iostream>

#include <ext/stdio_filebuf.h>

void standard_filebuf() {
    constexpr auto path = "./output";
    std::filebuf fb;
    fb.open(path, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
    std::iostream ifs(&fb);
    ifs << "0xdd";
    for (;;) {
        uint8_t x = 0;
        ifs >> x;
        std::cout << std::hex << static_cast<uint32_t>(x) << std::endl;
    }
}

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
    constexpr auto path = "./output";
    const auto fd = ::open(path, O_RDWR | O_APPEND);

    __gnu_cxx::stdio_filebuf<char> fd_file_buf(fd, std::ios_base::in | std::ios_base::binary);
    std::istream ifs(&fd_file_buf);
    for (;;) {
        uint8_t x = 0;
        ifs >> x;
        std::cout << std::hex << static_cast<uint32_t>(x) << std::endl;
    }

    return 0;
}
