## C++ assignment for the ARPRO / PROAV courses at Centrale Nantes.

<p align="center">
  <a><img alt="f4" src="./latex/f4.png" width="300"></a>
</p>

- **Goal**: implement the game *Four in a Row*
- **Topics**: classes & inheritance
- **Instructions**: have a look at `latex/forza_quattro.pdf`
- **Dependencies**:
  - CMake >= 3.12
  - [piksel](https://github.com/bernhardfritz/piksel)

To compile and run the solution:

```
git clone --recursive https://github.com/bernhardfritz/piksel.git
mkdir build && cd build
cmake .. -DBUILD_SOLUTIONS=ON
make
./solution/solved_forza_quattro
```

To build the web-application, install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) using:

```
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk/
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

Then, compile almost as above:

```
mkdir build && cd build
emcmake cmake .. -DBUILD_SOLUTIONS=ON
emmake make
```
