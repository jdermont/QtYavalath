#include "board.h"

Board::Board() {
    oneBoard = 0L;
    twoBoard = 0L;
}

vector<int> Board::getAvailableMoves() {
    uint64_t board = oneBoard | twoBoard;
    vector<int> moves; moves.reserve(61);
    for (int i = 0; i < 61; i++) {
        if (((board >> i) & 1) == 0) {
            moves.push_back(i);
        }
    }
    return moves;
}

void Board::makeMove(int player, int move) {
    if (player == PLAYER_ONE) {
        oneBoard ^= 1L << move;
    } else {
        twoBoard ^= 1L << move;
    }
}

void Board::undoMove(int player, int move) {
    if (player == PLAYER_ONE) {
        oneBoard ^= (1L << move);
    } else {
        twoBoard ^= (1L << move);
    }
}

bool Board::isFilled(int move) {
    long board = oneBoard | twoBoard;
    return ((board >> move) & 1) != 0;
}

void Board::setBoard(Board board) {
    oneBoard = board.oneBoard;
    twoBoard = board.twoBoard;
}

bool Board::isOver(int player, int move) {
    return isLoser(player, move) || (oneBoard | twoBoard) == 0x1fffffffffffffffL;
}

int Board::getWinner(int player, int move) {
    if (isWinner(player, move)) return player;
    if (isLoser(player, move)) return (player + 1) & 1;
    return PLAYER_NONE;
}

string Board::getState() {
    string state = "";
    for (int i=0;i<61;i++) {
        if (((oneBoard >> i) & 1) == 1) {
            state += to_string(i);
            state += ',';
        }
    }
    state += "|";
    for (int i=0;i<61;i++) {
        if (((twoBoard >> i) & 1) == 1) {
            state += to_string(i);
            state += ',';
        }
    }
    return state;
}

bool Board::isWinner(int player, int move) {
    uint64_t who = player == PLAYER_ONE ? oneBoard : twoBoard;
    for (auto & mask : pattern_win[move]) {
        if ((who & mask) == mask) {
            return true;
        }
    }
    return false;
}

bool Board::isLoser(int player, int move) {
    uint64_t who = player == PLAYER_ONE ? oneBoard : twoBoard;
    for (auto & mask : pattern_lose[move]) {
        if ((who & mask) == mask) {
            return true;
        }
    }
    return false;
}
