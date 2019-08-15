#ifndef CPU_H
#define CPU_H

#include "move.h"
#include "../game/game.h"

#include <chrono>
#include <algorithm>
#include <cmath>

#define CEXP (2*sqrt(2))

using namespace std::chrono;

class Cpu
{
public:
    Cpu();

    void setPlayer(int player);
    int getPlayer();
    void setGame(Game *game);
    Move* getBestMove(long timeInMicro);

private:
    int player;
    Game *game;

    // for simulation games
    Game *simulationGame;
    vector<int> moves;
    int moves2[61] = {};

    int games;
    bool provenEnd;

    uint64_t seed;

    uint64_t nextInt(uint64_t n);
    vector<Move*> generateMoves(Move *parent, int level);
    void selectAndExpand(vector<Move*> & moves, int games, int level);
    int simulateOneGame(int forPlayer);
};

#endif // CPU_H
