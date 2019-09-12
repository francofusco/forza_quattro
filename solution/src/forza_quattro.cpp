#include <forza_quattro/board.h>
#include <forza_quattro/mouse_player.h>
#include <forza_quattro/random_player.h>

int main(int argc, char** argv) {
  int size = 7;
  if(argc > 1)
    size = std::atoi(argv[1]);
  Board game(size);
  MousePlayer p1(game);
  RandomPlayer p2(game);
  game.setPlayers(p1, p2);
  game.start();
  return 0;
}
