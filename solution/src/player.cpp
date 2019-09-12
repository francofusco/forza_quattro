#include <forza_quattro/player.h>


Player::Player(Board& board)
: board_(board),
  color_(Board::Cell::EMPTY)
{

}


void Player::setColor(const Board::Cell& color) {
  color_ = color;
}
