#include <iostream>
#include <librobots/Direction.h>
#include <librobots/Message.h>
#include <librobots/Position.h>
#include <librobots/Robot.h>
#include <librobots/RobotState.h>
#include <vector>

using namespace std;

class MyRobot1 : public Robot {
    size_t width = 0, height = 0, energy = 0, power = 0;

public:
    void setConfig(size_t width_init, size_t height_init, unsigned energy_init,
                   unsigned power_init) override {
        width = width_init;
        height = height_init;
        energy = energy_init;
        power = power_init;
    };

    string action(vector<string> updates) override {
        for (const auto &update: updates) {
            vector<string> params = split(update, " ", 2);
            cout << "Command: " << params.at(0) << endl;
            cout << "Parameters: " << params.at(1) << endl;
        }
        return "wait";
    }

    [[nodiscard]] string name() const override { return "My 1st Robot"; }
};

class MyRobot2 : public Robot {
    size_t width = 0, height = 0, energy = 0, power = 0;

public:
    void setConfig(size_t width_init, size_t height_init, unsigned energy_init,
                   unsigned power_init) override {
        width = width_init;
        height = height_init;
        energy = energy_init;
        power = power_init;
    };

    string action(vector<string> updates) override {
        string action = "wait";
        for (const auto &update: updates) {
            vector<string> params = split(update, " ", 2);
            cout << "Command: " << params.at(0) << endl;
            cout << "Parameters: " << params.at(1) << endl;
            if (params.at(0) == "damage") {
                action = "attack " + params.at(1);
            }
        }
        return action;
    }

    [[nodiscard]] string name() const override { return "My 2nd Robot"; }
};

void testRobots() {
    vector<Robot *> robots = {new MyRobot1(), new MyRobot2()};
    for (auto &robot: robots) {
        cout << "Initializing robot " << robot->name() << endl;
        robot->setConfig(2, 2, 10, 1);
    }

    for (auto &robot: robots) {
        cout << "Sending only board update to robot " << robot->name() << endl;
        string action = robot->action(vector<string>{"board R    B    R"});
        cout << "Robot asked for action: " << action << endl;
    }

    for (auto &robot: robots) {
        cout << "Sending 'board' and 'damage' to " << robot->name() << endl;
        string action =
                robot->action(vector<string>{"board R    B    R", "damage -1,1,1"});
        cout << "Robot asked for action: " << action << endl;
    }
}

int main() {
    testRobots();
    testDirection();
    testMessage();
    testPosition();
    testRobotState();
    return 0;
}
