#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <stdint.h>

#define INF 2000000000

using namespace std;

class Move {
public:
    Move *parent;
    int player;
    int move;
    bool terminal;

    int32_t score;
    uint32_t games;

    vector<Move*> children;

    explicit Move(Move *parent, int player, int move) : parent(parent), player(player), move(move) {
        terminal = false;
        games = 0;
        score = 0;
    }

    bool operator < (const Move& move) const {
        double avg1 = score / (games+1e-3);
        double avg2 = move.score / (move.games+1e-3);
        return avg1 < avg2;
    }

    bool operator > (const Move& move) const {
        double avg1 = score / (games+1e-3);
        double avg2 = move.score / (move.games+1e-3);
        return avg1 > avg2;
    }

    virtual ~Move() { for (auto & m : children) { delete m; } }
};

#endif // MOVE_H
