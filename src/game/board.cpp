#include "board.h"

Board::Board() {


}

bool Board::isWinner(player_t player, move_t move) {
    uint64_t who = player == PLAYER_ONE ? oneBoard : twoBoard;
    for (auto & mask : pattern_win[move]) {
        if ((who & mask) == mask) {
            return true;
        }
    }
    return false;
}

bool Board::isLoser(player_t player, move_t move) {
    uint64_t who = player == PLAYER_ONE ? oneBoard : twoBoard;
    for (auto & mask : pattern_lose[move]) {
        if ((who & mask) == mask) {
            return true;
        }
    }
    return false;
}
