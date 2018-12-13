#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

void init() {
    logging::add_file_log(
        keywords::format = "[%TimeStamp%]: %Message%");
    logging::core::get()->set_filter(
        logging::trivial::severity >= logging::trivial::info);
}

int main() {
    init();
    logging::add_common_attributes();

    BOOST_LOG_TRIVIAL(trace) << "A trace servity message";
    BOOST_LOG_TRIVIAL(info) << "A info servity message";
    return 0;
}
