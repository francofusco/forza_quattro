add_executable(solved_forza_quattro
  src/forza_quattro.cpp
  src/board.cpp
  src/player.cpp
  src/mouse_player.cpp
  src/random_player.cpp
)
target_include_directories(solved_forza_quattro PRIVATE include)
target_link_libraries(solved_forza_quattro piksel)
