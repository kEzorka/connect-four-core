#include <iostream>
#include "../lib/json.hpp"
#include "../lib/httplib.h"

using json = nlohmann::json;

void handleMove(const httplib::Request& req, httplib::Response& res) {
    auto request_data = json::parse(req.body);

    std::string player = request_data["player"];
    int column = request_data["column"];
    auto board = request_data["board"];

    int yellow_move = (column + 1) % 7;
    // getting the next move

    json response_data = {
        {"player", "Yellow"},
        {"column", yellow_move}
    };

    res.set_content(response_data.dump(), "application/json");

    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

int main() {
    httplib::Server svr;

    svr.Post("/move", handleMove);

    std::cout << "Сервер запущен на порту 8080..." << std::endl;
    svr.Options("/move", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204;
    });
    svr.listen("0.0.0.0", 8080);
}
