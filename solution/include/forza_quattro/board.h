#ifndef FORZA_QUATTRO_BOARD_H
#define FORZA_QUATTRO_BOARD_H

#include <piksel/baseapp.hpp>

// This is what we call a "forward declaration" of a class: we promise the
// compiler that, sooner or later, we will provide detailed information about
// it, ie, we will provide a piece of code with its full definition!.
class Player;

/* Our class inherits from Piksel's BaseApp class, and therefore it is a
 * "runnable" program. It will thus need to override some of the methods from
 * the base class, in particular to:
 * - Initialize the app;
 * - Handle the main loop / render the grid;
 * - Process user's input, in our case just the mouse.
 */
class Board : public piksel::BaseApp {
public:
  static const int CELL_SIZE; // size of a single grid cell
  static const int CHIP_DIAMETER; // size of the circle within a cell

  // Simple enum to define the state of a cell; it can be used also to
  // distinguish between players colors.
  enum class Cell {
    EMPTY,
    RED,
    YELLOW
  };

  // Default constructor: 6-by-7 grid.
  Board();

  // Use a NxN squared grid.
  Board(unsigned int side);

  // Constructor that accepts a given grid size.
  Board(unsigned int rows, unsigned int columns);

  // Returns the number of columns of the grid.
  const unsigned int& cols() const;

  // Returns the number of rows of the grid.
  const unsigned int& rows() const;

  // Accessor to the grid codes.
  const Cell& cell(unsigned int r, unsigned int c) const;

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
  // Setter for the grid codes.
  Cell& cell(unsigned int r, unsigned int c);

  // Given the row and column of a cell, evaluates the (x,y) coordinates of its
  // center, ie, in Piksel's canva.
  void cellCenter(
    unsigned int r,
    unsigned int c,
    float& x,
    float& y
  );

  // Called when the mouse is moved. Overrides piksel::BaseApp::mouseMoved.
  void mouseMoved(int x, int y) override;

  // Called when the mouse is pressed. Overrides piksel::BaseApp::mousePressed.
  void mousePressed(int button) override;

  // Called once on startup. Overrides piksel::BaseApp::setup.
  void setup() override;

  // Main loop function. It asks players to make a move and renders the grid.
  // Overrides piksel::BaseApp::draw.
  void draw(piksel::Graphics& g) override;

  // Auxiliary function that will ask the current player to make a choice.
  void update();

  // Gives the number of adjacent circles in one direction.
  unsigned int count(
    Cell val, // identifier of the color
    unsigned int r, // current row
    unsigned int c, // current column
    int dir_r, // vertical direction to check (either 1 or -1)
    int dir_c, // horizontal direction to check (either 1 or -1)
    unsigned int num // how many circles have been counted so far
  ) const;

  const unsigned int rows_, cols_; // grid size
  std::vector<Cell> grid_; // grid values
  bool red_; // if true, red plays; if false, yellow plays
  float mx_; // last known horizontal position of the mouse
  bool mouse_pressed_; // stores the state of the mouse
  unsigned int preview_col_; // stores information about a preview request
  Cell winner_; // who won the game
  unsigned int free_cells_; // used to check if there is a "draw"
  Player* red_player_; // first player
  Player* yellow_player_; // second player
};

#endif
