#pragma once

#include "demangle.hpp"

#include <future>
#include <iostream>
#include <thread>
#include <ctime>

/* std::async object生成時に動き出す
 *
 *
 */

void print(std::future_status status) {
    if (std::future_status::ready == status) {
        std::cout << "future_status: ready" << std::endl;
    } else if (std::future_status::timeout == status) {
        std::cout << "future_status: timeout" << std::endl;
    } else if (std::future_status::deferred == status) {
        std::cout << "future_status: deferred" << std::endl;
    }
}

void async() {
    std::future<bool> f = std::async(std::launch::async, []() -> bool {
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return true;
    });

    std::cout << "async result:" << f.get() << std::endl;
    std::cout << "async func end" << std::endl;
}

// ready
void async1() {
    std::future<bool> f = std::async(std::launch::async, []() -> bool {
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return true;
    });

    std::cout << "wait_for 3" << std::endl;
    auto status = f.wait_for(std::chrono::seconds(5));
    print(status);
}

void async1_1() {
    std::future<bool> f = std::async(std::launch::async, []() -> bool {
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return true;
    });

    //  wait startup async thread
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::cout << "wait_for 3" << std::endl;
    auto status = f.wait_for(std::chrono::seconds(5));
    print(status);
}

// timeout
// timeoutしているが、return valueがf.get()で取得できる
// ない場合は false
void async2() {
    std::future<bool> f = std::async(std::launch::async, []() -> bool {
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        if (false)
            return true;
    });

    std::cout << "wait_for 2" << std::endl;
    auto status = f.wait_for(std::chrono::seconds(2));
    print(status);
    std::cout << "result:" << f.get() << std::endl;
}

// timeout
void async2_1() {
    std::future<bool> f = std::async(std::launch::async, []() -> bool {
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return true;
    });

    //  wait startup async thread
    //  1000だとready
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::cout << "wait_for 2" << std::endl;
    auto status = f.wait_for(std::chrono::seconds(2));
    print(status);
}

// 30秒待つ
// 30秒以内に終わるため、すぐ返ってくる
void async3() {
    std::future<bool> f = std::async(std::launch::async, []() -> bool {
        // event 待ち想定
        std::cout << "exec lambda" << std::endl;
        return true;
    });

    //  wait startup async thread
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::cout << "wait_for 30" << std::endl;
    auto status = f.wait_for(std::chrono::seconds(30));
    print(status);
    std::cout << "result:" << f.get() << std::endl;
}

// 10秒待つ
// reutnrしない場合
void async4() {
    std::future<void> f = std::async(std::launch::async, []() {
        // event 待ち想定
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(12));
    });

    //  wait startup async thread
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::cout << "wait_for 10" << std::endl;
    auto status = f.wait_for(std::chrono::seconds(10));
    print(status);
}


// wait_forの時間はcall時から?
void async5() {
    std::future<void> f = std::async(std::launch::async, []() {
        // event 待ち想定
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    });

    //  wait startup async thread
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    std::cout << "wait_for 10" << std::endl;
    auto start = std::chrono::system_clock::now();
    auto status = f.wait_for(std::chrono::seconds(10));
    auto end = std::chrono::system_clock::now();
    print(status);
    std::time_t t = std::chrono::system_clock::to_time_t(start);
    std::cout << std::ctime(&t) << std::endl;
    t = std::chrono::system_clock::to_time_t(end);
    std::cout << std::ctime(&t) << std::endl;
}

// 実行してからtimeoutを計測する
void async5_1() {
    std::future<void> f = std::async(std::launch::async, []() {
        // event 待ち想定
        std::cout << "exec lambda" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    });
    auto now = std::chrono::system_clock::now();
    auto abs_time = now + std::chrono::seconds(10);
    using sscrisk::demangle;
    std::cout << demangle(typeid(abs_time)) << std::endl;

    //  wait startup async thread
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    std::cout << "wait_for 10" << std::endl;
    auto start = std::chrono::system_clock::now();
    auto status = f.wait_until(abs_time);
    auto end = std::chrono::system_clock::now();
    print(status);

    std::time_t t = std::chrono::system_clock::to_time_t(start);
    std::cout << std::ctime(&t) << std::endl;
    t = std::chrono::system_clock::to_time_t(end);
    std::cout << std::ctime(&t) << std::endl;
}
