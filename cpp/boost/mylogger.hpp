#pragma once

#include <boost/log/expressions/keyword.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>

namespace neosuzu {

enum severity_level {
    trace,
    debug,
    info,
    warning,
    error,
};

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level);

BOOST_LOG_GLOBAL_LOGGER(
    glob_logger, boost::log::sources::severity_logger_mt<severity_level>);

}  // namespace neosuzu
