#include "cpu.h"

Cpu::Cpu()
{
    auto now = high_resolution_clock::now();
    auto nanos = duration_cast<nanoseconds>(now.time_since_epoch()).count();
    seed = 123456969ULL * (uint64_t)nanos + (uint64_t)(&now);
    simulationGame = new Game();
}


void Cpu::setPlayer(int player) {
    this->player = player;
}

int Cpu::getPlayer() {
    return player;
}

void Cpu::setGame(Game *game) {
    this->game = game;
}

Move* Cpu::getBestMove(long timeInMicro/*, vector<Para> & pary*/) {
    auto start = high_resolution_clock::now();
    vector<Move*> moves = generateMoves(nullptr,0);

    games = 0;

    provenEnd = false;

    long duration = duration_cast<microseconds>( high_resolution_clock::now() - start).count();
    while (!provenEnd && duration < timeInMicro) {
        selectAndExpand(moves,games+1,0);
        games++;
        duration = duration_cast<microseconds>( high_resolution_clock::now() - start).count();
    }

    sort(moves.begin(),moves.end(), [](const Move *a, const Move *b) -> bool
    {
        double avg1 = a->score / (a->games+1e-3);
        double avg2 = b->score / (b->games+1e-3);

        return avg1 > avg2;
    });

    for (int i=1;i<moves.size();i++) {
        delete moves[i];
    }

    return moves[0];
}

uint64_t Cpu::nextInt(uint64_t n) {
    seed ^= seed << 13;
    seed ^= seed >> 7;
    seed ^= seed << 17;
    return seed % n;
}

void Cpu::selectAndExpand(vector<Move*> & moves, int games, int level) {
    vector<int> indexes;
    double maxArg = -2 * INF;
    double a,b;
    double logCache = log(games);
    for (size_t i=0; i < moves.size(); i++) {
        Move *move = moves[i];
        if (move->terminal) {
            a = (double)move->score / move->games;
            b = 0.0;
        } else if (move->games == 0) {
            a = 1000.0;
            b = 1000.0;
        } else {
            a = (double)move->score / move->games;
            b = CEXP * sqrt(logCache / move->games);
        }

        if (a + b > maxArg) {
            maxArg = a + b;
            indexes.clear();
            indexes.push_back(i);
        } else if (a + b == maxArg) {
            indexes.push_back(i);
        }
    }
    Move *move = moves[indexes[nextInt(indexes.size())]];
    if (move->terminal) {
        move->games += 1;
        if (move->score == INF) {
            if (level == 0) {
                provenEnd = true;
                return;
            }
            Move *parent = move->parent;
            if (parent != nullptr) {
                parent->score = -INF;
                parent->games++;
                parent->terminal = true;
                parent = parent->parent;
            }
            while (parent != nullptr) {
                parent->score += parent->player == move->player ? 1 : -1;
                parent->games++;
                parent = parent->parent;
            }
        } else {
            bool allChildrenTerminal = true;
            int maxScore = -INF;
            for (auto & m : moves) {
                maxScore = max(maxScore,m->score);
                if (!m->terminal) {
                    allChildrenTerminal = false;
                    break;
                }
            }
            Move *parent = move->parent;
            if (allChildrenTerminal) {
                if (level == 0) {
                    provenEnd = true;
                    return;
                }
                if (maxScore == -INF) {
                    if (parent != nullptr) {
                        parent->score = INF;
                        parent->games++;
                        parent->terminal = true;
                        parent = parent->parent;
                    }
                    if (parent != nullptr) {
                        parent->score = -INF;
                        parent->games++;
                        parent->terminal = true;
                        parent = parent->parent;
                    }
                    while (parent != nullptr) {
                        parent->score += parent->player == move->player ? -1 : 1;
                        parent->games++;
                        parent = parent->parent;
                    }
                } else {
                    if (parent != nullptr) {
                        parent->games++;
                        parent->score = 0;
                        parent->terminal = true;
                        parent = parent->parent;
                    }
                    while (parent != nullptr) {
                        parent->score += 0;
                        parent->games++;
                        parent = parent->parent;
                    }
                }
            } else {
                if (move->score == -INF) {
                    while (parent != nullptr) {
                        parent->score += parent->player == move->player ? -1 : 1;
                        parent->games++;
                        parent = parent->parent;
                    }
                } else {
                    move->score += 0;
                    while (parent != nullptr) {
                        parent->score += 0;
                        parent->games++;
                        parent = parent->parent;
                    }
                }
            }
        }
        return;
    }
    game->makeMove(move->move);
    if (move->games > 0) {
        if (move->children.size() == 0) {
            move->children = generateMoves(move, level+1);
        }
        selectAndExpand(move->children, move->games+1, level+1);
    } else {
        int score = simulateOneGame(move->player);
        move->score = score;
        move->games = 1;

        Move *parent = move->parent;
        while (parent != nullptr) {
            parent->score += parent->player == move->player ? score : -score;
            parent->games++;
            parent = parent->parent;
        }
    }
    game->undoMove();
}

vector<Move*> Cpu::generateMoves(Move *parent, int level) {
    vector<int> movesNum = game->getAvailableMoves();
    int player = game->getCurrentPlayer();
    vector<Move*> moves; moves.reserve(movesNum.size());
    for (auto & moveNum : movesNum) {
        game->makeMove(moveNum);
        if (game->isOver()) {
            int winner = game->getWinner();
            if (winner == player) {
                Move *move = new Move(parent,player,moveNum);
                move->score = INF;
                move->games = 1;
                move->terminal = true;
                moves.push_back(move);
                game->undoMove();
                return moves;
            } else if (winner == PLAYER_NONE) {
                Move *move = new Move(parent,player,moveNum);
                move->score = 0;
                move->games = 1;
                move->terminal = true;
                moves.push_back(move);
            } else if (moves.size() == 0) {
                Move *move = new Move(parent,player,moveNum);
                move->score = -INF;
                move->games = 1;
                move->terminal = true;
                moves.push_back(move);
            }
        } else {
            moves.push_back(new Move(parent,player,moveNum));
        }
        game->undoMove();
    }
    return moves;
}

int Cpu::simulateOneGame(int forPlayer) {
    simulationGame->setGameNoHistory(game);

    moves = simulationGame->getAvailableMoves();

    while (!simulationGame->isOver()) {
        int n = 0;
        int player = simulationGame->getCurrentPlayer();
        for (int move : moves) {
            if (simulationGame->isFilled(move)) continue;
            simulationGame->makeMove(move);
            if (simulationGame->isOver()) {
                int winner = simulationGame->getWinner();
                if (winner == player) {
                    return winner == forPlayer ? 1 : -1;
                } else if (winner == PLAYER_NONE) {
                    moves2[n++] = move;
                }
            } else {
                moves2[n++] = move;
            }
            simulationGame->undoMove();
        }
        if (n > 0) {
            int move = moves2[nextInt(n)];
            simulationGame->makeMove(move);
        } else {
            int move = moves[nextInt(moves.size())];
            simulationGame->makeMove(move);
        }
    }

    int winner = simulationGame->getWinner();
    if (winner == forPlayer) {
        return 1;
    } else if (winner == PLAYER_NONE) {
        return 0;
    } else {
        return -1;
    }
}
