#ifndef FORZA_QUATTRO_RANDOM_PLAYER_H
#define FORZA_QUATTRO_RANDOM_PLAYER_H

#include <forza_quattro/player.h>

class RandomPlayer : public Player {
public:
  // Constructor, simply calls the constructor of the superclass.
  RandomPlayer(Board& board);

  // Randomly choose a column.
  bool choose(unsigned int& col) override;
};

#endif
