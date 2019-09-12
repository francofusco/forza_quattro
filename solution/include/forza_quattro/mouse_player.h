#ifndef FORZA_QUATTRO_MOUSE_PLAYER_H
#define FORZA_QUATTRO_MOUSE_PLAYER_H

#include <forza_quattro/player.h>

class MousePlayer : public Player {
public:
  // Constructor, simply calls the constructor of the superclass.
  MousePlayer(Board& board);

  // Choose a place depending on the current mouse position.
  bool choose(unsigned int& col) override;

};

#endif
