#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

void init() {
    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info);
}

int main() {
    init();
    BOOST_LOG_TRIVIAL(trace) << "A trace servity message";
    BOOST_LOG_TRIVIAL(info) << "A info servity message";
    return 0;
}
