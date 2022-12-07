//
// Created by Linus Gasser on 02.12.22.
//

#ifndef INEITI_MESSAGE_H
#define INEITI_MESSAGE_H

#include "Position.h"
#include <string>
#include <vector>

/**
 * The different types of messages in the game. The update and the
 * action messages are all together.
 */
enum class MessageType {
    UpdateBoard = 0,
    UpdateDamage,
    UpdateEnergy,
    UpdatePower,
    UpdateBonus,
    UpdateRobot,
    ActionMove,
    ActionAttack,
    ActionWait,
    ActionRadar,
};

/**
 * A message is an interpretation of the string passed between the game
 * engine and the robot.
 * It also has static methods that allow to create a string based on the
 * values.
 * Instead of getters, all variables are public.
 */
class Message {
public:
    /// The interpreted message.
    MessageType msg;

    /// A direction of all robots in the UpdateBoard message. Or one robot for the
    /// UpdateRobot and UpdateDamage message, or the direction for the
    /// ActionMove and ActionAttack messages.
    std::vector<Direction> robots;

    /// The directions of the newly spawned boni for UpdateBonus.
    std::vector<Direction> boni;

    /// The energy in UpdateDamage and UpdateEnergy message.
    /// The power in the UpdatePower message.
    unsigned energy = 0, power = 0;

    /**
   * Returns a new Message interpreted from the given string.
   * @param s the message to be interpreted.
   */
    explicit Message(const std::string &s);

    /**
   * Returns a vector of UpdateBoard messages, one for each roboter in the
   * 'robots' parameter.
   * @param robots all alive robots on the field
   * @return a vector of UpdateBoard messages that can be sent to the robots.
   */
    static std::vector<std::string>
    updateBoard(const std::vector<Position> &robots);

    /// Returns an UpdateDamage message.
    static std::string updateDamage(Direction direction, unsigned energy);

    /// Returns an UpdateEnergy message.
    static std::string updateEnergy(unsigned energy);

    /// Returns an UpdatePower message.
    static std::string updatePower(unsigned power);

    /// Returns an UpdateBonus message.
    static std::string updateBonus(Direction direction);

    /// Returns an UpdateRobot message.
    static std::string updateRobot(Direction direction);

    /// Returns an ActionMove message.
    static std::string actionMove(Direction direction);

    /// Returns an ActionAttack message.
    static std::string actionAttack(Direction direction);

    /// Returns an ActionWait message.
    static std::string actionWait();

    /// Returns an ActionRadar message.
    static std::string actionRadar();
};

/**
 * Splits a string in one or more substrings
 * @param s the string to split
 * @param sep the separator, which will be removed from the results
 * @param max_sep the maximum number of elements returned. 0 for as many as
 * possible
 * @return a vector of strings, but without the split
 */
std::vector<std::string> split(const std::string &s, const std::string &sep,
                               size_t max_sep = 0);

void testMessage();

#endif// INEITI_MESSAGE_H
