#include <forza_quattro/board.h>
#include <forza_quattro/player.h>
#include <stdexcept>

const int Board::CELL_SIZE = 80;
const int Board::CHIP_DIAMETER = 65;

Board::Board(
  unsigned int rows,
  unsigned int columns
)
: piksel::BaseApp(columns*CELL_SIZE, rows*CELL_SIZE, "Forza Quattro"), // call the constructor of the base class
  rows_(rows), // keep track of the number of rows and columns of the grid
  cols_(columns),
  grid_(rows_*cols_, Cell::EMPTY), // make sure that at least the memory is allocated
  red_player_(nullptr), // make sure that the pointers are invalid at first: they could
  yellow_player_(nullptr) // contain any (possibly invalid) address in the beginning
{
  // nothing to do here, we just needed to initialize few members
  // the rest will be done directly in "setup()"
}


Board::Board()
: Board(6,7) // constructor delegation
{
  // nothing to do here, we delegated the work to Board(uint,uint)
}


Board::Board(unsigned int side)
: Board(side,side) // constructor delegation
{
  // nothing to do here, we delegated the work to Board(uint,uint)
}


const unsigned int& Board::cols() const {
  return cols_;
}


const unsigned int& Board::rows() const {
  return rows_;
}


const Board::Cell& Board::cell(unsigned int r, unsigned int c) const {
  return grid_.at(r*cols_ + c);
}


Board::Cell& Board::cell(unsigned int r, unsigned int c) {
  return grid_.at(r*cols_ + c);
}


void Board::cellCenter(
  unsigned int r,
  unsigned int c,
  float& x,
  float& y
)
{
  x = 0.5*CELL_SIZE + c * CELL_SIZE;
  y = 0.5*CELL_SIZE + r * CELL_SIZE;
}


bool Board::next(unsigned int column, unsigned int& row) const {
  // starting from the bottom, try to find the first empty cell in a given column
  for(unsigned int r = rows_; r > 0; r--) {
    if(cell(r-1,column) == Cell::EMPTY) {
      // found it!
      row = r-1;
      return true;
    }
  }
  // loop completed: no empty spaces available
  return false;
}


void Board::setPlayers(Player& red, Player& yellow) {
  // prevent calls like 'setPlayers(p,p)'
  if(&red == &yellow)
    throw std::invalid_argument("The two players must be different");
  // assign players and colors
  red_player_ = &red;
  yellow_player_ = &yellow;
  red.setColor(Cell::RED);
  yellow.setColor(Cell::YELLOW);
}




void Board::setup() {
  // fill all the grid with empty cells
  for(auto& c : grid_)
    c = Cell::EMPTY;
  // red goes first
  red_ = true;
  // no one won yet
  winner_ = Cell::EMPTY;
  // do not show any preview yet
  preview_col_ = cols_;
  // reset mouse state
  mouse_pressed_ = false;
  // check that players have been assigned
  if(red_player_ == nullptr)
    throw std::runtime_error("Red player has not been assigned");
  if(yellow_player_ == nullptr)
    throw std::runtime_error("Yellow player has not been assigned");
  // tell the players that we are about to start the game, so that they can
  // reset their internal variables
  red_player_->start();
  yellow_player_->start();
}



void Board::draw(piksel::Graphics& g) {
  // call update() here, provided that no player won already
  if(winner_ == Cell::EMPTY)
    update();

  // blue background
  g.background(glm::vec4(0, 0, 1, 1));

  // draw the circles depending on the content of the grid
  float x,y;
  for(unsigned int r=0; r<rows_; r++) {
    for(unsigned int c=0; c<cols_; c++) {
      cellCenter(r, c, x, y);
      if(cell(r,c) == Cell::RED)
        g.fill(glm::vec4(1,0,0,1)); // red
      else if(cell(r,c) == Cell::YELLOW)
        g.fill(glm::vec4(1,1,0,1)); // yellow
      else
        g.fill(glm::vec4(1,1,1,1)); // white
      g.ellipse(x, y, CHIP_DIAMETER, CHIP_DIAMETER);
    }
  }

  // show next position, if given.
  unsigned int r;
  if(preview_col_ < cols_ && next(preview_col_,r)) {
    // the current column has a free cell: show where the circle would end up
    cellCenter(r, preview_col_, x, y);
    if(red_)
      g.fill(glm::vec4(0.7,0,0,1)); // dark red
    else
      g.fill(glm::vec4(0.7,0.5,0,1)); // dark yellow
    g.ellipse(x, y, CHIP_DIAMETER, CHIP_DIAMETER);
  }

  // We have a winner, display some text
  if(winner_ != Cell::EMPTY) {
    g.textSize(0.4*CELL_SIZE);
    g.fill(glm::vec4(0,0,0,1));
    g.text(std::string(winner_==Cell::RED ? "Red" : "Yellow") + " player won!", CELL_SIZE, CELL_SIZE);
  }

}


