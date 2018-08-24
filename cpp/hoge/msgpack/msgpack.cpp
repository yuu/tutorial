#include <msgpack.hpp>

#include <iostream>
#include <sstream>
#include <string>

int main()
{
    msgpack::type::tuple<int, bool, std::string> src(1, true, "example");

    std::stringstream buffer;
    msgpack::pack(buffer, src);

    buffer.seekg(0);

    std::string str(buffer.str());
    msgpack::object_handle oh =
        msgpack::unpack(str.data(), str.size());

    msgpack::object deserialized = oh.get();
    std::cout << deserialized << std::endl;

    msgpack::type::tuple<int, bool, std::string> dst;
    deserialized.convert(dst);

    printf("deserialzed convert to arg1: %d arg2: %d arg3: %s\n", std::get<0>(dst), std::get<1>(dst), std::get<2>(dst).c_str());

    return 0;
}
