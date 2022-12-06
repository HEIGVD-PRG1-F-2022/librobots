//
// Created by Linus Gasser on 01.12.22.
//

#ifndef INEITI_POSITION_H
#define INEITI_POSITION_H

#include "Direction.h"
#include <iostream>
#include <string>

/**
 * Represents a Position either with wraparound or without. If a width and
 * height are given, the + and - operations will wrap around.
 */
class Position {
  int x{}, y{};

  size_t width = 0, height = 0;

  /// Addition
  friend Position operator+(Position pos, const Position &other);

  /// Subtraction
  friend Position operator-(Position pos, const Position &other);

  /// Adding a Direction
  friend Position operator+(Position pos, const Direction &other);

  /// Subtracting a Direction
  friend Position operator-(Position pos, const Direction &other);

  /// Adding to a Direction
  friend Position operator+(const Direction &dir, Position other);

  /// Subtracting from a Direction
  friend Position operator-(const Direction &dir, Position other);

  /// Equality operator
  friend bool operator==(const Position &p1, const Position &p2);

  /// Inequality operator
  friend bool operator!=(const Position &p1, const Position &p2);

  /// Output operator
  friend std::ostream &operator<<(std::ostream &out, const Position &pos);

  /// Wraps the positions to fit the board.
  Position &wrap();

public:
  /// Default constructor.
  Position();

  /**
   * Constructor with optional width and height. If given, the Position will
   * always be calculated modulo the width and the height, making the board wrap
   * around on the sides. If both width and height are > 0, then every operation
   * will
   * @param x position
   * @param y position
   * @param width if given, will wrap around
   * @param height if given, will wrap around
   */
  Position(int x, int y, size_t width = 0, size_t height = 0);

  /// Addition for Position
  Position &operator+=(const Position &pos);

  /// Subtraction for Position
  Position &operator-=(const Position &pos);

  /// Addition for Position and Direction
  Position &operator+=(const Direction &dir);

  /// Subtraction for Position and Direction
  Position &operator-=(const Direction &dir);

  /// Getter for x position
  [[nodiscard]] int getX() const;

  /// Getter for y position
  [[nodiscard]] int getY() const;

  /// Negate both x and y position. If both width and height is given,
  /// this will also do the wrap, so probably give you not the result
  /// you expect.
  Position &neg();

  /// Creates a random position.
  static Position random(unsigned xMax, unsigned yMax, size_t width = 0,
                         size_t height = 0);

  /// The magnitude of this Position.
  [[nodiscard]] double mag() const;

  /// The distance to another Position.
  [[nodiscard]] double dist(const Position &other) const;

  /// Creates a Direction pointing from this Position to the 'other'.
  [[nodiscard]] Direction directionTo(const Position &other) const;
};

void testPosition();

#endif // INEITI_POSITION_H
