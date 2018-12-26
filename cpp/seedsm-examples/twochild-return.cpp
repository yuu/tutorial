#include "seedsm.h"

#include "util.h"

#include <ev++.h>
#include <iostream>

struct Policy1 {
    enum STATE {
        WAIT_A,
        WAIT_B,
        WAIT_RES,
        WAIT_RES_SKIP,
    };

    enum EVENT {
        TO_A,
        TO_B,
        TO_RES,
        TO_RES_CMD,
    };
};

DEFINE_EVENT(Policy1::TO_A)
DEFINE_EVENT(Policy1::TO_B)
DEFINE_EVENT(Policy1::TO_RES)
DEFINE_EVENT(Policy1::TO_RES_CMD)

struct A : public seedsm::StateMachine<Policy1> {
    using ST = Policy1::STATE;
    using EV = Policy1::EVENT;

    A(ev::loop_ref loop)
        : StateMachine("root", loop) {
        create_states({ST::WAIT_A, ST::WAIT_B});
        create_states(ST::WAIT_B, {ST::WAIT_RES, ST::WAIT_RES_SKIP});

        add_transition<EV::TO_A>(ST::WAIT_B, ST::WAIT_A);
        add_transition<EV::TO_B>(ST::WAIT_A, ST::WAIT_RES);
        add_transition<EV::TO_RES>(ST::WAIT_A, ST::WAIT_RES);
        add_transition<EV::TO_RES_CMD>(ST::WAIT_A, ST::WAIT_RES_SKIP);

        on_transition<EV::TO_A>(ST::WAIT_B, []{ std::cout << "[wait b] to [wait a]" << std::endl;});

        on_state_entered(ST::WAIT_A, [] { std::cout << "in a" << std::endl; });
        on_state_entered(ST::WAIT_B, [] { std::cout << "in b" << std::endl; });
        on_state_entered(ST::WAIT_RES,
                         [] { std::cout << "in wait res" << std::endl; });
        on_state_entered(ST::WAIT_RES_SKIP,
                         [] { std::cout << "in wait res skip" << std::endl; });
    }
};

int main() {
    using ST = Policy1::STATE;
    using EV = Policy1::EVENT;

    ev::dynamic_loop loop;
    A a(loop);

    a.start();
    a.send<EV::TO_RES>();
    a.send<EV::TO_A>();
    loop.run(0);

    return 0;
}
