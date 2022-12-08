//
// Created by Linus Gasser on 01.12.22.
//

#include "librobots/Position.h"
#include "librobots/Robot.h"
#include <cassert>
#include <cmath>
#include <random>

using namespace std;

Position::Position() : Position(0, 0) {}

Position::Position(int x, int y, size_t width, size_t height)
    : x(x), y(y), width(width), height(height) {}

Position Position::random(unsigned xMax, unsigned yMax, size_t width,
                          size_t height) {
    std::random_device rd;
    std::uniform_int_distribution<int> w(0, int(xMax - 1));
    std::uniform_int_distribution<int> h(0, int(yMax - 1));
    return {w(rd), h(rd), width, height};
}

Position operator+(Position pos, const Position &other) { return pos += other; }

Position operator-(Position pos, const Position &other) { return pos -= other; }

Position operator+(Position pos, const Direction &other) {
    return pos += other;
}

Position operator-(Position pos, const Direction &other) {
    return pos -= other;
}

Position operator+(const Direction &dir, Position other) { return other + dir; }

Position operator-(const Direction &dir, Position other) {
    return (other - dir).neg();
}

bool operator==(const Position &p1, const Position &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(const Position &p1, const Position &p2) { return !(p1 == p2); }

ostream &operator<<(ostream &out, const Position &pos) {
    out << "(" << pos.x << "," << pos.y << ")";
    return out;
}

Position &Position::operator+=(const Position &pos) {
    x += pos.x;
    y += pos.y;
    wrap();
    return *this;
}
Position &Position::operator-=(const Position &pos) {
    x -= pos.x;
    y -= pos.y;
    wrap();
    return *this;
}
Position &Position::operator+=(const Direction &dir) {
    x += dir.getdX();
    y += dir.getdY();
    wrap();
    return *this;
}
Position &Position::operator-=(const Direction &dir) {
    x -= dir.getdX();
    y -= dir.getdY();
    wrap();
    return *this;
}

int Position::getX() const { return x; }

int Position::getY() const { return y; }

double Position::mag() const { return hypot(x, y); }

double Position::dist(const Position &other) const {
    return (other - *this).mag();
}

Direction Position::directionTo(const Position &other) const {
    auto dist = (other - *this);
    if (width > 0 && height > 0) {
        int w = int(width);
        int h = int(height);
        dist.x = ((dist.x + w / 2) % w) - w / 2;
        dist.y = ((dist.y + h / 2) % h) - h / 2;
    }

    return {dist.x, dist.y};
}

Position &Position::wrap() {
    if (width == 0 || height == 0) {
        return *this;
    }

    int w = int(width);
    int h = int(height);
    x = (x + w) % w;
    y = (y + h) % h;
    return *this;
}

Position &Position::neg() {
    x *= -1;
    y *= -1;
    wrap();
    return *this;
}

void testPosition() {
    Position p1(1, 1, 10, 10), p2(0, 0, 10, 10);
    assert(Position(9, 9) == p2 - p1);
    Position p3(1, 1), p4(0, 0);
    assert(Position(-1, -1) == p4 - p3);
    Direction dir = Position(0, 0, 10, 10).directionTo(Position(7, 8, 10, 10));
    assert(Direction(-3, -2) == dir);
}