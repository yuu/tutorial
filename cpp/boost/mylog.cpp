#include "mylogger.hpp"

#include <boost/log/attributes/clock.hpp>

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>

// boost common
#include <boost/core/null_deleter.hpp>
#include <boost/make_shared.hpp>

// backend
#include <boost/log/sinks/text_ostream_backend.hpp>

// frontend
#include <boost/log/sinks/sync_frontend.hpp>
// format
#include <boost/log/expressions.hpp>

#include <boost/log/attributes/current_process_name.hpp>
#include <boost/log/support/date_time.hpp>

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
        r.add_attribute("ProcessID",
                        boost::log::attributes::current_process_id());
        r.add_attribute("Process",
                        boost::log::attributes::current_process_name());
        r.add_attribute("ThreadID",
                        boost::log::attributes::current_thread_id());
    }

    return std::move(r);
}

void init_log_system() {
    // バックエンドを生成
    using our_backend = boost::log::sinks::text_ostream_backend;
    auto backend = boost::make_shared<our_backend>();
    {
        boost::shared_ptr<std::ostream> stream_out(&std::cout,
                                                   boost::null_deleter());
        backend->add_stream(stream_out);

        // ログ書き出し時に自動的にフラッシュを行うように設定する。
        // バッファリングはされなくなるが、プログラムがクラッシュした場合には安定性が高い
        backend->auto_flush(true);
    }

    // フロントエンドを定義
    auto frontend =
        boost::make_shared<boost::log::sinks::synchronous_sink<our_backend>>(
            backend);

    // ログフォーマットを定義
    {
        using boost::log::expressions::format;
        using boost::log::expressions::format_date_time;
        using boost::log::expressions::attr;
        using boost::log::expressions::message;
        using ptime = boost::posix_time::ptime;
        using proc_id = boost::log::attributes::current_process_id;
        using thr_id = boost::log::attributes::current_thread_id;
        using proc_name = boost::log::attributes::current_process_name;
        frontend->set_formatter(
            format("%1%\t%2%\t%3%\t%4%\t[%5%]\t%6%\t%7%\t%8%\t%9%") %
            format_date_time<ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") %
            attr<std::string>("SrcFile") % attr<int>("RecordLine") %
            attr<std::string>("CurrentFunction") % neosuzu::severity % message %
            attr<proc_id::value_type>("ProcessID") %
            attr<thr_id::value_type>("ThreadID") %
            attr<proc_name::value_type>("Process"));
    }

    // ライブラリ側の定義を使うと以下な感じでも書けるしい。
    frontend->set_filter(neosuzu::severity >= neosuzu::debug);

    // ライブラリのコアに登録する
    boost::log::core::get()->add_sink(frontend);
}

}  // namespace neosuzu

// BOOST_LOG_SEVの戻り値は, basic_record_ostream
#define MY_GLOBAL_LOGGER(sv)                             \
    BOOST_LOG_SEV(neosuzu::glob_logger::get(), sv)       \
        << boost::log::add_value("RecordLine", __LINE__) \
        << boost::log::add_value("SrcFile", __FILE__)    \
        << boost::log::add_value("CurrentFunction", BOOST_CURRENT_FUNCTION)

// コード元は、以下。
// http://d.hatena.ne.jp/yamada28go/20140215/1392470561
int main() {
    neosuzu::init_log_system();

    MY_GLOBAL_LOGGER(neosuzu::info) << "foo";
    BOOST_LOG_SEV(neosuzu::glob_logger::get(), neosuzu::debug) << "foo";

    return 0;
}
