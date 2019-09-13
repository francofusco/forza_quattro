cmake_minimum_required(VERSION 3.1)
project(forza_quattro)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(piksel)

add_executable(piksel_example src/piksel_example.cpp)
target_include_directories(piksel_example PUBLIC piksel/src)
target_link_libraries(piksel_example piksel)

add_library(forza_quattro
  src/board.cpp
  src/player.cpp
  src/mouse_player.cpp
  src/random_player.cpp
)
target_include_directories(forza_quattro PUBLIC piksel/src PUBLIC include)
target_link_libraries(forza_quattro piksel)

add_executable(play_forza_quattro src/forza_quattro.cpp)
target_include_directories(play_forza_quattro PUBLIC piksel/src PUBLIC include)
target_link_libraries(play_forza_quattro forza_quattro)