void Board::mouseMoved(int x, int y) {
  // store only the horizontal position, as we need to use it only for knowing
  // which column is being selected
  mx_ = x;
}


void Board::mousePressed(int) {
  // check if the game has to be reset
  if(winner_ != Cell::EMPTY) {
    setup();
    return;
  }

  // store the value
  mouse_pressed_ = true;
}


bool Board::mousePressed() {
  // if the mouse has been pressed, reset its state and return true
  if(mouse_pressed_) {
    mouse_pressed_ = false;
    return true;
  }

  // otherwise, just return false
  return false;
}


unsigned int Board::mouseColumn() const {
  return (unsigned int) (mx_/CELL_SIZE);
}



void Board::preview(unsigned int col) {
  // get the next available position
  unsigned int row;
  if(!next(col, row)) {
    // send an error if the colum is full
    throw std::invalid_argument("Request to preview in column with index " +
      std::to_string(col) + " but the column is full"
    );
  }

  // save the requested column for later
  preview_col_ = col;
}


unsigned int Board::count(
  Cell val, // identifier of the color
  unsigned int r, // current row
  unsigned int c, // current column
  int dir_r, // vertical direction to check (either 1 or -1)
  int dir_c, // horizontal direction to check (either 1 or -1)
  unsigned int num // how many circles have been counted so far
) const
{
  // if both directions are zero, we would end up in an infinite loop
  if(dir_r == 0 && dir_c == 0) {
    throw std::invalid_argument("In order to count consecutive chips, 'dir_r' "
      "and 'dir_c' cannot be both 0"
    );
  }

  // check that we can make the next step
  if( (dir_r < 0 && r < -dir_r) || (dir_r > 0 && r+dir_r >= rows_) )
    return num;
  if( (dir_c < 0 && c < -dir_c) || (dir_c > 0 && c+dir_c >= cols_) )
    return num;

  // evaluate next cell to be visited
  unsigned int next_row = r + dir_r;
  unsigned int next_col = c + dir_c;

  // if the next cell is not of the same value, exit
  if(cell(next_row, next_col) != val)
    return num;

  // keep counting recursively
  return count(val, next_row, next_col, dir_r, dir_c, num+1);
}



void Board::update() {
  // reset the preview column, it is player's duty to make a preview request
  preview_col_ = cols_;

  // alias storing the active player
  Player& p = red_ ? *red_player_ : *yellow_player_;

  // ask the player to choose; if no choice is made, exit
  unsigned int col;
  if(!p.choose(col))
    return;

  // can we fill the selected column?
  unsigned int row;
  if(!next(col, row)) {
    throw std::runtime_error("A player made an invalid choice by selecting "
      "column index " + std::to_string(col) + " (the column is full!)"
    );
  }

  // fill the column
  cell(row, col) = p.color();

  // count the maximum number of adjacent chips
  unsigned int adj = count(cell(row,col), row, col, 1, 0, 0) + count(cell(row,col), row, col, -1, 0, 0);
  adj = std::max(adj, count(cell(row,col), row, col, 0, 1, 0) + count(cell(row,col), row, col, 0, -1, 0));
  adj = std::max(adj, count(cell(row,col), row, col, 1, 1, 0) + count(cell(row,col), row, col, -1, -1, 0));
  adj = std::max(adj, count(cell(row,col), row, col, 1, -1, 0) + count(cell(row,col), row, col, -1, 1, 0));

  // the current cell is filled, so at least 3 neighbors are required to make 4 in a row
  if(adj >= 3)
    winner_ = p.color();

  // switch player for the next turn
  red_ = !red_;
}
