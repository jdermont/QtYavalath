#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game
{
public:
    Game();
    bool isOver();
    int getFilled();
    bool isFilled(int move);
    int getWinner();
    void makeMove(int move);
    void undoMove();
    vector<int> getAvailableMoves();
    int getCurrentPlayer();
    void setGameNoHistory(Game *game);
    void changePlayer();
    string getState();
private:
    Board board;
    int currentPlayer;
    vector<int> lastMoves;
};

#endif // GAME_H
