//
// Created by Linus Gasser on 01.12.22.
//

#ifndef INEITI_ROBOTSTATE_H
#define INEITI_ROBOTSTATE_H

#include "Message.h"
#include "Position.h"
#include "Robot.h"
#include <string>

/**
 * The RobotState holds a robot together with all its necessary values:
 * its position, energy, and power.
 * It collects updates in a cache until the game decides to update the robots.
 * The resulting action is stored in RobotState for the game to retrieve at a
 * later moment.
 */
class RobotState {
  /// A pointer to the robot.
  Robot *robot;

  /// The position of the robot on the grid.
  Position pos;

  /// The energy and the power of the robot.
  unsigned energy, power;

  /// A cache for putting new update messages before they are sent to the robot.
  std::vector<std::string> updates_cache;

  /// The last action sent by the robot.
  Message action = Message("wait");

public:
  /**
   * Creates a new robot with the given parameters.
   * @param robot for this RobotState
   * @param pos of the robot - should be initialised with width and height
   * @param side of the grid, should fit the width and height of 'pos'
   * @param energy the robot initially has
   * @param power the robot initially has
   */
  explicit RobotState(Robot *robot, Position pos, size_t side, unsigned energy,
                      unsigned power);

  /// Getter for the name of the robot
  std::string getName();

  /// Getter for the power of this robot
  [[nodiscard]] unsigned getPower() const;

  /// Getter for the energy of this robot
  [[nodiscard]] unsigned int getEnergy() const;

  /// Getter for the last action sent by the robot
  Message getAction();

  /// Getter for the current position of the robot
  [[nodiscard]] Position getPosition() const;

  /// Returns if this robot is dead or not
  [[nodiscard]] bool isDead() const;

  /// Executes an attack by another robot to the position 'dest'. The
  /// RobotState will only honor the attack if it is within range.
  /// The energy of the robot will be updated, and a message will be
  /// stored in the update_cache.
  void actionAttack(const RobotState &attacker, const Position &dest);

  /// Executes the move of a robot.
  void actionMove(const Direction &relative);

  /// Stores the position of the other robots in the update_cache.
  void actionRadar(const std::vector<Position> &positions);

  /// Stores the position of the new bonus in the update_cache.
  void actionBonus(const Position &bonus);

  /// Updates the energy of the robot and adds it to the update_cache.
  void actionEnergy(unsigned bonusEnergy);

  /// Updates the power of the robot and adds it to the update_cache.
  void actionPower(unsigned bonusPower);

  /// Checks whether this robot collides with the 'other'. If true,
  /// calculates which one survives and stores a 'updateDamage' message
  /// in update_cache.
  void checkCollision(RobotState &other);

  /// Sends all updates from the update_cache plus the given updateBoard
  /// to the robot and updates the 'action'.
  void sendUpdate(const std::string &updateBoard);
};

void testRobotState();

#endif // INEITI_ROBOTSTATE_H
