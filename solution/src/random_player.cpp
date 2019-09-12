#include <forza_quattro/random_player.h>


RandomPlayer::RandomPlayer(Board& board)
: Player(board)
{

}


bool RandomPlayer::choose(unsigned int& col) {
  // get a list of all columns in which we can insert a chip
  unsigned int r;
  std::vector<unsigned int> cols;
  for(unsigned int c=0; c<board_.cols(); c++) {
    if(board_.next(c,r))
      cols.push_back(c);
  }

  // if no columns are available anymore, exit
  if(cols.size() == 0)
    return false;

  // pick a column randomly
  col = cols[std::rand() % cols.size()];
  return true;
}
