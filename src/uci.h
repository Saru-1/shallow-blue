#ifndef UCI_H
#define UCI_H

#include "board.h"
#include "move.h"
#include "search.h"
#include "option.h"
#include "book.h"
#include <sstream>
#include <fstream>
#include <memory>

/**
 * @brief Class for handling UCI input/output.
 */
namespace Uci {
  void init();

  /**
   * @brief Starts listening for UCI input and responds to it when received.
   */
  void start();

  extern Book _book;

  /**
   * @brief Current board being used.
   */
  extern Board _board;

  /**
   * @brief Search object for the current or last search that has taken place.
   * Is a nullptr if no search has yet taken place.
   */
  extern std::shared_ptr<Search> _search;
  
  void _initOptions();

  void _loadBook();

  void _printEngineInfo();

  void _setOption(std::istringstream&);

  /**
   * @brief Handles the ucinewgame command
   *
   * Sets the board to the starting position.
   */
  void _uciNewGame();

  /**
   * @brief Handles the position command
   *
   * The passed istringstream should contain the received line with everything following the `position` command.
   *
   * @param is istringstream contining position information
   */
  void _setPosition(std::istringstream&);

  /**
   * @brief Handles the go command
   *
   * The passed istringstream should contain the received line with everything following the `go` command
   *
   * @param is istringstream containing go parameters
   */
  void _go(std::istringstream&);

  /**
   * @brief Performs a search to the given depth and outputs the best move.
   * @param limits limits on the search
   */
  void _pickBestMove(Search::Limits);

  /**
   * @brief Calculates perft for each legal move of the current board and prints each perft value.
   *
   * @param depth Depth to run perft to
   */
  void _perftDivide(int);

  /**
   * @brief Returns the perft value for the given board to the given depth.
   *
   * @param  board Board to calculate perft of
   * @param  depth   Depth to search to
   * @return The perft of the board for the given depth
   */
  unsigned long long _perft(const Board&, int);

};

#endif
