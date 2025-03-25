#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "../include/connect-four.h"

bool isValidLocation(const Board &board, int col) {
    return board[0][col] == EMPTY;
}

int getNextOpenRow(const Board &board, int col) {
    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][col] == EMPTY) {
            return row;
        }
    }
    return -1;
}

void dropPiece(Board &board, const int& row, const int& col, const std::string& piece) {
    board[row][col] = piece;
}

std::vector<int> getValidLocations(const Board &board) {
    std::vector<int> validLocations;
    for (int col = 0; col < COLS; ++col) {
        if (isValidLocation(board, col)) {
            validLocations.push_back(col);
        }
    }
    return validLocations;
}

bool winningMove(const Board &board, const std::string& piece) {
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            if (board[row][col] == piece && board[row][col+1] == piece &&
                board[row][col+2] == piece && board[row][col+3] == piece) {
                return true;
            }
        }
    }
    
    for (int col = 0; col < COLS; ++col) {
        for (int row = 0; row < ROWS - 3; ++row) {
            if (board[row][col] == piece && board[row+1][col] == piece &&
                board[row+2][col] == piece && board[row+3][col] == piece) {
                return true;
            }
        }
    }
    
    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            if (board[row][col] == piece && board[row-1][col+1] == piece &&
                board[row-2][col+2] == piece && board[row-3][col+3] == piece) {
                return true;
            }
        }
    }
    
    for (int row = 0; row < ROWS - 3; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            if (board[row][col] == piece && board[row+1][col+1] == piece &&
                board[row+2][col+2] == piece && board[row+3][col+3] == piece) {
                return true;
            }
        }
    }
    
    return false;
}

int evaluateWindow(const std::vector<std::string>& window, const std::string& piece) {
    int score = 0;
    std::string opp_piece = (piece == PLAYER_2 ? PLAYER_1 : PLAYER_2);
    int countPiece = 0, countOpp = 0, countEmpty = 0;
    
    for (std::string cell : window) {
        if (cell == piece) {
            ++countPiece;
        } else if (cell == opp_piece) {
            ++countOpp;
        } else if (cell == EMPTY) {
            ++countEmpty;
        }
    }
    
    if (countPiece == 4) {
        score += 10000;
    } else if (countPiece == 3 && countEmpty == 1) {
        score += 5;
    } else if (countPiece == 2 && countEmpty == 2) {
        score += 2;
    }
    if (countOpp == 3 && countEmpty == 1) {
        score -= 4;
    }
        
    return score;
}

int scorePosition(const Board &board, const std::string& piece) {
    int score = 0;
    
    int centerCol = COLS / 2;
    int centerCount = 0;
    for (int row = 0; row < ROWS; ++row) {
        if (board[row][centerCol] == piece) {
            ++centerCount;
        }
    }
    score += centerCount * 3;
    
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            std::vector<std::string> window;
            for (int i = 0; i < WINDOW_LENGTH; ++i) {
                window.push_back(board[row][col+i]);
            }
            score += evaluateWindow(window, piece);
        }
    }
    
    for (int col = 0; col < COLS; ++col) {
        for (int row = 0; row < ROWS - 3; ++row) {
            std::vector<std::string> window;
            for (int i = 0; i < WINDOW_LENGTH; ++i) {
                window.push_back(board[row+i][col]);
            }
            score += evaluateWindow(window, piece);
        }
    }
    
    for (int row = 3; row < ROWS; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            std::vector<std::string> window = { board[row][col], board[row-1][col+1], board[row-2][col+2], board[row-3][col+3] };
            score += evaluateWindow(window, piece);
        }
    }
    
    for (int row = 0; row < ROWS - 3; ++row) {
        for (int col = 0; col < COLS - 3; ++col) {
            std::vector<std::string> window = { board[row][col], board[row+1][col+1], board[row+2][col+2], board[row+3][col+3] };
            score += evaluateWindow(window, piece);
        }
    }
    
    return score;
}

bool isTerminalNode(const Board &board) {
    return winningMove(board, PLAYER_1) || winningMove(board, PLAYER_2) || getValidLocations(board).empty();
}

int alphaBeta(Board board, int depth, int alpha, int beta, bool maximizingPlayer) {
    std::vector<int> validLocations = getValidLocations(board);
    bool terminal = isTerminalNode(board);
    
    if (depth == 0 || terminal) {
        if (terminal) {
            if (winningMove(board, PLAYER_2)) {
                return INF;
            } else if (winningMove(board, PLAYER_1)) {
                return NEG_INF;
            } else { 
                return 0;
            }
        } else {
            return scorePosition(board, PLAYER_2);
        }
    }
    
    if (maximizingPlayer) {
        int value = NEG_INF;
        for (int col : validLocations) {
            int row = getNextOpenRow(board, col);
            Board boardCopy = board;
            dropPiece(boardCopy, row, col, PLAYER_2);
            int newScore = alphaBeta(boardCopy, depth - 1, alpha, beta, false);
            value = std::max(value, newScore);
            alpha = std::max(alpha, value);
            if (alpha >= beta) {
                break;
            }
        }
        return value;
    } else {
        int value = INF;
        for (int col : validLocations) {
            int row = getNextOpenRow(board, col);
            Board boardCopy = board;
            dropPiece(boardCopy, row, col, PLAYER_1);
            int newScore = alphaBeta(boardCopy, depth - 1, alpha, beta, true);
            value = std::min(value, newScore);
            beta = std::min(beta, value);
            if (alpha >= beta) {
                break;
            }
        }
        return value;
    }
}

int pickBestMove(Board board, int depth) {
    std::vector<int> validLocations = getValidLocations(board);
    int bestScore = NEG_INF;
    int bestCol = validLocations[0];
    
    for (int col : validLocations) {
        int row = getNextOpenRow(board, col);
        Board boardCopy = board;
        dropPiece(boardCopy, row, col, PLAYER_2);
        int score = alphaBeta(boardCopy, depth - 1, NEG_INF, INF, false);
        if (score > bestScore) {
            bestScore = score;
            bestCol = col;
        }
    }
    
    return bestCol;
}
