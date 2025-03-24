#pragma once

#include "../lib/json.hpp"
#include "../lib/httplib.h"

using json = nlohmann::json;

class ConnectFour {
public:
    ConnectFour();
    void start();
    //friend void handleMove(const httplib::Request& req, httplib::Response& res);

private:
    httplib::Server svr;

};
