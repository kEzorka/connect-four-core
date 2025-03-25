#include "../include/connect-four.h"
#include <iostream>

void handleMove(const httplib::Request& req, httplib::Response& res) {
    auto request_data = json::parse(req.body);

    std::string player = request_data["player"];
    int column = request_data["column"];
    auto got_board = request_data["board"];

    std::string turn = EMPTY;
    if (player == "Yellow") {
        turn = PLAYER_1;
    } else {
        turn = PLAYER_2;
    }

    Board board = got_board;

    int yellow_move = (column + 1) % 7;

    int bestCol = pickBestMove(board, 6);
    // if (isValidLocation(board, bestCol)) {
    //     int row = getNextOpenRow(board, bestCol);
    //     dropPiece(board, row, bestCol, turn);
    // }

    // getting the next move

    json response_data = {
        {"player", "Yellow"},
        {"column", bestCol}
    };

    res.set_content(response_data.dump(), "application/json");

    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
}

ConnectFour::ConnectFour() {
    svr.Options("/move", [](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204;
    });
    
    svr.Post("/move", handleMove);
}

void ConnectFour::start() {
    svr.listen("0.0.0.0", 8080);
}
