#include <forza_quattro/board.h>
#include <forza_quattro/mouse_player.h>
#include <forza_quattro/random_player.h>

int main(int argc, char** argv) {
  // get number of rows and columns
  int rows = 6, cols = 7;
  if(argc > 1)
    rows = cols = std::atoi(argv[1]);
  if(argc > 2)
    cols = std::atoi(argv[2]);

  // change seed for pseudo-random numbers
  std::srand(time(nullptr));

  // create the game app
  Board game(rows, cols);

  // create the players
  MousePlayer p1(game);
  RandomPlayer p2(game);

  // assign players, then start
  game.setPlayers(p1, p2);
  game.start();
  return 0;
}
