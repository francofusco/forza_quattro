#ifndef PIKSEL_FORZA_QUATTRO
#define PIKSEL_FORZA_QUATTRO

#include <piksel/baseapp.hpp>

class ForzaQuattro : public piksel::BaseApp {
public:
  // Default constructor: 7-by-7 grid
  ForzaQuattro() : ForzaQuattro(7,7) { }

  // Use a NxN squared grid
  ForzaQuattro(unsigned int side) : ForzaQuattro(side,side) { }

  // Constructor that accepts a given grid size.
  ForzaQuattro(unsigned int rows, unsigned int columns);

  // called once on startup
  void setup() override;

  // Main loop function
  void draw(piksel::Graphics& g) override;

  // Called when the mouse is pressed
  void mousePressed(int button) override;

  // Called when the mouse is moved
  void mouseMoved(int x, int y) override {
    mx_ = x;
    my_ = y;
  }

  static const int CELL_SIZE; // size of a single grid cell
  static const int CELL_DIAMETER; // size of the circle within a cell

  enum class Cell {
    EMPTY,
    RED,
    YELLOW
  };

  // Accessor to the grid codes.
  inline const Cell& cell(unsigned int r, unsigned int c) const { return grid_[r*cols_ + c]; }

private:
  // Setter for the grid codes.
  inline Cell& cell(unsigned int r, unsigned int c) { return grid_[r*cols_ + c]; }

  // Given a column, tell in which row we could insert a circle. Returns false if the column is full.
  bool next(unsigned int column, unsigned int& row) const;

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
  float mx_, my_; // last known position of the mouse
  Cell winner_;

};

#endif
