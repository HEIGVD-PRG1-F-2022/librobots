//
// Created by Linus Gasser on 04.12.22.
//

#ifndef INEITI_BONUS_H
#define INEITI_BONUS_H

#include "Position.h"

/// Represents either an Energy or a Power bonus.
enum class BonusType {
  Energy,
  Power,
};

/**
 * The bonus class is very simply and probably could be a `struct`. It exposes
 * its variables as public members.
 */
class Bonus {
public:
  /// The position of the bonus on the board
  Position pos;

  /// Which type this bonus is
  BonusType type;

  /// The value - represents either the energy or the power.
  unsigned value;

  /// Instantiates a bonus randomly with a position between 0..width and
  /// 0..height and 1..=valueMax.
  explicit Bonus(size_t width, size_t height, unsigned valueMax,
                 BonusType type);
};

#endif // INEITI_BONUS_H
