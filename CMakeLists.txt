cmake_minimum_required(VERSION 3.1)
project(forza_quattro)
set(CMAKE_CXX_STANDARD 11)

# compile piksel
add_subdirectory(piksel)

# make piksel's headers visible to the compiled sources
include_directories(piksel/src)

# compile the example
add_executable(piksel_example src/piksel_example.cpp)
target_link_libraries(piksel_example piksel)

# compile the game
add_executable(forza_quattro
  src/forza_quattro_main.cpp
  src/board.cpp
  # src/other_file.cpp
  # etc.
)
target_include_directories(forza_quattro PUBLIC include)
target_link_libraries(forza_quattro piksel)

# give the option to build examples
option(BUILD_SOLUTIONS OFF)
if(${BUILD_SOLUTIONS})
  add_executable(solved_forza_quattro
    solution/src/forza_quattro.cpp
    solution/src/board.cpp
    solution/src/player.cpp
    solution/src/mouse_player.cpp
    solution/src/random_player.cpp
  )
  target_include_directories(solved_forza_quattro PRIVATE solution/include)
  target_link_libraries(solved_forza_quattro piksel)
  # add_subdirectory(solution)
endif(${BUILD_SOLUTIONS})
