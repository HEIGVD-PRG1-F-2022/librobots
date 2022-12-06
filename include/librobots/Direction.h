//
// Created by Linus Gasser on 05.12.22.
//

#ifndef INEITI_DIRECTION_H
#define INEITI_DIRECTION_H

#include <iostream>

/**
 * A direction towards another object. It can be used together with the Position
 * class.
 */
class Direction {
  int dx, dy;

  /// Comparison of two Direction s
  friend bool operator==(const Direction &p1, const Direction &p2);

  /// Adding two Direction s
  friend Direction operator+(Direction dir, const Direction &other);

  /// Subtracting two Direction s
  friend Direction operator-(Direction dir, const Direction &other);

  /// Outputting a Direction
  friend std::ostream &operator<<(std::ostream &out, const Direction &pos);

public:
  /// Default constructor.
  Direction() : Direction(0, 0){};

  /// Create a Direction given dx and dy.
  Direction(int dx, int dy);

  /// Create a Direction from a "dx,dy" string
  explicit Direction(const std::string &dirStr);

  /// Returns the direction with magnitude 0 <= mag < 2. In a square grid this
  /// corresponds to one of the 9 squares, including 0, 0.
  Direction unitary();

  /// Addition operand.
  Direction &operator+=(const Direction &dir);

  /// Subtraction operand.
  Direction &operator-=(const Direction &dir);

  /// Returns a copy of dX.
  [[nodiscard]] int getdX() const;

  /// Returns a copy of dY.
  [[nodiscard]] int getY() const;

  /// The magnitude of the direction.
  [[nodiscard]] double mag() const;

  /// Returns the index to a vector (or string) representing a square
  /// with all possible positions from (-side/2, -side/2) to (side/2, side/2).
  [[nodiscard]] size_t indexSquare(size_t side) const;
};

void testDirection();

#endif // INEITI_DIRECTION_H
