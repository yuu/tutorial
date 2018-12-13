#include <boost/log/trivial.hpp>

int main() {
    BOOST_LOG_TRIVIAL(trace) << "A trace servity message";
    return 0;
}
