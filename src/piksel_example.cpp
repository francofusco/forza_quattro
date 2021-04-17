#include <piksel/baseapp.hpp>
#include <ctime>

// example application using piksel
class App : public piksel::BaseApp {
public:
  App() : piksel::BaseApp(640, 480, "Hello Piksel") {}

  // called once on startup
  void setup() override {
    // select random background color
    std::srand(time(NULL));
    double r = (std::rand() % 256)/255.;
    double g = (std::rand() % 256)/255.;
    double b = (std::rand() % 256)/255.;
    color_ = glm::vec4(r, g, b, 1);
  }

  // main loop function
  void draw(piksel::Graphics& g) override {
    // set background and draw a circle
    g.background(color_);
    g.ellipse(mouse_x_, mouse_y_, 60, 60);
  }

  // called whenever the mouse is moved
  void mouseMoved(int x, int y) override {
    mouse_x_ = x;
    mouse_y_ = y;
  }

private:
  float mouse_x_; // last known x-coordinate of the mouse
  float mouse_y_; // last known y-coordinate of the mouse
  glm::vec4 color_; // background color
};



int main() {
  // create the app and run it
  App app;
  app.start();
}
