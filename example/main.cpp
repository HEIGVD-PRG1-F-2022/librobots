#include <iostream>
#include <librobots.h>
#include <vector>

using namespace std;

class MyRobot : public Robot {
  size_t width, height, energy, power;

public:
  MyRobot() : width(0), height(0), energy(0), power(0){};

  void set_config(size_t width_init, size_t height_init,
                          unsigned energy_init, unsigned power_init) override {
    width = width_init;
    height = height_init;
    energy = energy_init;
    power = power_init;
  };

  std::string action(std::vector<std::string> updates) override {
    for (const auto &update : updates) {
      vector<string> params = split(update, " ");
      cout << "Command: " << params.at(0) << endl;
    }
    return "wait";
  }

  [[nodiscard]] std::string name() const override { return "My Robot"; }
};

int main() {
  vector<Robot *> robots = {new MyRobot()};
  robots.at(0)->set_config(2, 2, 10, 1);
  cout << "Name of the robot: " << robots.at(0)->name() << endl;
  cout << "Empty action is: " << robots.at(0)->action(vector<string>()) << endl;
  cout << "Attack action is: "
       << robots.at(0)->action(vector<string>{"board     ", "attack -1,-1,1"})
       << endl;
  return 0;
}