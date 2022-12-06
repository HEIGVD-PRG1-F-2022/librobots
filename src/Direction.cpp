//
// Created by Linus Gasser on 05.12.22.
//

#include "librobots/Direction.h"
#include "librobots/Message.h"
#include "librobots/Robot.h"
#include <cassert>
#include <cmath>

using namespace std;

Direction::Direction(int dx, int dy) : dx(dx), dy(dy) {}

Direction::Direction(const string &dirStr) {
  auto dir = split(dirStr, ",");
  dx = int(strtol(dir.at(0).c_str(), nullptr, 10));
  dy = int(strtol(dir.at(1).c_str(), nullptr, 10));
}

double Direction::mag() const { return hypot(dx, dy); }

int Direction::getdX() const { return dx; }

int Direction::getY() const { return dy; }

Direction Direction::unitary() {
  double longest = max(abs(dx), abs(dy));
  if (longest > 0) {
    return {int(round(dx / longest)), int(round(dy / longest))};
  } else {
    return *this;
  }
}

size_t Direction::indexSquare(size_t side) const {
  return size_t(dy * int(side) + dx + int(side * side / 2));
}

Direction &Direction::operator+=(const Direction &dir) {
  dx += dir.dx;
  dy += dir.dy;
  return *this;
}

Direction &Direction::operator-=(const Direction &dir) {
  dx -= dir.dx;
  dy -= dir.dy;
  return *this;
}

Direction operator+(Direction dir, const Direction &other) {
  return dir += other;
}

Direction operator-(Direction dir, const Direction &other) {
  return dir -= other;
}

bool operator==(const Direction &p1, const Direction &p2) {
  return p1.dx == p2.dx && p1.dy == p2.dy;
}

ostream &operator<<(ostream &out, const Direction &pos) {
  out << "d(" << pos.dx << "," << pos.dy << ")";
  return out;
}

void testDirection() { assert(Direction(0, 0) == Direction(0, 0).unitary()); }