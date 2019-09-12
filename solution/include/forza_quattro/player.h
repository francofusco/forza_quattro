#ifndef FORZA_QUATTRO_PLAYER_H
#define FORZA_QUATTRO_PLAYER_H

#include <forza_quattro/board.h>

/* Base class defining the "interface" of a player. It mainly consists of a
 * method called "choose" that asks a player to make a move. Since the method
 * used to choose a column depends on the specific strategy adopted by the
 * player, it will be implemented by sub-classes.
 */
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
