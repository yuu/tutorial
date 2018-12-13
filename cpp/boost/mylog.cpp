#include "mylogger.hpp"

#include <boost/log/attributes/clock.hpp>

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>

namespace neosuzu {

BOOST_LOG_GLOBAL_LOGGER_INIT(
    glob_logger, boost::log::sources::severity_logger_mt<severity_level>) {
    // ログレコードの属性を設定する
    auto r = boost::log::sources::severity_logger_mt<severity_level>();

    // [ログに含まれる属性を設定する]
    // 以下の共通属性定義関数で定義する事も可能である。
    // boost::log::add_common_attributes();

    // ここでは、独自に必要な属性の定義を行う
    {
        // タイムスタンプを設定する
        r.add_attribute("TimeStamp", boost::log::attributes::local_clock());
    }

    return std::move(r);
}

}  // namespace neosuzu

// BOOST_LOG_SEVの戻り値は, basic_record_ostream
#define MY_GLOBAL_LOGGER(sv)                             \
    BOOST_LOG_SEV(neosuzu::glob_logger::get(), sv)       \
        << boost::log::add_value("RecordLine", __LINE__) \
        << boost::log::add_value("SrcFile", __FILE__)    \
        << boost::log::add_value("CurrentFunction", BOOST_CURRENT_FUNCTION)

int main() {
    MY_GLOBAL_LOGGER(neosuzu::info) << "foo";

    return 0;
}
