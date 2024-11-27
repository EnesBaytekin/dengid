#ifndef APP_MAIN_HPP
#define APP_MAIN_HPP

#include "app/i_app_abstraction.hpp"

class AppMain: public IAppAbstraction {
public:
    AppMain(IAppImplementation* _implementation):
        IAppAbstraction(_implementation) {}
    ~AppMain() = default;
    void setup() override;
    void update() override;
    void check_events() override;
};

#endif
