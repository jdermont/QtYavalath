# QtYavalath
Yavalath application written in QT

### Stub implementation of AI

MCTS AI for Yavalath. From "vanilla" MCTS it differs:

* it uses MCTS solver
* it avoid losing moves if possible (move selection as well in rollouts/simulations)
* it uses winning moves if possible (move selection as well in rollouts/simulations)

Those simple things greatly enhance the strength. More enchancement incoming after GUI complete, i.e. opening books, RAVE, some heuristics for progressive bias, pattern matching.
