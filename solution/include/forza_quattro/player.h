#ifndef FORZA_QUATTRO_PLAYER_H
#define FORZA_QUATTRO_PLAYER_H

#include <forza_quattro/board.h>

class Player {
public:
  // Creates a player and keep track of the board.
  Player(Board& board);

  // Destructor.
  virtual ~Player() = default;

  // Give a color to this player.
  void setColor(const Board::Cell& color);

  // Retrieve the color given to the player.
  inline const Board::Cell& color() const { return color_; }

  // Choose a column where to put the next item. Returns false if no choice is made.
  virtual bool choose(unsigned int& col) = 0;

  // Used to notify the player that we will reset the game.
  virtual void start() { }

protected:
  Board& board_; // the board to play on
  Board::Cell color_; // the color given to the player
};

#endif
