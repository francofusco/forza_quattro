#include <forza_quattro/mouse_player.h>


MousePlayer::MousePlayer(Board& board)
: Player(board)
{

}


bool MousePlayer::choose(unsigned int& col) {
  // get currently selected column
  col = board_.mouseColumn();

  // if the column is not a valid index, exit
  if(col == board_.cols())
    return false;

  // make sure that there is room in the selected column
  unsigned int r;
  if(!board_.next(col, r))
    return false;

  // the mouse has been pressed, so this is our choice
  if(board_.mousePressed())
    return true;

  // the mouse has yet to be pressed: only show a preview
  board_.preview(col);
  return false;
}
