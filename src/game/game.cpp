#include "game.h"

Game::Game()
{
    currentPlayer = PLAYER_ONE;
}

bool Game::isOver() {
    return !lastMoves.empty() && board.isOver((currentPlayer+1)&1, lastMoves[lastMoves.size()-1]);
}

int Game::getFilled() {
    return lastMoves.size();
}

bool Game::isFilled(int move) {
    return board.isFilled(move);
}

int Game::getWinner() {
    return board.getWinner((currentPlayer+1)&1, lastMoves[lastMoves.size()-1]);
}

void Game::makeMove(int move) {
    board.makeMove(currentPlayer, move);
    currentPlayer = (currentPlayer+1)&1;
    lastMoves.push_back(move);
}

void Game::undoMove() {
    board.undoMove((currentPlayer+1)&1, lastMoves[lastMoves.size()-1]);
    currentPlayer = (currentPlayer+1)&1;
    lastMoves.pop_back();
}

vector<int> Game::getAvailableMoves() {
    return board.getAvailableMoves();
}

int Game::getCurrentPlayer() {
    return currentPlayer;
}

void Game::setGameNoHistory(Game *game) {
    board.setBoard(game->board);
    currentPlayer = game->currentPlayer;
    lastMoves.clear();
    if (!game->lastMoves.empty()) lastMoves.push_back(game->lastMoves[game->lastMoves.size()-1]);
}

void Game::changePlayer() {
    currentPlayer = (currentPlayer+1)%2;
}

string Game::getState() {
    return board.getState();
}
