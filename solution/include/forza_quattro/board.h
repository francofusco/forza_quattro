#ifndef FORZA_QUATTRO_BOARD_H
#define FORZA_QUATTRO_BOARD_H

#include <piksel/baseapp.hpp>

// This is what we call a "forward declaration" of a class: we promise the
// compiler that, sooner or later, we will provide detailed information about
// it, ie, we will provide a piece of code with its full definition!.
class Player;

class Board : public piksel::BaseApp {
public:
  // Default constructor: 6-by-7 grid.
  Board();

  // Use a NxN squared grid.
  Board(unsigned int side);

  // Constructor that accepts a given grid size.
  Board(unsigned int rows, unsigned int columns);

  static const int CELL_SIZE; // size of a single grid cell
  static const int CELL_DIAMETER; // size of the circle within a cell

  // Simple enum to define the state of a cell; it can be used also to
  // distinguish between players colors.
  enum class Cell {
    EMPTY,
    RED,
    YELLOW
  };

  // Returns the number of columns of the grid.
  inline const unsigned int& cols() const { return cols_; }

  // Returns the number of rows of the grid.
  inline const unsigned int& rows() const { return rows_; }

  // Accessor to the grid codes.
  inline const Cell& cell(unsigned int r, unsigned int c) const { return grid_[r*cols_ + c]; }

  // Given a column, tell in which row we could insert a circle. Returns false if the column is full.
  bool next(unsigned int column, unsigned int& row) const;

  // Allows to visualize a move without making it.
  void preview(unsigned int col);

  // Returns the index of the column pointed by the mouse.
  unsigned int mouseColumn() const;

  // Returns true if the mouse has been pressed since last call to this method.
  bool mousePressed();

  // Keep track of the two players, also giving them a color.
  void setPlayers(Player& red, Player& yellow);

private:
  // Called once on startup.
  void setup() override;

  // Main loop function. It asks players to make a move and renders the grid.
  void draw(piksel::Graphics& g) override;

  // Called when the mouse is pressed.
  void mousePressed(int button) override;

  // Called when the mouse is moved.
  void mouseMoved(int x, int y) override {
    mx_ = x;
  }

  // Auxiliary function that will ask the current player to make a choice.
  void update();

  // Setter for the grid codes.
  inline Cell& cell(unsigned int r, unsigned int c) { return grid_[r*cols_ + c]; }

  // Given the row and column of a cell, evaluates the (x,y) coordinates of its center
  inline void cell_center(
    unsigned int r,
    unsigned int c,
    float& x,
    float& y
  )
  {
    x = 0.5*CELL_SIZE + c * CELL_SIZE;
    y = 0.5*CELL_SIZE + r * CELL_SIZE;
  }

  // gives the number of adjacent circles in one direction
  unsigned int count(
    Cell val, // identifier of the color
    unsigned int r, // current row
    unsigned int c, // current column
    int dir_r, // vertical direction to check (either 1 or -1)
    int dir_c, // horizontal direction to check (either 1 or -1)
    unsigned int num // how many circles have been counted so far
  ) const;

  const unsigned int rows_, cols_; // grid size
  std::vector<Cell> grid_; // grid codes
  bool red_; // if true, red plays; if false, yellow plays
  float mx_; // last known position of the mouse
  bool mouse_pressed_; // stores the state of the mouse
  unsigned int preview_col_; // stores information about a preview request
  Cell winner_; // who won the game
  Player* red_player_; // first player
  Player* yellow_player_; // second player
};

#endif
