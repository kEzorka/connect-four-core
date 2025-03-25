#pragma once

#include "../lib/json.hpp"
#include "../lib/httplib.h"

using json = nlohmann::json;
typedef std::vector<std::vector<std::string>> Board;

constexpr std::string EMPTY = "";
constexpr std::string PLAYER_1 = "Red";
constexpr std::string PLAYER_2 = "Yellow";

constexpr int ROWS = 6;
constexpr int COLS = 7;
constexpr int WINDOW_LENGTH = 4;
constexpr int INF = INT_MAX;
constexpr int NEG_INF = INT_MIN;

bool isValidLocation(const Board &board, int col);
int getNextOpenRow(const Board &board, int col);
void dropPiece(Board &board, const int& row, const int& col, const std::string& piece);
std::vector<int> getValidLocations(const Board &board);
bool winningMove(const Board &board, const std::string& piece);
int evaluateWindow(const std::vector<std::string>& window, const std::string& piece);
int scorePosition(const Board &board, const std::string& piece);
bool isTerminalNode(const Board &board);
int alphaBeta(Board board, int depth, int alpha, int beta, bool maximizingPlayer);
int pickBestMove(Board board, int depth);

class ConnectFour {
public:
    ConnectFour();
    void start();

private:
    httplib::Server svr;

};
