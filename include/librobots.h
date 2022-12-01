//
// Created by Linus Gasser on 30.11.22.
//

#ifndef LIBROBOT_LIBROBOTS_H
#define LIBROBOT_LIBROBOTS_H

#include <string>
#include <vector>

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

/**
 * An abstract class to define our robots.
 * If you inherit from this class, you must implement all virtual functions.
 */
class Robot {
public:
  /**
   * Sets the config of the robot.
   *
   * @param width of the playing field
   * @param height of the playing field
   * @param energy to start with
   * @param power to startwith
   */
  virtual void setConfig(size_t width, size_t height, unsigned energy,
                          unsigned power) = 0;
  /**
   * Requests an action from the robot - here the strategy must be
   * implemented.
   *
   * @param updates one or more updates from the game.
   * @return the action the robot wants to execute
   */
  virtual std::string action(std::vector<std::string> updates) = 0;

  /**
   * Fetches the name
   * @return the name of the robot.
   */
  [[nodiscard]] virtual std::string name() const = 0;
};

#endif // LIBROBOT_LIBROBOTS_H
