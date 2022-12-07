//
// Created by Linus Gasser on 04.12.22.
//

#include "librobots/Bonus.h"
#include <random>

using namespace std;

Bonus::Bonus(size_t width, size_t height, unsigned valueMax, BonusType type)
    : type(type) {
    pos = Position::random(unsigned(width), unsigned(height), width, height);
    std::random_device rd;
    std::uniform_int_distribution<unsigned> val(1, valueMax);
    value = val(rd);
}
