#ifndef MAIN_APP_HPP
#define MAIN_APP_HPP

#include "app_design.hpp"

class MainApp : public App<MainApp> {
private:
public:
    MainApp() = default;
    ~MainApp() = default;
    void start_up();
    void update();
};

#endif