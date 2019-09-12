#include <piksel/baseapp.hpp>

class App : public piksel::BaseApp {
public:
  App() : piksel::BaseApp(640, 480, "Hello Piksel") {}

  // called one on startup
  void setup() {
    auto h2rgb = [](double t) {
      if(t < 0) t += 1;
      else if(t > 1) t -= 1;
      if(t < 1/6.) return 6*t;
      if(t < 1/2.) return 1.;
      if(t < 2/3.) return (2/3.-t)*6;
      return 0.;
    };
    std::srand(time(NULL));
    double h = (std::rand() % 256)/255.;
    color_ = glm::vec4(h2rgb(h+1./3), h2rgb(h), h2rgb(h-1./3), 1);
  }

  // main loop function
  void draw(piksel::Graphics& g) override {
    g.background(color_);
    g.rect(50, 50, 100, 100);
    g.ellipse(mouse_x_, mouse_y_, 60, 60);
  }

  // event-driven function
  void mouseMoved(int x, int y) override {
    mouse_x_ = x;
    mouse_y_ = y;
  }

private:
  float mouse_x_; // last known x-coordinate of the mouse
  float mouse_y_; // last known y-coordinate of the mouse
  glm::vec4 color_;
};



int main() {
  App app;
  app.start();
}
