//
// Created by Linus Gasser on 02.12.22.
//

#include "librobots/Message.h"
#include "librobots/Robot.h"
#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <string>

using namespace std;

const vector<string> MESSAGE_STRINGS = {"board", "damage", "energy", "power",
                                        "boni", "robot", "move", "attack",
                                        "wait", "radar"};

Message::Message(const string &s) {
    vector<string> cmd_args = split(s, " ", 2);
    auto it =
            find(MESSAGE_STRINGS.begin(), MESSAGE_STRINGS.end(), cmd_args.at(0));
    if (it == MESSAGE_STRINGS.end()) {
        throw runtime_error("This string is not a message: " + s);
    }
    msg = MessageType(it - MESSAGE_STRINGS.begin());
    if (cmd_args.size() > 1) {
        auto args = split(cmd_args.at(1), ",");
        switch (msg) {
            case MessageType::UpdateBoard:
                for (size_t i = 0; i < 25; i++) {
                    int x = int(i % 5) - 2;
                    int y = int(i / 5) - 2;
                    switch (args.at(0)[i]) {
                        case 'R':
                            robots.emplace_back(x, y);
                            break;
                        case 'B':
                            boni.emplace_back(x, y);
                            break;
                    }
                }
                break;
            case MessageType::UpdateEnergy:
                energy = unsigned(stoi(args.at(0)));
                break;
            case MessageType::UpdatePower:
                power = unsigned(stoi(args.at(0)));
                break;
            case MessageType::UpdateBonus:
                boni.emplace_back(stoi(args.at(0)), stoi(args.at(1)));
                break;
            case MessageType::UpdateDamage:
                energy = unsigned(stoi(args.at(2)));
                [[fallthrough]];
            case MessageType::UpdateRobot:
            case MessageType::ActionMove:
            case MessageType::ActionAttack:
                robots.emplace_back(stoi(args.at(0)), stoi(args.at(1)));
                break;
            case MessageType::ActionWait:
            case MessageType::ActionRadar:
                break;
        }
    }
}

std::string Message::getMessageType() const {
    return MESSAGE_STRINGS[size_t(msg)];
}

vector<string> Message::updateBoard(const vector<Position> &robots, const vector<Position> &boni) {
    vector<string> ret;
    for (auto src: robots) {
        string board(25, ' ');
        for (auto bonus: boni) {
            auto dir = src.directionTo(bonus);
            if (dir.mag() < 3) {
                board[dir.indexSquare(5)] = 'B';
            }
        }
        for (auto dst: robots) {
            if (src != dst) {
                auto dir = src.directionTo(dst);
                if (dir.mag() < 3) {
                    board[dir.indexSquare(5)] = 'R';
                }
            }
        }
        ret.push_back("board " + board);
    }
    return ret;
}

string format(const string &s, int count, ...) {
    va_list args;
    va_start(args, count);
    string ret = s + " ";

    while (count-- > 0) {
        ret += to_string(va_arg(args, int));
        if (count > 0) {
            ret += ",";
        }
    }

    va_end(args);
    return ret;
}

string Message::updateDamage(Direction direction, unsigned energy) {
    return format("damage", 3, direction.getdX(), direction.getdY(), energy);
}

string Message::updateEnergy(unsigned energy) {
    return format("energy", 1, energy);
}

string Message::updatePower(unsigned power) {
    return format("power", 1, power);
}

string Message::updateBonus(Direction direction) {
    return format("boni", 2, direction.getdX(), direction.getdY());
}

string Message::updateRobot(Direction direction) {
    return format("robot", 2, direction.getdX(), direction.getdY());
}

string Message::actionMove(Direction direction) {
    return format("move", 2, direction.getdX(), direction.getdY());
}

string Message::actionAttack(Direction direction) {
    return format("attack", 2, direction.getdX(), direction.getdY());
}

string Message::actionWait() { return "wait"; }

string Message::actionRadar() { return "radar"; }

vector<string> split(const string &s, const string &sep, size_t max_sep) {
    vector<string> ret;
    size_t last = 0;
    size_t next = 0;
    while ((next = s.find(sep, last)) != string::npos &&
           (ret.size() + 1 < max_sep || max_sep == 0)) {
        ret.push_back(s.substr(last, next - last));
        last = next + 1;
    }
    ret.push_back(s.substr(last));
    return ret;
}

void testMessage() {
    Message msg1{"board "
                 "R  B "
                 "  B  "
                 "  R  "
                 "  R  "
                 "   RB"};
    assert(msg1.msg == MessageType::UpdateBoard);
    assert(msg1.robots.size() == 4);
    assert(msg1.boni.size() == 3);
    vector<Direction> robotsDir = {{-2, -2}, {0, 0}, {0, 1}, {1, 2}};
    assert(robotsDir == msg1.robots);
    vector<Direction> bonus = {{1, -2}, {0, -1}, {2, 2}};
    assert(bonus == msg1.boni);

    vector<string> boards;
    vector<Position> robots(msg1.robots.size());
    transform(msg1.robots.begin(), msg1.robots.end(), robots.begin(),
              [](Direction d) -> Position { return Position() + d; });
    for (const auto &msg: Message::updateBoard(robots)) {
        boards.emplace_back(msg);
    }
    assert(boards.size() == 4);
    vector<string> boardsString{
            // board   1111122222333334444455555
            {"board                         R"},
            {"board R                R     R "},
            {"board        R          R      "},
            {"board  R    R                  "},
    };
    assert(boards == boardsString);

    Message msg2("move -1,-1");
    assert(msg2.msg == MessageType::ActionMove);
    assert(msg2.robots.at(0) == Direction(-1, -1));
    assert("energy 2" == Message::updateEnergy(2));
}